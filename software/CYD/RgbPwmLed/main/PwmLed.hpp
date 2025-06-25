/*! \brief PWM Class for RGB led on the CYD
 *
 *  The RGB Led is connected with pin 17,4 and 16 for setting blue, red and green.
 *  It uses PWM to adjust Led brightness.
 * 
 *  For IDF version 5.4
 */
#pragma once

#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_log.h"

class PwmLed {
public:
    PwmLed(gpio_num_t pin, ledc_channel_t channel, ledc_timer_t timer)
        : m_pin(pin), m_channel(channel), m_timer(timer), m_maxDuty(8191) {
        init();
    }

    void setDuty(uint8_t percent) {
        if (percent > 100) percent = 100;
        uint32_t duty = ((100-percent) * m_maxDuty) / 100;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, m_channel, duty);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, m_channel);
    }

    void start() {
        setDuty(0);
    }

    void stop() {
        ledc_stop(LEDC_HIGH_SPEED_MODE, m_channel, 0);
    }

private:
    gpio_num_t m_pin;
    ledc_channel_t m_channel;
    ledc_timer_t m_timer;
    uint32_t m_maxDuty;

    void init() {
        ledc_timer_config_t ledc_timer = {
            .speed_mode = LEDC_HIGH_SPEED_MODE, // timer mode
            .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
            .timer_num = m_timer, // timer index
            .freq_hz = 5000, // frequency of PWM signal                   
            .clk_cfg = LEDC_AUTO_CLK,
            .deconfigure = false
        };

        ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

        ledc_channel_config_t ledc_channel = {
            .gpio_num = m_pin,
            .speed_mode = LEDC_HIGH_SPEED_MODE,
            .channel = m_channel,
            .intr_type = LEDC_INTR_DISABLE,
            .timer_sel = m_timer,
            .duty = 0,
            .hpoint = 0,
            .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
            .flags = {
                .output_invert = 0  // Set to 1 if you want inverted output
            }
        };
        
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    }
};