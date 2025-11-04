#include "BleClient.hpp"

static constexpr const char* TAG = "MAIN";

extern "C" void app_main() {
    ESP_LOGI(TAG, "Started app_main()");

    static BleClient client;
    esp_err_t err = client.init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init BLE client: %s", esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "BLE client is running");

    // wait until BLE client is ready
    while (!client.isReady()){
        ESP_LOGI(TAG, "polling");
        vTaskDelay(pdMS_TO_TICKS(1000)); // start polling
    }

    ESP_LOGI(TAG, "BLE ready, Sending data");
    ESP_LOGI(TAG, "Noharm rules!");
    client.sendMessage("Noharm rules!\n");
}