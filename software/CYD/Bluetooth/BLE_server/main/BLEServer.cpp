/*! \brief BLE Server implementation
 *
 * Creates a BLE server device. It advertises a services by UUID. The implemented function receives a string, reverses it, and sends it back.
 */

#include "BLEServer.hpp"

uint16_t BleServer::conn_handle_ = 0;
uint16_t BleServer::rx_handle_ = 0;
uint16_t BleServer::tx_handle_ = 0;
uint8_t BleServer::own_addr_type_ = 0;

BleServer::BleServer() {}
BleServer::~BleServer() {}

esp_err_t BleServer::init() {
    ESP_LOGI(TAG, "NVS flash init");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    // Initialize NimBLE host stack
    ESP_LOGI(TAG, "NimBLE stack init");
    ret = nimble_port_init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init NimBLE port: %s", esp_err_to_name(ret));
        return ret;
    }

    // Configure callbacks
    ESP_LOGI(TAG, "Set callbacks");
    ble_hs_cfg.sync_cb = onSync;
    ble_hs_cfg.reset_cb = onReset;
    ESP_LOGI(TAG, "Callbacks are set");

    // Start NimBLE stack task
    nimble_port_freertos_init([](void*) {
        ESP_LOGI(TAG, "NimBLE FreeRTOS task started");
        nimble_port_run();  // wait forever
    });

    return ESP_OK;
}

void BleServer::onSync() {
    ESP_LOGI(TAG, "OnSync function called");
    // Get BLE MAC
    ble_addr_t addr;
    ble_hs_id_infer_auto(0, &own_addr_type_);
    ble_hs_id_copy_addr(own_addr_type_, addr.val, nullptr);
    
    ESP_LOGI(TAG, "BLE address: %02x:%02x:%02x:%02x:%02x:%02x",
             addr.val[5], addr.val[4], addr.val[3],
             addr.val[2], addr.val[1], addr.val[0]);

    ESP_LOGI(TAG, "Gap init");
    ble_svc_gap_init();
    ESP_LOGI(TAG, "Device name set");
    ble_svc_gap_device_name_set("n0"); // shorten name to reduce payload (CYD-server was too long)

    ESP_LOGI(TAG, "Gatt init");
    ble_svc_gatt_init();
    ESP_LOGI(TAG, "Register services");
    registerService();

    // Set advertising fields
    ESP_ERROR_CHECK(ble_gap_adv_set_fields(advFields()));
    
    ESP_LOGI(TAG, "Advertising start");
    vTaskDelay(pdMS_TO_TICKS(200)); // slight delay
    ESP_ERROR_CHECK(ble_gap_adv_start(
        own_addr_type_,
        nullptr,
        BLE_HS_FOREVER,
        advParams(),
        gapEvent,
        nullptr
    ));
     ESP_LOGI(TAG, "Advertising has started");
}

void BleServer::onReset(int reason) {
    ESP_LOGE(TAG, "Resetting BLE stack; reason=%d", reason);
}

void BleServer::registerService() {

    static ble_gatt_chr_def characteristics[] = {
        {
            .uuid = &rx_uuid.u,
            .access_cb = onRxWrite,
            .flags = BLE_GATT_CHR_F_WRITE,
            .val_handle = &rx_handle_,  // store RX handle
        },
        {
            .uuid = &tx_uuid.u,
            .access_cb = onTxRead,
            //.flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY, // added: expose the Client Characteristic Configuration Descriptor (CCCD). 
            .flags = BLE_GATT_CHR_F_NOTIFY, // Notify should be enough.
            .val_handle = &tx_handle_,  // store TX handle
        },
        {0}
    };

    static ble_gatt_svc_def svc_defs[] = {
        {
            .type = BLE_GATT_SVC_TYPE_PRIMARY,
            .uuid = &svc_uuid.u,
            .characteristics = characteristics,
        },
        {0}
    };

    ESP_ERROR_CHECK(ble_gatts_count_cfg(svc_defs));
    ESP_ERROR_CHECK(ble_gatts_add_svcs(svc_defs));

    // Make the GATT services DB live. Important was not in previous version!
    int rc = ble_gatts_start();
    if (rc != 0) {
        ESP_LOGE(TAG, "ble_gatts_start failed: %d", rc);
    } else {
        ESP_LOGI(TAG, "GATT services started");
        ESP_LOGI(TAG, "Handles: RX=%u (write), TX=%u (notify)", rx_handle_, tx_handle_); // 16 and 18 in my case
    }
}

int BleServer::onRxWrite(uint16_t conn_handle, uint16_t, ble_gatt_access_ctxt* ctxt, void*) {
    // Copy payload safely (handles mbuf chains) with help from ChatGPT5
    std::string received;
    received.resize(ctxt->om->om_len);
    os_mbuf_copydata(ctxt->om, 0, ctxt->om->om_len, received.data());

    ESP_LOGI(TAG, "Received string: %s", received.c_str());

    std::reverse(received.begin(), received.end());
    ESP_LOGI(TAG, "Reversed string: %s", received.c_str());

    os_mbuf* om = ble_hs_mbuf_from_flat(received.data(), received.size());
    int rc = ble_gatts_notify_custom(conn_handle, tx_handle_, om);
    if (rc != 0) {
        ESP_LOGE(TAG, "Notify failed rc=%d (tx_handle_=%u, conn=%u)", rc, tx_handle_, conn_handle);
        os_mbuf_free_chain(om);
    }
    return 0;
}

int BleServer::onTxRead(uint16_t, uint16_t, struct ble_gatt_access_ctxt*, void*) {
    return 0;  // TX is notify-only
}

int BleServer::gapEvent(struct ble_gap_event* event, void*) {
    switch (event->type) {
        case BLE_GAP_EVENT_CONNECT:
            if (event->connect.status == 0) {
                conn_handle_ = event->connect.conn_handle;
                ESP_LOGI(TAG, "Client connected, handle=%d", conn_handle_);
            } else {
                ESP_LOGI(TAG, "Connection failed, restarting advertising");
                ble_gap_adv_start(
                    own_addr_type_,
                    nullptr,
                    BLE_HS_FOREVER,
                    advParams(),
                    gapEvent,
                    nullptr
                );
            }
            break;

        case BLE_GAP_EVENT_DISCONNECT:
            ESP_LOGI(TAG, "Client disconnected, restarting advertising");
            ble_gap_adv_start(
                own_addr_type_,
                nullptr,
                BLE_HS_FOREVER,
                advParams(),
                gapEvent,
                nullptr
            );
            break;

        default:
            break;
    }
    return 0;
}

ble_gap_adv_params* BleServer::advParams() {
    static ble_gap_adv_params params;
    memset(&params, 0, sizeof(params));
    params.conn_mode = BLE_GAP_CONN_MODE_UND;
    params.disc_mode = BLE_GAP_DISC_MODE_GEN;
    return &params;
}

// modified to also advertise the given name
ble_hs_adv_fields* BleServer::advFields() {
    // there is an 31 bytes payload limit! So there is a limit in what you can do here.
    static ble_hs_adv_fields fields;
    memset(&fields, 0, sizeof(fields));

    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
    fields.tx_pwr_lvl_is_present = 1;
    fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

    const char* name = ble_svc_gap_device_name();
    fields.name = (uint8_t*)name;
    fields.name_len = strlen(name);
    fields.name_is_complete = 1;

    // Advertise service UUID, this takes most op the space.
    fields.uuids128 = (ble_uuid128_t *)&svc_uuid; 
    fields.num_uuids128 = 1;
    fields.uuids128_is_complete = 1;
 
    return &fields;
}