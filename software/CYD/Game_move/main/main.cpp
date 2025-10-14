#include "Ili9341Display.hpp"
#include "esp_log.h"

static const char* TAG = "MAIN";

extern "C" void app_main(void)
{
    Ili9341Display display(13, 14, 15, 2, -1, 27); // MOSI, SCLK, CS, DC, RST, BCKL (BL on GPIO 27)
    display.init();
    //ESP_LOGI(TAG, "Starting diagnostics");
    //display.diagnostics();
    //display.diagnostics_drawables();
    
    uint16_t black = display.rbg565(0, 0, 0);
    uint16_t red = display.rbg565(255, 0, 0);

    MovingRect box(40.f, 40.f, 24, 24, red, 120.f, 90.f); // create an entity

    // let it move based on time
    int64_t prev = esp_timer_get_time();
    ESP_LOGI(TAG, "Starting game-loop");
    while (true) {
        const int64_t now = esp_timer_get_time();
        float dt = float(now - prev) / 1'000'000.f;
        prev = now;
        if (dt > 0.1f) dt = 0.1f; // clamp long stalls

        // Update and Draw and Present
        box.update(dt, Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
        display.fillScreen(black);
        box.draw(display);
        display.present();

        vTaskDelay(pdMS_TO_TICKS(33)); // about 30 FPS
    }

}