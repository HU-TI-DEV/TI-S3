# ESP32-project opzet, ESP32-IDF, Arduino component en CleanRTOS installatie

## Prependex Appendix: Bruikbare pinnen

Goed om te weten: van de meeste esp32 devkits zijn een stuk of 8 pinnen niet bruikbaar (zonder dat je een expert bent op esp32 gebied), omdat die voor interne taken / peripherals van de esp32 gebruikt kunnen worden. Een grappig voorbeeld is een esp32 devkit variant met extra veel pinnen. Echter, maar 1 of 2 van die extra pinnen zijn om dezelfde reden daadwerkelijk bruikbaar. Zoek dus altijd van tevoren goed uit welke pinnen van je ESP32 microcontroller je echt zonder kopzorgen kunt gebruiken.

## Eerst ESP32, dan Zigbee, ESP32-C6

(2024-09-07) Ik probeer nog eens de nieuwste versie van de ESP32-IDF (hedendage is dat 5.3.1) plus andere benodigdheden te installeren.

Eerst test ik dat met een gewone ESP32. Het zou dan ook moeten werken voor esp32-s2, s3 en c3.

Vervolgens een en ander upgraden voor zigbee en dat testen met een ESP32-C6.
(zigbee werkt alleen met een ESP32-C6 of ESP32-H2)

Ik open even een command prompt in admin mode en maak een folder aan voor dit experiment, en noem die: E:/HuDev/test_zig_2.

