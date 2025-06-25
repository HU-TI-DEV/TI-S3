#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <array>

class RLed {
public:
    RLed(gpio_num_t red)
        : red_pin(red) {
        configureGpio(red_pin);
        redLedOn();
    }

    void redLedOn();
    void redLedOff();

private:
    gpio_num_t red_pin;
    void configureGpio(gpio_num_t pin);
};
