# Programma ESP32 IDF en CleanRTOS installeren - deel 1

Deze les gaan we de ESP32 IDF programmeeromgeving installeren en (team-)project voor de code aanmaken.

### Logboek bijhouden, Canvas opdracht

Start een nieuw kopje in je persoonlijk logboek, bijvoorbeeld genaamd "ESP32 IDF Installatie".
Houdt tijdens het proces goed bij in je logboek wat je leert, waar je tegenaan loopt en hoe je het oploste.

Een mooi 'bewijs' van een succesvolle installatie is een screenshot nadat je de "dump log" button hebt ingedrukt tijdens het CleanRTOS testprogramma "AllWaitables.ino".

Lever na een succesvolle installatie en test bij de Canvas opdracht "ESP32 IDF Installatie" de link in naar dat kopje in je logboek (dus bijvoorbeeld <https://github.com/bla/persoonlijk_logboek.md#esp-idf-installatie>).

## Voorbereiding

- Kijk eventueel even [deze inleidende video](https://youtu.be/DKVyf8Wh0kE)
- Lees eventueel alvast wat in [ESP32-IDF-opzet](../../infrastructuur/ESP32-IDF-opzet/ESP32-IDF-opzet.md).
- Neem voor de zekerheid mee:
  - **Twee** breadboards (een ESP32 heeft er 2 nodig)
  - Een drukknopje
  - Een weerstand van 1 a 2 kOhm
  - Een 470uF condensator
  - Een 100nF condensator
  - Een snoer waarmee je je laptop aan USB-C kunt verbinden
  - Een snoer waarmee je je laptop aan micro-USB kunt verbinden
- Bereid je voor op wat chaos - en probeer alvast wat geduld te reserveren.
  Dit soort dingen gaan zelden in 1x goed.

## Tijdens en na de les

### Begin van de les

Je krijgt aan het begin van de les van Harm de ieder één ESP32 devkits:

- Ieder lid van een **stabiellopenteam** krijgt **één ESP32-S3** devkit
  (laatste versie: sneller - ivm mogelijk cameragebruik - maar mogelijk minder
   compatible met bestaande libraries en kinderziektes)
- Ieder lid van een **speeddetectorteam** krijgt **één ESP32-WROOM32D** devkit
  (minste kans op onverwachte troubles, maximaal standaard / compatible)
- Ieder lid van een **verlichtingteam met bluetooth-mesh** krijgt **één esp32-WROOM-32** devkits
  
### ESP-IDF-5.3 installeren

- Installeer de ESP-IDF 5.3 bouwomgeving, inclusief arduino-ide component en test er je ESP32 mee (HelloWorld).
Hopelijk lukt het als je [dit logboek](../../infrastructuur/ESP32-IDF-opzet/ESP32-IDF-opzet.md) volgt. Er is ook een logboek versie [voor Mac OS X](../../infrastructuur/ESP32-IDF-opzet/ESP32-IDF-opzet-Mac-OS-X.md).
- Installeer - dat zelfde logboek volgend, lasergame_template_2 (een aantal utility libraries en CleanRTOS). Voor het lasergame_template_2 is er ook een [Mac OS X logboek](../../infrastructuur/ESP32-IDF-opzet/lasergame_template_2-Mac-OS-X.md).

### Aanbevolen

- Probeer wat CleanRTOS examples uit en bestudeer deze.
- Probeer eens een arduino-ide libary toe te voegen aan je IDF project.
