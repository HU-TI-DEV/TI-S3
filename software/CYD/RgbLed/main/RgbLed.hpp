#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <array>

class RgbLed {
public:
    enum class Color {
        OFF,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,
        MAGENTA,
        WHITE
    };

    RgbLed(gpio_num_t red, gpio_num_t green, gpio_num_t blue)
        : red_pin(red), green_pin(green), blue_pin(blue) {
        configureGpio(red_pin);
        configureGpio(green_pin);
        configureGpio(blue_pin);
        setColor(Color::OFF);
    }

    void setColor(Color color) {
        switch (color) {
            case Color::OFF:
                setRgb(true, true, true); break;
            case Color::RED:
                setRgb(false, true, true); break;
            case Color::GREEN:
                setRgb(true, false, true); break;
            case Color::BLUE:
                setRgb(true, true, false); break;
            case Color::YELLOW:
                setRgb(false, false, true); break;
            case Color::CYAN:
                setRgb(true, false, false); break;
            case Color::MAGENTA:
                setRgb(false, true, false); break;
            case Color::WHITE:
                setRgb(false, false, false); break;
        }
    }

private:
    gpio_num_t red_pin;
    gpio_num_t green_pin;
    gpio_num_t blue_pin;

    void configureGpio(gpio_num_t pin);

    void setRgb(bool r, bool g, bool b);  
};
