#include "LDR.hpp"

extern "C" void app_main() {
    LDRSensor ldr(ADC1_CHANNEL_6, GPIO_NUM_34); // GPIO34 = ADC1_CHANNEL_6
    ldr.start();

    // Keep running
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
