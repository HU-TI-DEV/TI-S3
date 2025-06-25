/*! \brief PWM example for the connected RGB led on the CYD
 *
 *  This demonstrates brightness control for the LEDs using PWM.
 */
#include "PwmLed.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

// C++ FreeRTOS task function to fade LED
void ledFadeTask(void* pvParameter) {
    PwmLed* led = static_cast<PwmLed*>(pvParameter);

    led->start();
    while (true) {
        for (int i = 0; i <= 100; ++i) {
            led->setDuty(i);
            vTaskDelay(pdMS_TO_TICKS(20));
        }

        for (int i = 100; i >= 0; --i) {
            led->setDuty(i);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Starting PWM LED example with FreeRTOS task...");

    static PwmLed redLed(GPIO_NUM_4, LEDC_CHANNEL_0, LEDC_TIMER_0); // Pin 4 connected to the Red Led

    // Create task
    xTaskCreate(ledFadeTask, "LED Fade Task", 2048, &redLed, 5, nullptr);
}
