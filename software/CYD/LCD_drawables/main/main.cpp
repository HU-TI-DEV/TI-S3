#include "Ili9341Display.hpp"
#include "esp_log.h"
#include <esp_random.h> // for esp_random()

static const char* TAG = "MAIN";

extern "C" void app_main(void)
{
    Ili9341Display display(13, 14, 15, 2, -1, 27); // MOSI, SCLK, CS, DC, RST, BCKL (BL on GPIO 27, BL for CYD3.2 on GPIO 21)
    ESP_LOGI(TAG, "Init display");
    display.init();
    display.backlightOn(); // make sure the backlight is on
    // ESP_LOGI(TAG, "Starting diagnostics");
    // display.diagnostics(); // This works since in only uses the fillscreen method
    // display.diagnostics_drawables(); // Implement (all) primitives before you can call this method

    // Only the drawPixel method is implemented. 
    // This is a heavy task and you should do nothing like this in your main loop. Better to create a task.
    // This is for a demo only:
    display.fillScreen(display.rbg565(0, 0, 0)); // clear the screen
    while (true) {
        // Loop over all pixels
        for (int y = 0; y < Ili9341Display::HEIGHT; ++y) {
            for (int x = 0; x < Ili9341Display::WIDTH; ++x) {
                // Random RGB values [0..255]
                uint8_t r = esp_random() & 0xFF;
                uint8_t b = esp_random() & 0xFF;
                uint8_t g = esp_random() & 0xFF;

                uint16_t color = display.rbg565(r, b, g);
                display.drawPixel(x, y, color);
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        }

        // Small pause to prevent watchdog trigger
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
