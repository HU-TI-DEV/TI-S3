/*! \brief I2C Manager implementation
 *
 */

#include "I2CManager.hpp"

I2CManager::I2CManager(i2c_port_t port, gpio_num_t sda, gpio_num_t scl, uint32_t clk_speed)
    : i2c_port_(port), sda_pin_(sda), scl_pin_(scl), clock_speed_(clk_speed) {}

I2CManager::~I2CManager() {
    i2c_driver_delete(i2c_port_);
}

esp_err_t I2CManager::init() {
    i2c_config_t conf = {};
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sda_pin_;
    conf.scl_io_num = scl_pin_;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = clock_speed_;
    esp_err_t err = i2c_param_config(i2c_port_, &conf);
    if (err != ESP_OK) return err;

    return i2c_driver_install(i2c_port_, conf.mode, 0, 0, 0);
}

esp_err_t I2CManager::readRegister(uint8_t device_addr, uint8_t reg_addr, uint8_t* data, size_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port_, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t I2CManager::writeRegister(uint8_t device_addr, uint8_t reg_addr, const uint8_t* data, size_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port_, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    return ret;
}