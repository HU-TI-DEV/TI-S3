# Programma ESP32 IDF en CleanRTOS installeren

Deze les gaan we de ESP32 IDF programmeeromgeving installeren, (team-)project voor de code aanmaken.
### Logboek bijhouden, Canvas opdracht
Start een nieuw kopje in je persoonlijk logboek, bijvoorbeeld genaamd "ESP32 IDF Installatie".
Houdt tijdens het proces goed bij in je logboek wat je leert, waar je tegenaan loopt en hoe je het oploste.
Een mooi 'bewijs' van een succesvolle installatie is een screenshot nadat je de "dump log" button hebt ingedrukt tijdens het CleanRTOS testprogramma "AllWaitables.ino".
Lever na een succesvolle installatie en test bij de Canvas opdracht "ESP32 IDF Installatie" de link in naar dat kopje in je logboek (dus bijvoorbeeld https://github.com/bla/persoonlijk_logboek.md#esp-idf-installatie).

## Voorbereiding
- Lees eventueel alvast wat in [ESP32-IDF-opzet](../../infrastructuur/ESP32-IDF-opzet/ESP32-IDF-opzet.md).
- Als je team een zigbee mesh gaat gebruiken, lees dan vervolgens wat in [ESP32-C6, Zigbee](../../onderwijsmateriaal/
voorbeeld-oude-logboeken-esp32/zigbee/ESP32-C6.md)
- Neem voor de zekerheid mee:
    - Een breadboard
    - Een drukknopje
    - Een weerstand van 1 a 2 kOhm
    - Een 470uF condensator
    - Een 100nF condensator
    - Een snoer waarmee je je laptop aan usbc kunt verbinden
    - Een snoer waarmee je je laptop aan micro-usb kunt verbinden
- Bereid je voor op wat chaos - en probeer alvast wat geduld te reserveren.
  Dit soort dingen gaan zelden in 1x goed.

## Tijdens en na de les
### Begin van de les
Je krijgt aan het begin van de les van Harm de ieder een of meerdree ESP32 chips:
(Mits Harm dat goedvindt - nog even checken)
- Ieder lid van een **rollatornavigatieteam** krijgt **één ESP32-S3**
  (laatste versie: sneller - ivm mogelijk cameragebruik - maar mogelijk minder 
   compatible met bestaande libraries en kinderziektes)
- Ieder lid van een **winkelverlichtingteam met zigbee-mesh** krijgt **drie esp32-c6** chips
  (omdat die met zigbee overweg kunnen - een voor serverproxy, een voor lamp, een voor handheld device)
- Ieder lid van een **winkelverlichtingteam met bluetooth-mesh** krijgt **drie esp32-WROOM-32D** chips
  (nu via ble - een voor serverproxy, een voor lamp, een voor handheld device)
- Ieder lid van een **speeddetector** team krijgt **één ESP32-WROOM32** chip
  (iets meer pootjes dan de WROOM-32D - welke je niet nodig hebt, maar enfin, we
   hadden deze ook ingekocht...)

### ESP-IDF-5.3 installeren
- Installeer de ESP-IDF 5.3 bouwomgeving, inclusief arduino-ide component en test er je ESP32 mee (HelloWorld). 
Hopelijk lukt het als je [dit logboek](../../infrastructuur/ESP32-IDF-opzet/ESP32-IDF-opzet.md) volgt.
- Installeer - dat zelfde logboek volgend, lasergame_template_2 (een aantal utility libraries en CleanRTOS).


### Aanbevolen
- Probeer wat CleanRTOS examples uit en bestudeer deze.
- Probeer eens een arduino-ide libary toe te voegen aan je IDF project.