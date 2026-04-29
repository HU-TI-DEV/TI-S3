#include "Ili9341Display.hpp"
#include "Scene.hpp"
#include "GameEntities.hpp"
#include "AnalogButtonReader.hpp"
#include "esp_log.h"

#define DIAGNOSTICS 1 // 0==off, 1==on

static const char* TAG = "MAIN";

extern "C" void app_main(void)
{
    Ili9341Display display(13, 14, 15, 2, -1, 21);
    // MOSI, SCLK, CS, DC, RST, BackLight (BL on GPIO27->21 for ESP32-2432S028)

    // Nice side effect of BL on pin 21 is that GPIO21 is normally HIGH.
    // We can use this as the VCC for the 5-button analog keypad on P3
    // (the cable color for this connection is red, very handy).
    // Keypad VCC=red [GPIO21], GND=black, OUT=blue [GPIO35], we don't use the yellow [GPIO22] wire.

    display.init();

    Scene scene;

    // Acquire the static player shark and center it
    PlayerHandle player = acquirePlayerShark();
    centerPlayerShark(Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
    initPlayerSharkVelocity(20.0f, 10.0f);

    // Register with the scene (no ownership transfer)
    (void)scene.add(player.entity);
    scene.setInputTarget(player.input);

    // Analog keypad
    AnalogButtonReader buttons(ADC1_CHANNEL_7, GPIO_NUM_35, 200); // 200 ms poll
    buttons.setCallback([&](Button button){
        scene.onButton(button);
    });
    buttons.start();

#if DIAGNOSTICS
    ESP_LOGI(TAG, "Display diagnostics");
    display.diagnostics();
    ESP_LOGI(TAG, "Display diagnostics_drawables");
    display.diagnostics_drawables();
    vTaskDelay(pdMS_TO_TICKS(15000)); //otherwise we don't see the shapes :-)
    ESP_LOGI(TAG, "Color Bit Test");
    for (int i = 0; i < 16; i++){
        uint16_t color = 1 << i;
        // swap bytes (also done in rgb565 function)
        color = ((color & 0xFF) << 8) | ((color >> 8) & 0xFF);
        display.drawRectangle(i*20, 0, 19, 239, color, true);
    }
    display.present();
    vTaskDelay(pdMS_TO_TICKS(15000));
#endif // DIAGNOSTICS

     // Basic 30 FPS loop
    const int FPS = 30;
    const TickType_t frame = pdMS_TO_TICKS(1000 / FPS);
    TickType_t last = xTaskGetTickCount();

    ESP_LOGI(TAG, "Game loop starting");
    while (true) {
        TickType_t now = xTaskGetTickCount();
        float dt = (now - last) * (portTICK_PERIOD_MS / 1000.0f);
        last = now;

        // clear the screen. Using fillScreen should be faster.
        display.fillScreen(0x0000);  // black

        // Simulate + draw, avoid logging in your loop this is slow
        // ESP_LOGI(TAG, "Update with delta t: %f", dt);
        scene.update(dt, Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
        scene.draw(display);
        // Push the frame
        display.present();

        vTaskDelay(frame);
    }
}