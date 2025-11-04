#include "BLEServer.hpp"

extern "C" void app_main(void) {
    static BleServer server;

    if (server.init() == ESP_OK) {
        // BLE server is running in background task
        ESP_LOGI("MAIN", "BLE server is running");
        while (true) {
            vTaskDelay(pdMS_TO_TICKS(1000)); // keep running
        }
    }
}