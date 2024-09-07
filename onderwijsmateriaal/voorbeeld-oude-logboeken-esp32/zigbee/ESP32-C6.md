# ESP32-C6 Tips

## Key specs:

- Wifi of Zigbee (en?) of Bluetooth BLE

- Low power

- 1 core

## Belangrijke links:

[esp32-c6-devkitm-1 user-guide](https://docs.espressif.com/projects/espressif-esp-dev-kits/en/latest/esp32c6/esp32-c6-devkitm-1/user_guide.html)

# Zigbee

zigbee met esp32c6

install esp-idf 5.1

git-clone ergens:
git clone https://github.com/espressif/esp-zigbee-sdk.git

install de drivers van
https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads

idf.py set-target esp32c6

idf.py fullclean

Vreemd: dit keer wordt de Esp32-c6-DevkitM-1
niet gedetecteerd via de USBA naar USBC kabel
(zoals bij de ESP32-S3 nodig was),
maar werkt het via een USBC naar USBC kabel.

Voor eerste keer flashen, na inpluggen:
press-and-hold-boot
add press reset
release reset
release boot

Ik bouw zo esp_zigbee_HA_sample/Ha_on_off_light
en esp_zigbee_HA_sample/Ha_on_off_switch

idf.py -p COM3 flash monitor
idf.py -p COM4 flash monitor

Na het flashen zeggen beide terminals:
Waiting for download
Nadat je beide microcontrollers met de reset-knop
hebt gereset, werkt het.
Je kunt dan op de on_off switch microcontroller
de boot-knop indrukken. Dat toggelt dan de
led op de on_off_light microcontroller.

Opvallend: De samples hebben alleen een .c en een .h file.
De vraag is of .cpp ook zou compileren.

Andere belangrijke vragen zijn: 

* Wordt arduino-ide (als component) ondersteund?
* Is het compatible met mijn CleanRTOS overlay?
  (of eenvoudig zo te maken)

Ik kopieer nu test_lasergame naar / als subfolder
van de test_zig filder.

Vervolgens kopieer ik de esp-zigbee-sdk folder
content in die test_lasergame subfolder.
De components dir in die folder bevat nu dus:
arduino-esp32,
esp-zigbee-lib,
en esp-zigbee-ncp.
Maar de eerste van die 3 moet vervangen worden omdat 
ik nu ESP IDF 5.1 gebruik ipv 4.4:
Dus delete ik die folder, en type opnieuw in components:
git clone -b idf-release/v5.1 https://github.com/espressif/arduino-esp32.git

idf.py set-target esp32c6
Dan:
CMake Error at components/arduino-esp32/CMakeLists.txt:278 (message):
  esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)
  Dus handmatig in sdkconfig zetten:
CONFIG_FREERTOS_HZ=1000

Maar dan geeft hij na idf.py set-target esp32c6 
nog steeds dezelfde error.

Oplossing van iemand:
Temporarily changing the value from 100 to 1000 in components/cmakelists.txt solves the problem and menuconfig runs wtihout error.
After that change the parameter in menuconfig and save the sdkconfig file.
Lastly, revert cmakelists.txt file to its original state (i.e. undo the change you make)

Maar enfin, uit die cmakelist.txt file blijkt dat het slechts een foutmelding is,
waar verder niets mee gedaan wordt. Je kunt dus altijd naderhand sdkconfig nog als boven aanpassen.

Verder: lees ik op: https://github.com/espressif/esp-zigbee-sdk/blob/main/examples/esp_zigbee_HA_sample/HA_on_off_light/main/idf_component.yml

Dat je idf_component.yml kunt maken zodanig dat de components automatisch geinstalleerd worden:

## IDF Component Manager Manifest File

dependencies:
  espressif/esp-zboss-lib: "~1.1.0"
  espressif/esp-zigbee-lib: "~1.1.0"
  espressif/led_strip: "~2.0.0"

## Required IDF version

  idf:
    version: ">=5.0.0"

Verschillende perikelen om naar esp versie 5 te gaan spelen op, nu ik code probeer te hergebruiken:
https://github.com/lovyan03/LovyanGFX/issues/282

in esp-zigbee-lib idf_component_register toegevoegd:
REQUIRES espressif__esp-zboss-lib
en 
REQUIRES esp_timer
(geen idee of dat laatste iets uitmaakte)

Enfin, de code crasht omdat:
E (259) esp_timer: Task is already initialized

Probeersel: comment out esp_timer_init() in crt_MainInits.h
Yep, dat hielp.
HelloWorld van CleanRTOS werkt nu.

Ook bleek: in crt_Handler.h probeerde ik een uint32 te loggen met ESP_LOGI.
Maar daar moest dus %u ipv %d gebruikt worden (%d is voor ints), oh nee, dat is voor long uint.
Wat lijkt te bouwen is:
ESP_LOGI("Probleem", "Handler Delay too long in us:%"PRIu32, diffAll);
Die PRIu32 komt uit <inttypes.h> welke kennelijk niet nog eens expliciet geinclude hoeft te worden (gebeurt kennelijk al ergens).

en overal gpio_pad_select_gpio vervangen door esp_rom_gpio_pad_select_gpio

Bij AllWaitables.ino klaagt hij weer dat esp_timer_init() nog moet worden aangeroepen.
Toch maar weer terugzetten in class MainInits.
Maar dan krijg ik weer: E (260) esp_timer: Task is already initialized.. mmmm..

in esp idf 5.1, met target esp32-c6, krijg ik na:
esp_err_t err = esp_timer_create(&timer_args, &hTimer);
de error err == ESP_ERR_INVALID_STATE
NB: in de main functie roep ik esp_timer_init() aan.
En tijdens het opstarten krijg ik de warning:
W (159) clk: esp_perip_clk_init() has not been implemented yet

volgens chatgpt moet CONFIG_ESP_TIMER_ISR_AFFINITY_NO_AFFINITY enabled worden.
Maar eens idf.py menuconfig aanroepen, zodat sdkconfig geupdate wordt, en die variabele hopelijk erbij komt te staan.
Ik zie de setting niet.
Ik zet er maar handmatig bij: CONFIG_ESP_TIMER_ISR_AFFINITY_NO_AFFINITY=Y
Dat lijkt niet te helpen.
