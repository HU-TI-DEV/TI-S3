/*! \brief Blink the connected RGB led on the CYD
 *
 *  The RGB Led is connected with pin 17,4 and 16 for setting blue, red and green.
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "RgbLed.hpp"
#include "esp_log.h"

static const char* TAG = "RGB";

extern "C" void app_main(void) {
    static RgbLed led(GPIO_NUM_4, GPIO_NUM_17, GPIO_NUM_16);  // Red, Green, Blue

    xTaskCreate([](void*){
        RgbLed::Color colors[] = {
            RgbLed::Color::RED,
            RgbLed::Color::GREEN,
            RgbLed::Color::BLUE,
            RgbLed::Color::CYAN,
            RgbLed::Color::MAGENTA,
            RgbLed::Color::WHITE,
            RgbLed::Color::OFF
        };

        while (true) {
            for (auto color : colors) {
                ESP_LOGI(TAG, "Setting different color...");
                led.setColor(color);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
    }, "led_task", 2048, nullptr, 5, nullptr);
}
