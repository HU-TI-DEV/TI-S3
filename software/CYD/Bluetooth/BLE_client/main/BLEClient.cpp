/*!
 * \brief BLE implementation
 */
#include "BleClient.hpp"

std::atomic<bool> BleClient::ready_{false};

ble_addr_t BleClient::server_addr_;
uint16_t BleClient::conn_handle_ = BLE_HS_CONN_HANDLE_NONE; // do not use 0! 0 can be a perfect handle.
uint16_t BleClient::rx_handle_ = 0;
uint16_t BleClient::tx_handle_ = 0;
uint8_t BleClient::own_addr_type_ = 0;
uint16_t BleClient::svc_end_handle_ = 0;

BleClient::BleClient() {}
BleClient::~BleClient() {}

// Discovery services function. With help from ChatGPT5. Only one Gatt characteristic discovery is allowed at the time that is why RX abd TX discovery are sequential. This is not for the light hearted.
void BleClient::discoverServices(uint16_t conn_handle) {
    ESP_LOGI(TAG, "Starting service discovery");

    struct Range { uint16_t start{0}; uint16_t end{0}; };
    auto *range = (Range*)malloc(sizeof(Range));

    int rc = ble_gattc_disc_svc_by_uuid(
        conn_handle, &SERVICE_UUID.u,
        [](uint16_t ch, const ble_gatt_error *err, const ble_gatt_svc *svc, void *arg) -> int {
            auto *r = reinterpret_cast<Range*>(arg);

            if (err->status == 0 && svc) {
                r->start = svc->start_handle;
                r->end   = svc->end_handle;
                ESP_LOGI(TAG, "Service found: start_handle=%u end_handle=%u", r->start, r->end);
                return 0; // keep going; we'll get a terminal callback with status != 0
            }

            if (r->start == 0 || r->end == 0) {
                ESP_LOGE(TAG, "Service not found (status=%d)", err->status);
                free(r);
                return BLE_HS_EDONE;
            }

            // 1) start RX discovery (by UUID)
            int rc1 = ble_gattc_disc_chrs_by_uuid(
                ch, r->start, r->end, &CHAR_UUID_RX.u,
                [](uint16_t ch2, const ble_gatt_error *err2, const ble_gatt_chr *chr, void *arg2) -> int {
                    auto *r2 = reinterpret_cast<Range*>(arg2);

                    if (err2->status == 0 && chr) {
                        BleClient::rx_handle_ = chr->val_handle;
                        ESP_LOGI(TAG, "RX characteristic handle=%u", BleClient::rx_handle_);
                        return 0; // wait for terminal callback
                    }

                    // RX discovery done (status != 0): now 2) start TX discovery
                    ESP_LOGI(TAG, "Discover TX characteristics by UUID");
                    auto *svc_end_heap = (uint16_t*)malloc(sizeof(uint16_t));
                    *svc_end_heap = r2->end;

                    int rc2 = ble_gattc_disc_chrs_by_uuid(
                        ch2, r2->start, r2->end, &CHAR_UUID_TX.u,
                        BleClient::onTxChrDiscovered,   // sets tx_handle_ and discovers CCCD
                        svc_end_heap);

                    if (rc2 != 0) {
                        ESP_LOGE(TAG, "Failed to start TX discovery: %d", rc2);
                        free(svc_end_heap);
                    }

                    free(r2);
                    return BLE_HS_EDONE;
                },
                r);

            if (rc1 != 0) {
                ESP_LOGE(TAG, "Failed to start RX discovery: %d", rc1);
                free(r);
            }
            return BLE_HS_EDONE;
        },
        range);

    if (rc != 0) {
        ESP_LOGE(TAG, "Failed to start service discovery: %d", rc);
        free(range);
    }
}

esp_err_t BleClient::init() {
    ESP_LOGI(TAG, "Init BLE client");

    // nvs flash init
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "failed to initialize nvs flash, error code: %d ", ret);
        return 0;
    }

    // NimBLE host config init
    ESP_ERROR_CHECK(nimble_port_init());
    ESP_LOGI(TAG, "NimBLE port initialized");

    ble_hs_cfg.reset_cb = onReset;
    ble_hs_cfg.sync_cb = onSync;

    // GAP service initialization 
    ble_svc_gap_init();
    ble_svc_gatt_init();

    ESP_LOGI(TAG, "Starting NimBLE FreeRTOS task");
    nimble_port_freertos_init(clientTask);

    return ESP_OK;
}

bool BleClient::isReady() const {
    return ready_.load();
}

void BleClient::clientTask(void*) {
    ESP_LOGI(TAG, "Client BLE task started");

    ESP_LOGI(TAG, "Running NimBLE host loop...");
    nimble_port_run();  // BLE events and stack execution

    // Never reached unless NimBLE shuts down
    nimble_port_freertos_deinit();

    // Clean up at exit
    vTaskDelete(NULL);
}

