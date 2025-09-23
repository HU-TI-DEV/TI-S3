/*! \brief A analog reader class for reading a keypad
 *
 *  Make an analog reading from the ESP32 ADC 
 *  The anaolog "input only" GPIO 35 is used as input to read the analog keypad.
 */
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/adc.h"
#include <vector>
#include <functional>

enum class Button {
    NONE,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    FIRE
};

class AnalogButtonReader {
public:
    AnalogButtonReader(adc1_channel_t channel, gpio_num_t pin, uint32_t interval_ms);
    ~AnalogButtonReader();

    void start();
    void stop();

    void setCallback(std::function<void(Button)> callback);

private:
    adc1_channel_t adc_channel_;
    gpio_num_t gpio_pin_;
    uint32_t interval_ms_;
    TaskHandle_t task_handle_;
    bool running_;
    std::function<void(Button)> button_callback_;

    static void taskWrapper(void* pvParameters);
    void run();
    Button detectButton(int raw_adc);
};