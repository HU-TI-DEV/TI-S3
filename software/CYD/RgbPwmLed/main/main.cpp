/*! \brief PWM example for the connected RGB led on the CYD
 *
 *  This demonstrates brightness control for the LEDs using PWM.
 */
#include "PwmLed.hpp"
#include "RgbLed.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void rgbTestTask(void* pvParameter) {
  RgbLed* rgbLed = static_cast<RgbLed*>(pvParameter);
  while (true) {
    ESP_LOGI("RGBLED", "Executing rgbLed->test()");
    rgbLed->test();
    vTaskDelay(pdMS_TO_TICKS(1000));  // Wait for 1 second
  }
}

extern "C" void app_main(void) {
  static PwmLed redLed(GPIO_NUM_4, LEDC_CHANNEL_0,LEDC_TIMER_0);  
  static PwmLed blueLed(GPIO_NUM_16, LEDC_CHANNEL_1,LEDC_TIMER_1); 
  static PwmLed greenLed(GPIO_NUM_17, LEDC_CHANNEL_2,LEDC_TIMER_2); 
  static RgbLed rgbLed(&redLed, &greenLed, &blueLed);

  // Create task
  ESP_LOGI("MAIN", "Started running RGB LED test task");
  xTaskCreate(rgbTestTask, "LED Test Task", 2048, &rgbLed, 5, nullptr);
}