void BleClient::onSync() {
    ESP_LOGI(TAG, "BLE stack synced");

    ble_hs_id_infer_auto(0, &own_addr_type_);
    ESP_LOGI(TAG, "Own addr type: %d", own_addr_type_);

    struct ble_gap_disc_params params = {
        .itvl = 0x10,
        .window = 0x10,
        .filter_policy = 0,
        .limited = 0,
        .passive = 0,
        .filter_duplicates = 0, 
    };

    int rc = ble_gap_disc(own_addr_type_, BLE_HS_FOREVER, &params, gapEvent, nullptr);
    if (rc != 0) {
        ESP_LOGE(TAG, "Failed to start scanning: %d", rc);
    } else {
        ESP_LOGI(TAG, "Scanning started...");
    }
}

void BleClient::onReset(int reason) {
    ESP_LOGE(TAG, "BLE reset, reason=%d", reason);
}

// catch (all) gap events
int BleClient::gapEvent(struct ble_gap_event* event, void*) {
    ESP_LOGI(TAG, "gapEvent type: %d", event->type);

    switch (event->type) {
        case BLE_GAP_EVENT_DISC: {
            const auto& d = event->disc;
            ESP_LOGI(TAG, "Discovered: %02X:%02X:%02X:%02X:%02X:%02X",
                    d.addr.val[5], d.addr.val[4], d.addr.val[3],
                    d.addr.val[2], d.addr.val[1], d.addr.val[0]);

            ESP_LOGI(TAG, "Discovered type=%d", d.addr.type); // 0 = public, 1 = random
            logDeviceName(d.data, d.length_data);

            ble_gap_disc_cancel();
            server_addr_ = d.addr;

            vTaskDelay(pdMS_TO_TICKS(200)); // allow stack to stabilize

            server_addr_.type = d.addr.type;  // by discovered type
            int rc = ble_gap_connect(own_addr_type_, &server_addr_, BLE_HS_FOREVER, nullptr, gapEvent, nullptr);
            if (rc != 0) {
                ESP_LOGE(TAG, "Connect failed: %d", rc);
            }

            break;
        }

        case BLE_GAP_EVENT_CONNECT: {
            if (event->connect.status == 0) {
                conn_handle_ = event->connect.conn_handle;
                ESP_LOGI(TAG, "GAP event: CONNECTED");
                ESP_LOGI(TAG, "Connection handle: %d", conn_handle_);

                struct ble_gap_conn_desc desc;
                int rc = ble_gap_conn_find(conn_handle_, &desc);
                if (rc == 0) {
                    ESP_LOGI(TAG, "Peer address type: %d", desc.peer_id_addr.type);
                    ESP_LOGI(TAG, "Peer address: %02X:%02X:%02X:%02X:%02X:%02X",
                            desc.peer_id_addr.val[5], desc.peer_id_addr.val[4],
                            desc.peer_id_addr.val[3], desc.peer_id_addr.val[2],
                            desc.peer_id_addr.val[1], desc.peer_id_addr.val[0]);
                } else {
                    ESP_LOGW(TAG, "Failed to get connection descriptor (rc=%d)", rc);
                }

                vTaskDelay(pdMS_TO_TICKS(100));  // small settle delay
                ESP_LOGI(TAG, "Starting service discovery... (discoveryServices function called)");
                discoverServices(conn_handle_);   // uses &SERVICE_UUID.u internally
            } else {
                ESP_LOGE(TAG, "GAP event: CONNECT FAILED; status=%d", event->connect.status);
            }
            break;
        }

        case BLE_GAP_EVENT_CONN_UPDATE:
            ESP_LOGI(TAG, "Connection parameters updated");
            break;

        case BLE_GAP_EVENT_DISC_COMPLETE:
            ESP_LOGI(TAG, "Discovery complete");
            break;
        
        case BLE_GAP_EVENT_NOTIFY_RX: {
            const auto &n = event->notify_rx;
            ESP_LOGI(TAG, "Notify RX: attr_handle=%u ind=%d", n.attr_handle, n.indication);
            if (n.om && n.om->om_len) {
                std::string msg(reinterpret_cast<const char*>(n.om->om_data), n.om->om_len);
                ESP_LOGI(TAG, "Notification received: %s", msg.c_str());
            }
            break;
        }

        default:
            ESP_LOGI(TAG, "Unhandled GAP event: %d", event->type);
            break;
    }

    return 0;
}

