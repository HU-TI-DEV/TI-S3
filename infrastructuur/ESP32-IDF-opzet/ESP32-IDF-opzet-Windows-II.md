# ESP32-project opzet, ESP32-IDF, Arduino component en RTOS installatie deel II <!-- omit in toc -->

<!-- TOC -->
- [Introductie](#introductie)
- [Arduino library voorbeelden](#arduino-library-voorbeelden)
	- [WifiScan.ino](#wifiscanino)
	- [AnalogRead.ino](#analogreadino)
<!-- /TOC -->

# Introductie
In deze MD file gaan we aan de slag met een aantal voorbeelden voor de ESP32.  
We gaan ervanuit dat je de voorbeelden uitprobeert op een simpele ESP32 (ik heb het getest met de ESP32-WROOM-32D).

**Deze voorbeelden gaan er vanuit dat je de export.bat hebt uitgevoerd, het esp-target hebt geset en dat je ook al de CONFIG_FREERTOS_HZ op 1000 hebt gezet. Is dit niet het geval? Bekijk [hier](./ESP32-IDF-opzet-Windows.md) hoe je dat doet.**

# Arduino library voorbeelden

## WifiScan.ino

Kopieer de inhoud van `main_for_wifi_scan_ard_ide_with_nvs.cpp` naar `main.cpp`

```
├── main
│   ├──  CMakeLists.txt
│   ├──  CMakeLists_for_zigbee.txt
│   ├──  component.mk
│   ├──  idf_component.yml
│   ├──  idf_component_for_zigbee.yml
│   ├──  Kconfig.projbuild
│   ├──  main.cpp
│   ├──  main_for_wifi_scan_ard_ide_with_nvs.cpp
│   └──  main_normal_no_nvs_backup.cpp
```
Zoals je ziet in de `main.cpp` is het volgende voorbeeld geselecteerd:
```c++
// **** Arduino IDE Examples ****
#include <WifiScan.ino>
//#include <WiFiAccessPoint.ino>
//#include <AnalogRead.ino>
```
Run het voorbeeld met:
```bash
...\S3-Template>idf.py flash monitor
```

Dit zou het volgende moeten geven (maar dan met andere netwerken):
![alt text](./images/screenshot_WifiScan.png)

Gaaf he!!  
**Sla dit screenshot op in je logboek**

## AnalogRead.ino

Kopieer de inhoud van `main_for_wifi_scan_ard_ide_with_nvs.cpp` naar `main.cpp`

Verander de `main.cpp` zodat het AnalogRead.ino voorbeeld is geselecteerd:
```c++
// **** Arduino IDE Examples ****
//#include <WifiScan.ino>
//#include <WiFiAccessPoint.ino>
#include <AnalogRead.ino>
```

AnalogRead.ino is te vinden in de dir: 
```bash
...\S3-Template\components\arduino-esp32\libraries\ESP32\examples\AnalogRead
```

Als we die openen zien we:

``` c++
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  //set the resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // read the analog / millivolts value for pin 2:
  int analogValue = analogRead(2);
  int analogVolts = analogReadMilliVolts(2);

  // print out the values you read:
  Serial.printf("ADC analog value = %d\n", analogValue);
  Serial.printf("ADC millivolts value = %d\n", analogVolts);

  delay(100);  // delay in between reads for clear read from serial
}
```

Run het voorbeeld met:
```bash
...\S3-Template>idf.py flash monitor
```

Klopt de output met wat je had verwacht?
**Sla dit screenshot op in je logboek**