[deze pagina](https://github.com/espressif/esp-idf) raadt aan om versie 5.3 van de ESP-IDF te gebruiken, dus type ik:
cd E:\HuDev\test_zig_2
e:

git clone -b v5.3 --recursive https://github.com/espressif/esp-idf.git esp-idf-v5.3

cd esp-idf-v5.3
install.bat

Nu is het geinstalleerd. Om de windows paden en alles voor de huidige sessie goed te zetten, moet je voortaan na het openen van je command (ook voortaan) eerst op deze plek "export.bat" aanroepen.

export.bat

Nu alles goed staat, werkt de build-tool "idf.py"

idf.py --version
retourneert nu als het goed is "ESP-IDF v5.3".

Het zou handig zijn als je niet steeds na het openen van de command-prompt eerst naar die directory hoeft te gaan en export.bat in te typen.
Liever maak je een snelkoppeling naar een command prompt die dat automatisch doet:

- RMB(rechtermuisknop) op bureaublad of elders -> nieuwe snelkoppeling
- Gebruik als commando/location of the item : cmd.exe /k "E:\HuDev\test_zig_2\esp-idf-v5.3\export.bat"
- Kies als naam ESP-IDF 5.3 command prompt.
- (optioneel) Open de shortcut, en pin hem aan je taskbar.
- Open hem altijd "als administrator"

Okee, laten we even een snelle hello world test doen:
cd E:\HuDev\test_zig_2\esp-idf-v5.3\examples\get-started\hello_world
e:
(op deze locatie staat een van de test-projecten)

## De eerste keer bouwen

.. maar voordat je de eerste keer goed kunt bouwen, moeten er 2 dingen gebeurd zijn:

- (eenmalig, voor "altijd") USB-communicatie drivers installeren voor het devkit boardje dat je gebruikt. De volgende komen vaak voor:
  
  ```python
   - CP210x USB-to-UART driver (voor chips zoals CP2102/CP2104):
     https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
  
   - FTDI USB-to-UART driver (voor boards met FTDI-chips):
     https://ftdichip.com/drivers/
  
   - CH340/CH341 driver (voor sommige goedkope ESP32-boards):
     http://www.wch.cn/downloads/category/5.html
  ```

- (eenmalig, per project) de juiste build-target instellen voor dit project. het volgende commando laat de keuze zien:
  
  - idf.py --list-targets

- Vervolgens dus je microcontroller voor het project instellen. dus bijvoorbeeld voor een normale esp32: idf.py set-target esp32
  (de ingestelde esp32 zie je terug in de file sdkconfig, als je er in zoekt op "target")

- (elke keer, nadat je de microcontroller opnieuw in usb hebt geplugd):
  
  - Open de device manager. Kijk bij Ports(COM) welke com-port je devkit heeft.
    (in mijn voorbeeld blijkt dat COM8)

- elke (re-)build:
  
  - idf.py -p COM8 flash monitor 

de toevoeging 'flash' zorgt dat het ook wordt geflasht en de toevoeging 'monitor' zorgt ervoor dat een programma-tje wordt gestart welke je kunt vergelijken met Serial Monitor van de Arduino IDE.

Je kunt de monitor weer sluiten met: de "CTRL" + "]" toets-combinatie.

## nieuw project maken

Laten we eens zelf een nieuw project maken volgens het boekje.
We maken er eerst een folder voor aan (op willekeurige plek).
Ik kies:
cd E:\HuDev\test_zig_2
mkdir testproject
cd testproject
git clone https://github.com/espressif/esp-idf-template.git .

testen:
idf.py -p COM8 flash monitor 
(met de spatiebalk kun je de flow uit de monitor stil zetten)

Je zult zien dat er voor het bouwen automatisch een build subfolder wordt aangemaakt. Die is enorm groot. Standaard worden echter alleen verschillen met de vorige code opnieuw gebouwd. Dat scheelt tijd. Soms gaat iets daarbij mis. Met idf.py fullclean kun je dan de oude build opruimen, zodat de volgende netjes weer van scratch begint.

Enfin, in het algemeen wil je behalve je hoofd-applicatie ook allerlei test-applicaties makkelijk kunnen bouwen en testen, zonder dat voor elk weer zo'n joekel van een build-directory wordt aangelegd.

## lasergame template

Een handig uitgangspunt van je project is het onderstaande lasergame-template-project:

- Alles wordt gebouwd op dezelfde build folder, met dezelfde main file.
- De CleanRTOS libraries zijn toegevoegd, evenals enkele Arduino-IDE libraries.
- Het heeft voorbeeld applicaties in een apps subfolder, die het gebruik van CleanRTOS demonstreren en hoe iets zowel gebouwd kan worden in Arduino-IDE als in ESP-IDF.
- Het heeft een ClockPin class - welke superhandig is voor het schrijven van frequency-chopped communicaties zoals IR-communicatie.
- Voor de liefhebber is er ook support voor ILI-touchscreen displays (alleen is dat nog niet compatibel met zigbee).

Okee, dat project zet ik ook maar in dezelfde folder, dus:
cd E:\HuDev\test_zig_2
git clone https://github.com/themave/test_lasergame_2
cd test_lasergame_2

Nog even de huidige microcontroller instellen voor dit project, in mijn geval nu de normale esp32:

idf.py set-target esp32

Dat resulteert in een error:

<img src="images/2024-09-08-13-53-27-image.png" title="" alt="" width="520">

Voor compatibiliteit met de arduino IDE components moet de freertos periodieke timer  op 1000 HZ worden ingesteld (zodat VTaskDelay(1) 1 ms duurt ipv 10ms).

Ik pas dat handmatig aan in de sdkconfig file:

<img src="images/2024-09-08-13-56-02-image.png" title="" alt="" width="304">

Daarna is geen verdere actie nodig. Dus niet opnieuw set-target aan roepen - die vervangt sdkconfig weer terug..

Okee, verder met het project

Als de test_lasergame_2 folder nog geen components subfolder bevat, maken we die.
mkdir components
cd components

Vervolgens clonen we de arduino-ide component die compatibel is met ESP-IDF 5.3:

git clone -b idf-release/v5.3 https://github.com/espressif/arduino-esp32.git
cd ..

Vervolgens testen we even de bijbehorende WifiScan example, door dat sample in main.cpp te selecteren:

<img src="images/2024-09-08-13-11-15-image.png" title="" alt="" width="313">

**VScode**

```
Ik kan daarbij VSCode aanbevelen. Gebruik dat voor al je c++ code editing.
Open een folder - in mijn geval de bovenste folder waar alles in zit: 
E:\HuDev\test_zig_2
```

Enfin, WifiScan bouwen:
idf.py -p COM8 flash monitor 

.. resulteert in een error:

![](images/2024-09-08-13-12-40-image.png)

Dat is iets wat nog niet is geupdate voor versie 5.3. Typsich nog zoiets dat je krijgt als je de laatste versie gebruikt. Wat dat betreft hadden we beter de voorlaatste versie van ESP-IDF kunnen gebruiken.

Enfin, in uart.h ontbreekt dus nog een flags variabele in de klasse uart_config_. We checken eerst in die esp32-hal-uart.c file even welk type hij verwacht.

In VSCode zien we op die regel:
<img src="images/2024-09-08-13-33-26-image.png" title="" alt="" width="546">
idf.py --version  retourneert 5.3, en ik heb de 5.3. versie voor de arduino ide toestand geinstalleerd. Het lijkt dus een nieuwe bug. Op stack overflow en google kan ik er niets over vinden. Enfin, dan voeg ik de ontbrekende members zelf maar even toe.
Via RMB (right mouse button) op die uart_config vraag ik VSCode "Go to declaration" om de klassedeclaratie te vinden.
Dit is em kennelijk:
![](images/2024-09-08-13-36-49-image.png)

Dus even zelf flags subdeel toevoegen:
<img src="images/2024-09-08-13-39-19-image.png" title="" alt="" width="551">

Okee, de WifiScan applicatie runt nu, maar in de monitor verschijnt:

<img src="images/2024-09-08-18-35-05-image.png" title="" alt="" width="529">

Vervolgens deze tip van stack overflow toegepast:

`` unselect Wifi nvs enabled in menuconfig ,component config -> Wifi -> Wifi NVS Flash``

Vervolgens werkte het. De ene ESP32 vond meestal niets, en af en toe een zwak signaal. Dat komt omdat het er eentje is waar een antenne op geschroefd dient te worden. Een andere ESP32 (met ingebouwde antenne) vond een hele reeks providers. 

Ook een aardige test (van CleanRTOS) kun je doen, door in main "#include <AllWaitables.ino>" uit te commentariëren en daarmee te bouwen.
(Die test heeft een button met pulldown-weerstand nodig aan pin23).

Een andere leuke test, als je een ILI-touchscreen hebt aangesloten, kun je doen door in main uit te commentarieren: #include <TouchscreenButton.ino> of #include <TouchscreenButtonGroup.ino>

littleFS lijkt nog niet te werken. misschien idf53 compatible variant ervan installeren oid.

### Zigbee

Enfin, voor IDF5.1 heb ik in een ander log al zigbee getest. voor IDF5.3 gaat het vast vergelijkbaar, dus zie [ESP32-C6.md op S3 github](https://github.com/HU-TI-DEV/TI-S3/blob/main/onderwijsmateriaal/voorbeeld-oude-logboeken-esp32/zigbee/ESP32-C6.md).