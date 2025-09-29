/*! \brief Headerfile for Ili9341 Display wrapper
 * A series of projects to create a basic game-loop. Based on ./LCD/Drawables example code.
 *
 *  - Let the primitives make use of the backbuffer
 *  - Added a present() function to flus backbuffer to the screen
 *  - Added a Moving rectangle.
 *  - Added analog key input
 * 
 *  Use a backbuffer to reduce flickering, present the whole frame at once, and smooth motion (when combined with frame timer)
 * 
 * Implements key input that can move an entity.
 */
#pragma once

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_ili9341.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_heap_caps.h" // for heap_caps_malloc
#include "esp_timer.h" // for esp_timer_get_time for fine grain timing

#include "Line.hpp"
#include "Rectangle.hpp"
#include "Square.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include <vector>

// #include "MovingRect.hpp"

class Ili9341Display {
public:
    Ili9341Display(int mosi, int sclk, int cs, int dc, int rst, int bl);
    ~Ili9341Display();

    // CYD in landscape: 320x240, different for CYD versions....
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
    // Drawing bitmaps
    void drawBitmapRGB565(int x, int y, int w, int h, const uint8_t* src);
    void drawBitmapRGB565(int x, int y, int w, int h, const uint16_t* src16);

    void present(); // push the backbuffer to the LCD panel
private:
    static constexpr const char* TAG = "Game_move";

    void setupSPI();
    void setupPanel();

    int _mosi, _sclk, _cs, _dc, _rst, _bl;
    spi_host_device_t _host = SPI2_HOST;
    esp_lcd_panel_io_handle_t _io = nullptr;
    esp_lcd_panel_handle_t _panel = nullptr;

    // For the backbuffer
    uint16_t* backbuffer_ = nullptr;     // WIDTH * HEIGHT entries
    size_t    backbuffer_len_ = 0;       // number of uint16_t entries

    inline bool hasBuffer() const { return backbuffer_ != nullptr; }
};