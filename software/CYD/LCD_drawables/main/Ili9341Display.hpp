/*! \brief Headerfile for Ili9341 Display wrapper
 *
 *  Basic drawing primitives
 */
#pragma once

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_ili9341.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_heap_caps.h" // for heap_caps_malloc

#include "Line.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include <vector>

class Ili9341Display {
public:
    Ili9341Display(int mosi, int sclk, int cs, int dc, int rst, int bl);
    ~Ili9341Display();

    // CYD in landscape: 320x240
    static constexpr int WIDTH = 320;
    static constexpr int HEIGHT = 240;

    void init();
    void fillScreen(uint16_t color);
    void backlightOn();
    void backlightOff();
    void diagnostics();
    void diagnostics_drawables();
    uint16_t rbg565(uint8_t r, uint8_t b, uint8_t g);

    // Drawing Primitives
    void drawPixel(int x, int y, uint16_t color);
    void drawLine(int x0, int y0, int x1, int y1, uint16_t color);
    void drawRectangle(int x, int y, int w, int h, uint16_t color, bool fill = false);
    void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color, bool fill = false);
    void drawCircle(int x, int y, int radius, uint16_t color, bool fill = false);

private:
    static constexpr const char* TAG = "Drawables";

    void setupSPI();
    void setupPanel();

    int _mosi, _sclk, _cs, _dc, _rst, _bl;
    spi_host_device_t _host = SPI2_HOST;
    esp_lcd_panel_io_handle_t _io = nullptr;
    esp_lcd_panel_handle_t _panel = nullptr;
};