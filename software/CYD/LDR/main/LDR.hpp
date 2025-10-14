/*! \brief A analog reader class for reading the LDR
 *
 *  Make an analog reading from the ESP32 ADC 
 *  The LDR is connected to GPIO 34
 * 
 *  TODO: should use adc_oneshot
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/adc.h"

class LDRSensor {
public:
    LDRSensor(adc1_channel_t channel, gpio_num_t pin, uint32_t read_interval_ms = 1000);
    ~LDRSensor();

    void start();
    void stop();

private:
    static void taskWrapper(void* pvParameters);
    void run();

    adc1_channel_t adc_channel_;
    gpio_num_t gpio_pin_;
    TaskHandle_t task_handle_;
    uint32_t read_interval_ms_;
    bool running_;

    static constexpr const char* TAG = "LDRSensor";
};