// discriptor discovery
int BleClient::txDscDiscovered(uint16_t conn_handle,
                               const struct ble_gatt_error* error,
                               uint16_t /*chr_val_handle*/,
                               const struct ble_gatt_dsc* dsc,
                               void*) {
    if (error->status != 0 || !dsc) {
        ESP_LOGE(TAG, "Descriptor discovery failed: %d", error->status);
        return 0;
    }

    // Create a 0x2902 UUID to compare against
    const ble_uuid16_t cccd_uuid = BLE_UUID16_INIT(0x2902);

    // Compare dsc->uuid (ble_uuid_any_t) with the 0x2902 uuid
    if (ble_uuid_cmp(&dsc->uuid.u, &cccd_uuid.u) == 0) {
        ESP_LOGI(TAG, "Found CCCD handle=%u", dsc->handle);

        // Enable NOTIFY: 0x0001 (LSB first)
        const uint8_t cccd_value[2] = { 0x01, 0x00 };

        int rc = ble_gattc_write_flat(conn_handle,
                                      dsc->handle,
                                      cccd_value,
                                      sizeof(cccd_value),
                                      onCccdWriteComplete,   // use a custom callback, not nullptr
                                      nullptr);
        if (rc != 0) {
            ESP_LOGE(TAG, "Failed to enable notifications (rc=%d)", rc);
        } else {
            ESP_LOGI(TAG, "Subscribed to TX notifications");
            BleClient::ready_.store(true);
        }
    }

    return 0;
}

int BleClient::onNotify(uint16_t conn_handle,
                        const struct ble_gatt_error* error,
                        struct ble_gatt_attr* attr,
                        void*) {
    if (error->status != 0 || !attr || !attr->om) {
        ESP_LOGE(TAG, "Notification error or empty attribute");
        return 0;
    }

    std::string message(reinterpret_cast<const char*>(attr->om->om_data), attr->om->om_len);
    ESP_LOGI(TAG, "Notification received: %s", message.c_str());
    return 0;
} 

// function to send string to RX
esp_err_t BleClient::sendMessage(const std::string& msg) {
    if (rx_handle_ == 0) {
        ESP_LOGE(TAG, "Cannot send: RX handle not discovered.");
        return ESP_FAIL;
    }
    if (conn_handle_ == BLE_HS_CONN_HANDLE_NONE) {
        ESP_LOGE(TAG, "Cannot send: no connection.");
        return ESP_FAIL;
    }

    int rc = ble_gattc_write_flat(conn_handle_, rx_handle_, msg.data(), msg.size(), onWriteComplete, nullptr);
    
    ESP_LOGI(TAG, "Write to RX rc=%d, len=%u", rc, (unsigned)msg.size());

    return rc == 0 ? ESP_OK : ESP_FAIL;
}

// helper function to display device name
void BleClient::logDeviceName(const uint8_t* data, uint8_t length) {
    uint8_t index = 0;
    while (index < length) {
        uint8_t field_len = data[index];
        if (field_len == 0 || (index + field_len >= length)) break;

        uint8_t field_type = data[index + 1];
        if (field_type == BLE_HS_ADV_TYPE_COMP_NAME || field_type == BLE_HS_ADV_TYPE_SHORT_NAME) {
            std::string name(reinterpret_cast<const char*>(&data[index + 2]), field_len - 1);
            ESP_LOGI(TAG, "Device name: %s", name.c_str());
            return;
        }

        index += field_len + 1;
    }
    ESP_LOGI(TAG, "Device name: (not found)");
}

// helper callback for Tx to discover all descriptors
int BleClient::onTxChrDiscovered(uint16_t conn_handle,
                             const struct ble_gatt_error *error,
                             const struct ble_gatt_chr *chr,
                             void *arg)
{
    // arg carries the service end handle (malloc'd below)
    uint16_t svc_end = arg ? *(uint16_t*)arg : 0;

    if (error->status != 0) {
        ESP_LOGW(TAG, "TX discovery complete (status=%d), tx_handle_=%u",
                 error->status, BleClient::tx_handle_);
        if (arg) free(arg);
        return BLE_HS_EDONE;
    }

    // Save TX value handle
    tx_handle_ = chr->val_handle;
    ESP_LOGI(TAG, "TX characteristic handle=%u", tx_handle_);

    // We no longer need arg beyond this point
    if (arg) free(arg);

    // Discover all descriptors in [tx_val_handle+1 .. service_end]
    int rc_d = ble_gattc_disc_all_dscs(conn_handle,
                                       chr->val_handle,
                                       svc_end,
                                       txDscDiscovered,  // descriptor callback helper function
                                       nullptr);
    if (rc_d != 0) {
        ESP_LOGE(TAG, "Failed to start descriptor discovery: %d", rc_d);
    }
    return BLE_HS_EDONE;
}

// ccc write complete callback
int BleClient::onCccdWriteComplete(uint16_t conn_handle,
                               const struct ble_gatt_error *error,
                               struct ble_gatt_attr* attr,
                               void* arg) {
    if (error->status == 0) {
        ESP_LOGI(TAG, "CCCD write ACKed; notifications enabled");
        BleClient::ready_.store(true);
    } else {
        ESP_LOGE(TAG, "CCCD write failed rc=%d", error->status);
    }
    return 0;
}

// completion callback for message write
int BleClient::onWriteComplete(uint16_t conn_handle,
                           const ble_gatt_error *error,
                           struct ble_gatt_attr* attr,
                           void* arg) {
    if (error->status == 0) {
        ESP_LOGI(TAG, "RX write ACKed by server");
    } else {
        ESP_LOGE(TAG, "RX write failed rc=%d", error->status);
    }
    return 0;
}
