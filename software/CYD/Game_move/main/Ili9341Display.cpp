/*! \brief Implementation for Ili9341 Display wrapper
 *
 *  This is a demonstration of a more game-loop-ready implementation of the display wrapper
 * 
 * In this version cusom init functions have been removed. Panel is setup trough esp_lcd_panel_* api.
 * Moving rectangle demonstration.
 * 
 */
#include "Ili9341Display.hpp"
#include "esp_log.h"

// REQUIRED for esp_lcd_panel_io_spi_config_t and related functions
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_interface.h" // full definition of esp_lcd_panel_t

Ili9341Display::Ili9341Display(int mosi, int sclk, int cs, int dc, int rst, int bl)
    : _mosi(mosi), _sclk(sclk), _cs(cs), _dc(dc), _rst(rst), _bl(bl) {}

Ili9341Display::~Ili9341Display() {
    if (backbuffer_) {
       heap_caps_free(backbuffer_);
       backbuffer_ = nullptr;
       backbuffer_len_ = 0;
   }
   backlightOff();
}

void Ili9341Display::init() {
    setupSPI();
    setupPanel();
    // Allocate full-screen backbuffer that we can use
    backbuffer_len_ = WIDTH * HEIGHT;
    backbuffer_ = static_cast<uint16_t*>(
        heap_caps_malloc(backbuffer_len_ * sizeof(uint16_t), MALLOC_CAP_DMA)
    );
    if (!backbuffer_) {
        ESP_LOGE(TAG, "Failed to allocate %d-byte backbuffer", (int)(backbuffer_len_ * sizeof(uint16_t)));
    } else {
        ESP_LOGI(TAG, "Backbuffer OK: %d bytes", (int)(backbuffer_len_ * sizeof(uint16_t)));
    }
    backlightOn();
}

void Ili9341Display::setupSPI() {
    //I have not been able to fix compiler warnings but the following works for the SPI bus configuration.
    spi_bus_config_t buscfg = {
        .mosi_io_num = _mosi,
        .miso_io_num = -1,
        .sclk_io_num = _sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = WIDTH * HEIGHT * 2 + 8
    };
    ESP_LOGI(TAG, "Setup SPI");
    ESP_ERROR_CHECK(spi_bus_initialize(_host, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = _cs,
        .dc_gpio_num = _dc,
        .spi_mode = 0,
        .pclk_hz = 30 * 1000 * 1000, // 30 MHz
        .trans_queue_depth = 10,
        .on_color_trans_done = NULL,
        .user_ctx = NULL,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8
    };
    ESP_LOGI(TAG, "Setup LCD panel io to SPI");
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(_host, &io_config, &_io));
}

void Ili9341Display::setupPanel() {
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = _rst,
        //.color_space = ESP_LCD_COLOR_SPACE_BGR,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };

    // Create raw panel object without auto init
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(_io, &panel_config, &_panel));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(_panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(_panel));

    // Landscape, origin top-left:
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(_panel, true));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(_panel, true, false)); // parameters are mirror_x and mirror_y
    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(_panel, 0, 0));  

    //invert color
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(_panel, 1));  

    ESP_LOGI(TAG, "ESP lcd panle setup is done.");
}

// A general function for pushing the frame to the LCD panel
void Ili9341Display::present() {
    // Push the backbuffer to the panel
    if (_panel) {
        esp_err_t err = esp_lcd_panel_draw_bitmap(_panel, 0, 0, WIDTH, HEIGHT, backbuffer_);
        vTaskDelay(pdMS_TO_TICKS(41)); // slight delay before new draw transfer is done. ToDo: implement a callback
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to draw bitmap: %s", esp_err_to_name(err));
        } /* else {
            ESP_LOGI(TAG, "Draw complete."); // temp disable log for beter performance
        } */
    } else {
        ESP_LOGE(TAG, "Panel is NULL");
    }
}

// The fillScreen can now use the present function. This function is reduced to filling a screen with a color. Use present function to fill the screen.
void Ili9341Display::fillScreen(uint16_t color) {
    if (!hasBuffer()) {
        ESP_LOGE(TAG, "Backbuffer not allocated");
        return;
    } else {
        // Fill the backbuffer
        for (int i = 0; i < (int)backbuffer_len_; ++i) {
            backbuffer_[i] = color;
        }
    }      
}

void Ili9341Display::backlightOn() {
    if (_bl >= 0) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << _bl),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        gpio_config(&io_conf);
        gpio_set_level(static_cast<gpio_num_t>(_bl), 1);
        ESP_LOGI(TAG, "Backlight turned on");
    }
}

void Ili9341Display::backlightOff() {
    if (_bl >= 0) {
        gpio_set_level(static_cast<gpio_num_t>(_bl), 0);
        ESP_LOGI(TAG, "Backlight turned off");
    }
}

/*! \brief convert 24-bit RGB into 16-bit RGB565 format
 *
 *  Apperently for the CYD it is RBG (confirmed for CYD3.2)
 */
