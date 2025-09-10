# Code Style Richtlijnen (ESP-IDF v5.4)

Deze richtlijn is bedoeld voor projecten met **ESP32** en **ESP-IDF v5.4**, geschreven in **C++17**.  

---

## Projectstructuur

Een vaste projectstructuur helpt overzicht te houden en maakt samenwerken eenvoudiger.  

```
project-root/
├─ CMakeLists.txt                 # top-level project
├─ sdkconfig.defaults             # standaard instellingen
├─ components/
│  ├─ core/                       # generieke componenten
│  │  ├─ Logger.hpp
│  │  └─ Logger.cpp
│  ├─ drivers/                    # hardware wrappers (LCD, ADC, etc.)
│  │  ├─ Ili9341Display.hpp
│  │  └─ Ili9341Display.cpp
│  └─ app/                        # applicatielogica
│     ├─ Scene.hpp
│     └─ Scene.cpp
└─ main/
   ├─ CMakeLists.txt
   └─ main.cpp                    # startpunt van de applicatie
```

**Richtlijnen:**
- `.hpp` en `.cpp` bestanden staan in dezelfde map, geen aparte `include/` map.  
- `main/` bevat alleen de minimale opstartcode (`main.cpp`).  
- Eigenlijke logica gaat altijd in `components/`. Dit maakt code herbruikbaar en testbaar.  

---

## CMake Basis

CMake bepaalt welke bestanden gecompileerd worden en welke afhankelijkheden er zijn.  
Fouten in CMake zorgen vaak voor **“undefined reference”** of ontbrekende headers.

Top-level `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(my_app)
```

main/CMakeLists.txt:
```cmake
idf_component_register(SRCS "main.cpp"
                      REQUIRES drivers core app)
```

Component `components/drivers/CMakeLists.txt`:
```cmake
idf_component_register(
  SRCS "Ili9341Display.cpp"
  INCLUDE_DIRS "."
  REQUIRES esp_lcd driver freertos
)
```

**Richtlijnen:**
- Zet altijd `INCLUDE_DIRS "."` als `.hpp` en `.cpp` in dezelfde map staan.  
- Gebruik `REQUIRES` om afhankelijkheden van andere components of IDF-modules aan te geven.  
- Verwijder en herbouw (`idf.py fullclean build`) bij hardnekkige build-fouten.  

---

## Commentaar (Doxygen-stijl)

Goed commentaar maakt de code begrijpelijk en genereert automatisch documentatie met Doxygen.

Bestandshoofd:
```cpp
 /**
  * @file Ili9341Display.hpp
  * @brief Wrapper voor ILI9341 LCD driver.
  */
```

Klasse:
```cpp
 /**
  * @class Ili9341Display
  * @brief RAII-wrapper rond een ILI9341 LCD paneel.
  *
  * Voorbeeld:
  * @code
  * Ili9341Display lcd(13, 14, 15, 2, -1, 21);
  * lcd.init();
  * lcd.fillScreen(0xFFFF);
  * @endcode
  */
```

Functie:
```cpp
 /**
  * @brief Converteer RGB naar RGB565.
  * @param r waarde 0..255 (rood)
  * @param g waarde 0..255 (groen)
  * @param b waarde 0..255 (blauw)
  * @return 16-bit kleur in RGB565 formaat
  */
 constexpr uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) noexcept;
```

---

## Stijlregels

### Headers
- Voorkeur heeft **`#pragma once`** in plaats van include guards.  

### Constante waarden
- Gebruik **`constexpr`** in plaats van `#define`:
  constexpr int kStackSmall = 2048;

### Enumeraties
- Gebruik **`enum class`** voor type-veiligheid:
  enum class Button { UP, DOWN, LEFT, RIGHT, FIRE, NONE };

### Types
- Gebruik vaste breedte types (`uint32_t`, `int16_t`) voor voorspelbaarheid.  

### Exceptions
- Exceptions zijn meestal uitgeschakeld in embedded. Gebruik **`esp_err_t`** of een `Result<T>` struct.  

### Naamgeving
- Klassen/bestanden: `PascalCase` → `Ili9341Display.hpp`  
- Methoden/variabelen: `camelCase` → `initPanel()`  

  Blijf consequent in het hoofdlettergebruik van bestandsnamen. Ook bij je includes van headers. Het besturingssysteem waar je op werkt kan wel eens hoofdlettergevoelig zijn!

### Inclusie-volgorde
1. Eigen header `"Ili9341Display.hpp"`  
2. Project headers  
3. IDF headers `<esp_log.h>`  
4. STL headers `<array>`  

### Code opmaak

For indentation we will use the same formatting as used in the arduino IDE. 
In the arduino IDE you can force this by pressing ctrl+t. 

```cpp
void loop() {
  if (digitalRead(2) == HIGH) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
```

For VS code we need to change some settings.
Open Command Palette (ctrl+shift+p) → Preferences: Open User Settings (JSON) and add:

```cpp
{
  "editor.tabSize": 2,
  "editor.insertSpaces": true,
  "editor.detectIndentation": false
}
```

Save the file and restart VSCode.

Test it by opening a new cpp file and pressing the tab key. It should insert 2 spaces instead of a tab character.
You can also press Shift+Alt+F to automatically format your file. 


---

## FreeRTOS

FreeRTOS-taken kosten geheugen en CPU. Slecht gebruik leidt tot crashes of hoge latency.  

**Richtlijnen:**
- Maak **weinig taken**; gebruik queues of event groups voor communicatie.  
- Kies **stackgrootte bewust**; meet met `uxTaskGetStackHighWaterMark()`.  
- Gebruik `vTaskDelay()` in plaats van busy-loops.  

**Trampoline-patroon voor klassetaken:**
```cpp
 static void taskTrampoline(void* arg) {
     auto* self = static_cast<MyClass*>(arg);
     self->run();
 }
 xTaskCreate(&MyClass::taskTrampoline, "task", 4096, &obj, 5, nullptr);
```

---

## Fouten & Logging

Zonder goede logging is debugging bijna onmogelijk.

**Richtlijnen:**
- Gebruik duidelijke TAGs (`static const char* TAG = "Display";`).  
- Log context bij fouten:
  inline bool checkOk(esp_err_t err, const char* msg) {
      if (err != ESP_OK) {
          ESP_LOGE("APP", "%s (%s)", msg, esp_err_to_name(err));
          return false;
      }
      return true;
  }
- Gebruik `ESP_ERROR_CHECK_WITHOUT_ABORT` in plaats van `ESP_ERROR_CHECK` bij niet-kritieke fouten.  

---

## Geheugen

Microcontrollers hebben vaak beperkte RAM, verkeerd gebruik veroorzaakt instabiliteit.  

**Richtlijnen:**
- Vermijd `new`/`delete` in loops; gebruik statische of globale objecten.  
- Grote buffers alloceren met:
  uint8_t* buffer = (uint8_t*) heap_caps_malloc(size, MALLOC_CAP_DMA);
- Altijd vrijgeven in de destructor of via RAII (`std::unique_ptr`).  
- Voor constante data zoals tabellen of sprites: gebruik `constexpr` of `const` zodat ze in flash geheugen geplaatst worden.  
