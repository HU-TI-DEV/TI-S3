#include "Ili9341Display.hpp"
#include "Scene.hpp"
#include "GameEntities.hpp"
#include "AnalogButtonReader.hpp"
#include "esp_log.h"

static const char* TAG = "MAIN";

extern "C" void app_main(void)
{
    Ili9341Display display(13, 14, 15, 2, -1, 27); // MOSI, SCLK, CS, DC, RST, BCKL (BL on GPIO 27)
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