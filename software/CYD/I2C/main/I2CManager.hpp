/*! \brief A class to manage I2C sensors on the ESP32
 *
 *  Supports adding multiple I2C sensors on the Cheap Yellow Display.
 *  SDA = GPIO21, SCL = GPIO22
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"

class I2CManager {
public:
    I2CManager(i2c_port_t port = I2C_NUM_0, gpio_num_t sda = GPIO_NUM_21, gpio_num_t scl = GPIO_NUM_22, uint32_t clk_speed = 100000);
    ~I2CManager();

    esp_err_t init();
    esp_err_t readRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t* data, size_t len);
    esp_err_t writeRegister(uint8_t device_addr, uint8_t reg_addr, const uint8_t* data, size_t len);

private:
    i2c_port_t i2c_port_;
    gpio_num_t sda_pin_;
    gpio_num_t scl_pin_;
    uint32_t clock_speed_;

    static constexpr const char* TAG = "I2CManager";
};
