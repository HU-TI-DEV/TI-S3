/*! \brief ADC reading analog buttons implementation
 *
 *  Make an analog reading from an analog keypad with 5 buttons
 *  ToDo: some keypresses seem to be missed no raw value is registered....
 */
#include "AnalogButtonReader.hpp"

static const char* TAG = "AnalogButtonReader";

// Thresholds must match with actual hardware values! Use the ADC example to find raw values.
struct ButtonThreshold {
    int min;
    int max;
    Button button;
};

static const std::vector<ButtonThreshold> button_thresholds = {
    // your code from previous exercise 
};

AnalogButtonReader::AnalogButtonReader(adc1_channel_t channel, gpio_num_t pin, uint32_t interval_ms)
    : adc_channel_(channel), gpio_pin_(pin), interval_ms_(interval_ms),
      task_handle_(nullptr), running_(false), button_callback_(nullptr) {

    adc1_config_width(ADC_WIDTH_BIT_11);
    adc1_config_channel_atten(adc_channel_, ADC_ATTEN_DB_12);
}

AnalogButtonReader::~AnalogButtonReader() {
    stop();
}

void AnalogButtonReader::start() {
    if (!running_) {
        running_ = true;
        xTaskCreatePinnedToCore(taskWrapper, "AnalogButtonTask", 4096, this, 5, &task_handle_, 1);
    }
}

void AnalogButtonReader::stop() {
    if (running_) {
        running_ = false;
        if (task_handle_) {
            vTaskDelete(task_handle_);
            task_handle_ = nullptr;
        }
    }
}

void AnalogButtonReader::setCallback(std::function<void(Button)> callback) {
    button_callback_ = callback;
}

void AnalogButtonReader::taskWrapper(void* pvParameters) {
    AnalogButtonReader* reader = static_cast<AnalogButtonReader*>(pvParameters);
    reader->run();
}

void AnalogButtonReader::run() {
    Button lastButton = Button::NONE;

    while (running_) {
        int raw = adc1_get_raw(adc_channel_);
        Button currentButton = detectButton(raw);

        if (currentButton != lastButton) {
            // ESP_LOGI(TAG, "Button Changed: %d (ADC Raw: %d)", static_cast<int>(currentButton), raw);
            lastButton = currentButton;
            if (button_callback_) {
                button_callback_(currentButton);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(interval_ms_));
    }
}

Button AnalogButtonReader::detectButton(int raw_adc) {
    for (const auto& threshold : button_thresholds) {
        if (raw_adc >= threshold.min && raw_adc <= threshold.max) {
            return threshold.button;
        }
    }
    return Button::NONE;
}