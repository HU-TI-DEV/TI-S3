#include "I2CManager.hpp"

static const char* TAG = "MAIN";

extern "C" void app_main() {
    I2CManager i2c;
    if (i2c.init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize I2C");
        return;
    }

    uint8_t chip_id = 0;
    if (i2c.readRegister(0x76, 0xD0, &chip_id, 1) == ESP_OK) {
        ESP_LOGI(TAG, "BME280 Chip ID: 0x%02X", chip_id); // 0x60 represents BME 280
    } else {
        ESP_LOGE(TAG, "Failed to read BME280 chip ID");
    }

    // Keep running
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}