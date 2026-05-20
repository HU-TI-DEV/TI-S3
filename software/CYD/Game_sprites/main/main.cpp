// Game_sprites main
#include "Ili9341Display.hpp"
#include "Scene.hpp"
#include "GameEntities.hpp"
#include "AnalogButtonReader.hpp"
#include "esp_log.h"

#define DIAGNOSTICS 1 // 0==off, 1==on

static const char* TAG = "MAIN";

/*
    Analog Keypad connection:
    VCC=red [GPIO21], GND=black, OUT=blue [GPIO35], we don't use the yellow [GPIO22] wire

    ------------------------------------------------

    ESP32-2432S028: Backlight is on GPIO21

    Nice side effect is that GPIO21 is usually HIGH.
    We can use this as the 5-button analog keypad VCC on P3
    (the plug cable color for this IO21 connection is red, very handy).

    ------------------------------------------------

    ESP32-2432S024: Backlight is on GPIO27

    NB: If we want to use P3 for the keypad connection on this CYD variant,
        we need to init and set IO21 to 'high', otherwise the keypad has no power.
*/

extern "C" void app_main(void)
{
    const int LCD_MOSI = 13;  ///< Master Out Slave In / Controller Out Peripheral In
    const int LCD_SCLK = 14;  ///< Serial Clock
    const int LCD_CS   = 15;  ///< Chip Select (active low)
    const int LCD_DC   =  2;  ///< Data/-Command indication
    const int LCD_RST  = -1;  ///< Reset
#ifdef DISPLAY28
    const int LCD_BL   = 21;  ///< Backlight pin for 2.8 inch display (large)
#else
    const int LCD_BL   = 27;  ///< Backlight pin for 2.4 inch display (smaller)
#endif

    // Create a display object and initialize the display
    Ili9341Display display(LCD_MOSI, LCD_SCLK, LCD_CS, LCD_DC, LCD_RST, LCD_BL);
    display.init();


#if DIAGNOSTICS
#ifdef DISPLAY28
    ESP_LOGI(TAG, "Display Configuration flag DISPLAY28 is set - CYD 2.8 inch display");
#else
    ESP_LOGI(TAG, "Display Configuration flag not set - CYD 2.4 inch display");
#endif

    ESP_LOGI(TAG, "Display Hardware COLOR TEST");
    for (int i = 0; i < 16; i++){
        uint16_t color = 1 << i;
        display.drawRectangle(i*20, 0, 19, 239, color, true);
        display.present();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelay(pdMS_TO_TICKS(14000));

    ESP_LOGI(TAG, "Display diagnostics");
    display.diagnostics();

    ESP_LOGI(TAG, "Display diagnostics_drawables");
    display.diagnostics_drawables();
    vTaskDelay(pdMS_TO_TICKS(5000)); //otherwise we don't see the shapes :-)
#endif // DIAGNOSTICS


    // Acquire the static player image (shark) and center it
    PlayerHandle player = acquirePlayerShark();
    centerPlayerShark(Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
    initPlayerSharkVelocity(20.0f, 10.0f);

    // Register the player with the scene (no ownership transfer)
    Scene scene;
    (void)scene.add(player.entity);
    scene.setInputTarget(player.input);

    // Create an object for the Analog keypad
    AnalogButtonReader buttons(ADC1_CHANNEL_7, GPIO_NUM_35, 200); // 200 ms poll interval
    buttons.setCallback([&](Button button){
        scene.onButton(button);
    });
    buttons.start();

    // Basic 30 FPS Game loop
    const int FPS = 30;
    const TickType_t frame = pdMS_TO_TICKS(1000 / FPS);
    ESP_LOGI(TAG, "Game loop starting (%d FPS)", FPS);
    TickType_t last = xTaskGetTickCount();
    while (true) {
        // Compute the delta time between frames ('dt') in miliseconds from the task tick counter value.
        // This allowes for accurate advancement of the simulation clock (see gameprogrammingpatterns.com).
        TickType_t now = xTaskGetTickCount();
        float dt = (now - last) * (portTICK_PERIOD_MS / 1000.0f);
        last = now;

        // Clear the framebuffer
        display.fillScreen(0x0000);  // black, we could also use 'display.rgb565(0,0,0)'
        // Simulate + draw
        // NB: Avoid logging in your Game Loop (logging is slow)
        // ESP_LOGI(TAG, "Update with delta t: %f", dt);
        scene.update(dt, Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
        scene.draw(display);
        // Transfer the framebuffer content to the display (=show it)
        display.present();

        vTaskDelay(frame);
    }
}