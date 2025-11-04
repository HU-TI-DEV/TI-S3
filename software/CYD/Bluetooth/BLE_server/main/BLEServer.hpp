/*!
 * \brief A class to manage BLE connections
 * Configure NimBLE - BLE only in menuconfig. This enables GATT client and server functionality
 * The sdkconfig is hard to configure. I used the sdkconfig file from the esp-idf example NimBLE_Beacon 
 *  
 * For ESP-IDF 5.4
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"

#include <algorithm>
#include <cstring>

// NimBLE stack APIs
#include "esp_nimble_hci.h"  // Required for NimBLE HCI
#include "nimble/nimble_port.h"  // NimBLE port functions
#include "nimble/nimble_port_freertos.h"  // FreeRTOS integration
#include "host/ble_hs.h"  // BLE Host Stack
#include "services/gap/ble_svc_gap.h"  // GAP service
#include "services/gatt/ble_svc_gatt.h"  // GATT service

#include <array>
#include <string>

class BleServer {
public:
    BleServer();
    ~BleServer();

    esp_err_t init();

private:
    static constexpr const char* TAG = "BleServer";

    static void onSync();
    static void onReset(int reason);
    static int gapEvent(struct ble_gap_event* event, void* arg);
    static int onRxWrite(uint16_t conn_handle, uint16_t attr_handle,
                         struct ble_gatt_access_ctxt* ctxt, void* arg);
    static int onTxRead(uint16_t conn_handle, uint16_t attr_handle,
                        struct ble_gatt_access_ctxt* ctxt, void* arg);
    static void registerService();
    static ble_gap_adv_params* advParams();
    static ble_hs_adv_fields* advFields();

    // BLE handles and state
    static uint16_t conn_handle_;
    static uint16_t rx_handle_;
    static uint16_t tx_handle_;
    static uint8_t own_addr_type_;

    // Service
    static constexpr ble_uuid128_t svc_uuid = BLE_UUID128_INIT(
        0xf0, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );

    // RX
    static constexpr ble_uuid128_t rx_uuid = BLE_UUID128_INIT(
        0x01, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );

    // TX
    static constexpr ble_uuid128_t tx_uuid = BLE_UUID128_INIT(
        0x02, 0xde, 0xbc, 0x9a,
        0x78, 0x56, 0x34, 0x12,
        0x34, 0x12, 0xf0, 0xde,
        0xbc, 0x9a, 0x78, 0x56
    );
};