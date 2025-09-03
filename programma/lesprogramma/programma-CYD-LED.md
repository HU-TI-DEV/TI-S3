# R(GB) Leds

## Voorbereiding
- Bestudeer het stuk over RGB Leds in [randomnerdtutorials.com](https://randomnerdtutorials.com/esp32-cheap-yellow-display-cyd-pinout-esp32-2432s028r/).
- Bestudeer de eerste 3 bladzijdes van de [espressif documentatie](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html) tot en met ```esp_err_t gpio_config(const gpio_config_t *pGPIOConfig)```.
- Bestudeer het type ```struct gpio_config_t``` in de [espressif documentatie](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html).
- Bestudeer de volgende [forum post](https://github.com/espressif/esp-idf/issues/285).

## Tijdens de les
Tijdens de les gaan we:
- naar de voorbeeld [code](../../software/CYD/RLed/) kijken. 
- de bronnen bestuderen bij [voorbereiding](#Voorbereiding). 
- aan de slag met de twee opdrachten! 

Er horen twee opdrachten bij dit onderwerp.  

### Opdracht I (RLed)
- aan de slag met de eerste voorbeeld [code](../../software/CYD/RLed/).
- maak voor een nieuw project altijd een nieuwe folder aan. In dit geval de (sub)folder ```Rled``` in je C:\espressif directory.
- kopieer de hele directory naar je C:\espressif directory zodat je de volgende structuur krijgt (in ```C:\espressif\RLed```):
```
├── main
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── RLed.cpp
│   └── RLed.hpp
├── CMakeLists.txt
└── sdkconfig                
```
-  om het werkend te krijgen moet je de RLed.cpp nog aanpassen. In de voorbeeld code is het stuk in RLed.cpp nog niet werkend, het zijn nu lege functies.
-  test het weer door ```idf.py -p com8 flash monitor``` te runnen in de RLed folder. 

Als het werkt:
- maak een foto van je CYD bordje terwijl de rode led aan is.
- maak een pdf van je RLed.cpp / plaats je project op je persoonlijke repo bijvoorbeeld onder /CYD/opdrachten

Nu gaan we nog wat onderzoek doen:
- in de RLed.hpp wordt de volgende file geinclude ```#include "driver/gpio.h"```. Zoek op je computer waar de ```gpio.h``` file staat opgeslagen. Als het goed is vind je meerdere plekken. Snap je waarom hij op meerdere plekken staat? Wat zouden de verschillen tussen de versies zijn? Bespreek je conclusies met een mede student en **schrijf je conclusies op in je logboek**.  
- open de gpio.h die op deze plek staat: ```C:\Espressif\esp-idf\components\esp_driver_gpio\include\driver``` Bestudeer het prototype van de functies: gpio_config en gpio_set_level 
- open de gpio.c die op deze plek staat: ```C:\Espressif\esp-idf\components\esp_driver_gpio\src```. Bestudeer de functie ```gpio_set_level```. Je ziet als het goed is dat de ```gpio_hal_set_level``` functie wordt aangeroepen. 
- open de wiki pagina over de [Hardware Abstraction Layer](https://en.wikipedia.org/wiki/Hardware_abstraction) en lees de alinea onder "In operating systems". **Probeer de 5 regels van de alinea in je eigen woorden op te schrijven in je logboek**.

### Opdracht II (RGBLed)
- we beginnen nu met andere voorbeeld [code](../../software/CYD/RgbLed/).
- kopieer deze ook weer naar je ```c:\espressif``` directory. 
- in deze code mist nog de RgbLed.cpp. 
- maak deze aan. 
- zorg dat hij mee gecompileert wordt door de CMakeLists.txt in de main folder aan te passen. Als je niet weet hoe dat moet, vraag het aan chatgpt (upload je CMakeLists.txt en vraag hoe je een file kan toevoegen).
- pas de RgbLed.cpp aan zodat hij de missende functies (configureGpio en setRgb) implementeert.    
- maak een foto van je CYD bordje terwijl de groene led aan is.
- maak een pdf van je RgbLed.cpp


## Na de les
- werk verder aan de opdrachten als je het nog niet af hebt. 

## Canvas

Voor beide opdrachten is een canvas entry, namelijk:
- ESP32 LED & PWM (deel 1 en 2)

Bestudeer de canvas opdracht om te zien wat je precies moet inleveren. 