uint16_t Ili9341Display::rbg565(uint8_t r, uint8_t b, uint8_t g) {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

void Ili9341Display::diagnostics() {
    uint16_t red     = rbg565(255, 0,   0);   // R=255, B=0,   G=0
    uint16_t green   = rbg565(0,   0,   255); // R=0,   B=0,   G=255
    uint16_t blue    = rbg565(0,   255, 0);   // R=0,   B=255, G=0

    ESP_LOGI(TAG, "Diagnostics Start");
    ESP_LOGI(TAG, "MOSI GPIO: %d", _mosi);
    ESP_LOGI(TAG, "SCLK GPIO: %d", _sclk);
    ESP_LOGI(TAG, "CS   GPIO: %d", _cs);
    ESP_LOGI(TAG, "DC   GPIO: %d", _dc);
    ESP_LOGI(TAG, "RST  GPIO: %d", _rst);
    ESP_LOGI(TAG, "BCKL GPIO: %d", _bl);

    if (_io) {
        ESP_LOGI(TAG, "SPI IO interface is initialized.");
    } else {
        ESP_LOGW(TAG, "SPI IO interface is NULL.");
    }

    if (_panel) {
        ESP_LOGI(TAG, "Panel object is initialized.");
    } else {
        ESP_LOGW(TAG, "Panel object is NULL.");
    }

    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGI(TAG, "Calling fillScreen with RED to test...");
    fillScreen(red);
    present(); // flush the backbuffer
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGI(TAG, "Calling fillScreen with GREEN to test...");
    fillScreen(green);
    present(); // flush the backbuffer
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGI(TAG, "Calling fillScreen with BLUE to test...");
    fillScreen(blue);
    present(); // flush the backbuffer
    vTaskDelay(pdMS_TO_TICKS(5000));
    
    // check which borders are addressed
    ESP_LOGI(TAG, "Calling fillScreen with black");
    fillScreen(rbg565(0, 0, 0)); // black
    vTaskDelay(pdMS_TO_TICKS(5000));

    drawLine(0, 0, WIDTH-1, 0, blue);                 // top (y=0)
    present();
    ESP_LOGI(TAG, "top (y=0)");
    vTaskDelay(pdMS_TO_TICKS(5000));

    drawLine(0, HEIGHT-1, WIDTH-1, HEIGHT-1, blue);   // bottom
    present();
    ESP_LOGI(TAG, "bottom");
    vTaskDelay(pdMS_TO_TICKS(5000));

    drawLine(0, 0, 0, HEIGHT-1, blue);              // left (x=0)
    present();
    ESP_LOGI(TAG, "left (x=0)");
    vTaskDelay(pdMS_TO_TICKS(5000));

    drawLine(WIDTH-1, 0, WIDTH-1, HEIGHT-1, blue);    // right
    present();
    ESP_LOGI(TAG, "right");
    vTaskDelay(pdMS_TO_TICKS(5000));

    //test backlight off
    backlightOff();
    ESP_LOGI(TAG, "Backlight off");

}

void Ili9341Display::diagnostics_drawables() {
    // please help me with these colors
    uint16_t red     = rbg565(255, 0,   0);   // R=255, B=0,   G=0
    uint16_t green   = rbg565(0,   0,   255); // R=0,   B=0,   G=255
    uint16_t blue    = rbg565(0,   255, 0);   // R=0,   B=255, G=0
    uint16_t yellow  = rbg565(255, 0,   255); // R=255, B=0,   G=255
    uint16_t orange  = rbg565(255, 0,   160); // R=255, B=0,   G=160
    // uint16_t white   = rbg565(255, 255, 255); // R=255, B=255, G=255

    std::vector<Drawable*> shapes = {
        new Line(10, 10, 120, 10, red),
        new Line(-10, 15, 330, 15, green), // out of bounds

        new Rectangle(10, 20, 60, 40, blue),
        new Rectangle(80, 20, 40, 40, yellow, true),

        new Square(10, 70, 30, red),
        new Square(50, 70, 30, green, true),

        new Circle(40, 130, 20, blue),
        new Circle(100, 130, 20, orange, true),

        new Triangle(10, 190, 50, 190, 30, 160, green),
        new Triangle(80, 190, 120, 190, 100, 160, red, true)
    };

    for (const auto& shape : shapes) {
        shape->draw(*this);
        present(); // after each shape is created we should present it
        delete shape;
    }
}

/*! \brief start of Drawing Primitives
 *
 *  drawPixel() Accesses panel trough backbuffer
 *  drawLine() Uses drawPixel() repeatedly  
 *  drawRectangle() Draws 4 lines or fills a region 
 *  drawSquare() inheritance from rectangel
 *  drawCircle() Uses Brensham's Circle Algorithm
 *  drawTriangle() Draws 3 lines or fills using scanlines 
 */
void Ili9341Display::drawPixel(int x, int y, uint16_t color) {
    if ((unsigned)x >= (unsigned)WIDTH || (unsigned)y >= (unsigned)HEIGHT) {
        // ESP_LOGE(TAG, "DrawPixel out of bounds");          
        return; // discard when out of bounds  
    }
    if (backbuffer_) {
        backbuffer_[y * WIDTH + x] = color;  // draw into backbuffer
    } else {
        ESP_LOGE(TAG, "No backbuffer. Can not perform draw."); // no fallback implemented but you could directly draw to panel like in previous examples.    
    }
}

void Ili9341Display::drawLine(int x0, int y0, int x1, int y1, uint16_t color) {
   // your code from the previous assignment
}

void Ili9341Display::drawRectangle(int x, int y, int w, int h, uint16_t color, bool fill) {
   // your code from the previous assignment
}

void Ili9341Display::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint16_t color, bool fill) {
   // your code from the previous assignment
}

/*! \brief draw circle with Brensham's Circle Algorithm
 *  Nice for Bart B. to chew on
 *  https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
 *
 */
void Ili9341Display::drawCircle(int x0, int y0, int r, uint16_t color, bool fill) {
   // your code from the previous assignment
}
// end of Drawing Primitives