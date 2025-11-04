/*!
 * \brief A class to manage BLE connections
 * Configure NimBLE - BLE only in menuconfig. This enables GATT client and server functionality
 * The sdkconfig is hard to configure. I used the sdkconfig file from the esp-idf example NimBLE_Beacon 
 * 
 * Rediscovery is not yet implemented. Remember that you might have many BLE devices that you connect to but it might nog be your server!
 * 
 * For ESP-IDF 5.4
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include <string>
#include <array>
#include <atomic>
#include <cstdint>

// NimBLE stack APIs
#include "esp_nimble_hci.h"  // Required for NimBLE HCI
#include "nimble/nimble_port.h"  // NimBLE port functions
#include "nimble/nimble_port_freertos.h"  // FreeRTOS integration
#include "host/ble_hs.h"  // BLE Host Stack
#include "host/ble_hs_adv.h" // BLE advertise 
#include "host/ble_gap.h"
#include "services/gap/ble_svc_gap.h"  // GAP service
#include "services/gatt/ble_svc_gatt.h"  // GATT service
#include "host/ble_uuid.h"

constexpr uint8_t BLE_HS_ADV_TYPE_SHORT_NAME = 0x08; 

class BleClient {
public:
    BleClient();
    ~BleClient();

    esp_err_t init();
    esp_err_t sendMessage(const std::string& msg);
    static void discoverServices(uint16_t conn_handle);

    bool isReady() const; // function to determine if BLE connection between devices is ready

private:
    static constexpr const char* TAG = "BleClient";

    static std::atomic<bool> ready_; // private ready flag static for simplicity

    // BLE handles and state
    static ble_addr_t server_addr_;
    static uint16_t conn_handle_;
    static uint16_t rx_handle_;
    static uint16_t tx_handle_;
    static uint8_t own_addr_type_;
    static uint16_t svc_end_handle_; // current service end handle for descriptor discovery

    // Service
    static constexpr ble_uuid128_t SERVICE_UUID = BLE_UUID128_INIT(
        0xf0, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );

    // RX = …de01  (client WRITES here)
    static constexpr ble_uuid128_t CHAR_UUID_RX = BLE_UUID128_INIT(
        0x01, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );

    // TX = …de02  (client SUBSCRIBES here)
    static constexpr ble_uuid128_t CHAR_UUID_TX = BLE_UUID128_INIT(
        0x02, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );

    // BLE lifecycle
    static void onSync();
    static void onReset(int reason);

    // GAP event handler
    static int gapEvent(struct ble_gap_event* event, void* arg);

    // BLE client task (called from FreeRTOS)
    static void clientTask(void*);

    // helper function(s)
    static void logDeviceName(const uint8_t* data, uint8_t length);
    
    static int txDscDiscovered(uint16_t conn_handle,
                               const struct ble_gatt_error* error,
                               uint16_t chr_val_handle,
                               const struct ble_gatt_dsc* dsc,
                               void* arg); 

    static int onNotify(uint16_t conn_handle,
                        const struct ble_gatt_error* error,
                        struct ble_gatt_attr* attr,
                        void* arg);

    static int onTxChrDiscovered(uint16_t conn_handle,
                                const struct ble_gatt_error* error,
                                const struct ble_gatt_chr* chr,
                                void* arg);
    
    static int onCccdWriteComplete(uint16_t conn_handle,
                               const struct ble_gatt_error* error,
                               struct ble_gatt_attr* attr,
                               void* arg);

    static int onWriteComplete(uint16_t conn_handle,
                           const ble_gatt_error* error,
                           struct ble_gatt_attr* attr,
                           void* arg);
};