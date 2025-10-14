#pragma once

#include "esp_err.h"
#include "esp_log.h"

class RgbLed {
 private:
  PwmLed* red;
  PwmLed* green;
  PwmLed* blue;

 public:
  RgbLed(PwmLed* red, PwmLed* green, PwmLed* blue)
      : red(red), green(green), blue(blue) {}
  void test() {
    red->setDuty(100);
    green->setDuty(10);
    blue->setDuty(30);
  }
};