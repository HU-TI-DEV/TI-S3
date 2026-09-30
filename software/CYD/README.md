# CYD - Hardware Variants

"Cheap Yellow Display"

> Note: The color-fix has been applied to the ESP32-project `Game_sprites`.\
> You can select the 2.8 or 2.4 inch display variant in the file\
> `Game_sprites/components/ili9341_display/Ili9341Display.hpp`

## ESP32-2432S028 (2.8 inch)

[AliExpress-Link](https://nl.aliexpress.com/item/1005009214166473.html)

- ESP32 variant "sparkle IoT":
  - Model XH32-S
  - WiFi+BT N4XX
- Display: 2.8 inch with resistive touchscreen
  - ILI9341 display controller
  - Backlight-pin: **IO21**
  - Color: not inverted
  - Color bit-order:
    - `FEDCBA9876543210` - bit position
    - `gggRRRrrBBBbbGGG` - color
    - -> this is byte-swapped *BGR*
    - -> we can use the RGB bit order if we set the display driver to BGR
- R21: LDR on front side
- LED1: RGB LED on back side
- RST button (black)
- BOOT button (black)
- Connectors:
  - USB1: USB-micro port for programming
  - USB2: USB-C port for general use/power
  - P1 (4pin): Vin/TX/RX/GND
  - CN1 (4pin): GND/IO22/IO27/3.3V
  - P3 (4pin): GND/IO35/IO22/IO21
  - P4 (2pin): SPK - Speaker 2 pin

Terminal output (your MAC address is different!):

```text
Chip is ESP32-D0WD-V3 (revision v3.1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: ec:e3:34:1f:01:70
```
  
## ESP32-2432S024 (2.4 inch)

[AliExpress-Link](https://nl.aliexpress.com/item/1005009897766961.html)

- ESP32 variant:
  - Model CS-32
  - WiFi+BT N4XX
- Display 2.4 inch LI435-2.4 with resistive touchscreen
  - ILI9341 display controller
  - Backlight-pin: **IO27**
  - Color: **inverted**
  - Color bit-order (when tested with LCD_RGB_ELEMENT_ORDER_RGB settings):
    - `FEDCBA9876543210` - bit position
    - `ggxBBBbbRRRrrGGG` - color (x=grey)
    - -> this is byte-swapped *RGB*
- LED1: RGB LED on **front** side
- R21: LDR on front side
- SW1 switch (power-on from battery?)
- RST button (white)
- BOOT button (white)
- Connectors:
  - USB: USB-C port for programming/general use/power
  - P1 (4pin): +5V/TX/RX/GND
  - BAT (2pin): +/- for LiPo-battery?
  - SPEAK (2pin): Speaker 2 pin
  - CN1 (4pin): GND/IO22/IO21/3.3V
  - P3 (4pin): GND/IO35/IO22/IO21

Terminal output (your MAC address is different!):

```text
Chip is ESP32-D0WD-V3 (revision v3.1)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 5c:01:3b:8a:38:80
```
  