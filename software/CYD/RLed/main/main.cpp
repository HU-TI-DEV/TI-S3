/*! \brief Blink the connected RGB led on the CYD
 *
 *  The RGB Led is connected with pin 17,4 and 16 for setting blue, red and
 * green.
 */
#include "RLed.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "RGB";

extern "C" void app_main(void) {
  static RLed led(GPIO_NUM_4);  // Red, Green, Blue

  xTaskCreate(
      [](void*) {
        while (true) {
          ESP_LOGI(TAG, "Setting Red On...");
          led.redLedOn();
          vTaskDelay(pdMS_TO_TICKS(1000));
          ESP_LOGI(TAG, "Setting Red Off...");
          led.redLedOff();
          vTaskDelay(pdMS_TO_TICKS(1000));
        }
      },
      "led_task", 2048, nullptr, 5, nullptr);
}
