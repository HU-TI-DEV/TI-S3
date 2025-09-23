#include "AnalogButtonReader.hpp"

static const char* TAG = "MAIN";

extern "C" void app_main() {
    // Analog keypad
    AnalogButtonReader buttons(ADC1_CHANNEL_7, GPIO_NUM_35, 200); // 200 ms poll

    buttons.setCallback([&](Button button){ // How do we call this function and why do we use it here?
        //switch (button) {
            // implement this switch case
        //}
    });
    buttons.start();

    // Keep running
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}