// removed a lot of necessary stuff!!! Please student, fix it!



void LDRSensor::start() {
    if (!running_) {
        running_ = true;
        xTaskCreatePinnedToCore(taskWrapper, // again removed a lot of arguments... please student, fix it!);
    }
}

void LDRSensor::taskWrapper(void* pvParameters) {
    LDRSensor* sensor = static_cast<LDRSensor*>(pvParameters);
    sensor->run();
}

