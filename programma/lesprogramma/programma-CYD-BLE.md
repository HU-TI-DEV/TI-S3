# Programma CYD BLE

Deze les gaat over Bluetooth Low Energy (BLE).

## Voorbereiding

Kijk de eerste 5 minuten van [deze video](https://www.youtube.com/watch?v=lj99N6pW-Ew) zodat je een idee hebt wat een client en server is.

    Wij geven alleen voorbeelden van BLE niet van klassiek Bluetooth (of Serial Bluetooth)

## De opdracht

Bij deze opdracht zijn twee [voorbeeld projecten](../../software/CYD/Bluetooth/). Je hebt twee ESP32 devices nodig (hoeft geen CYD te zijn een ESP32 WROOM kan ook). Eén ESP richt je in als server de ander als client. Laat in de console zien dat je data kunt uitwisslen.

## Tijdens en na de les

- Samen met een mede student configureer je een BLE server en BLE client.
- Wissel data tussen server en client uit.
- Maak een eenvoudige rekenmachine (Bijvoorbeeld 3 + 5 = 8). De client stuurt de operatie (ADD) en twee parameters (a=3, b=5). De server stuurt het resultaat terug. 
- Lever relvante code en screenshots in bij de Canvas opdracht **ESP32 CYD BLE**

### Optioneel

- Maak een eenvoudig protocol voor het uitwisselen van data met een CRC checksum dat je bijvoorbeeld in je project kunt gebruiken.
- Implementeer BLE communicatie met je device en een Android (?) app.

### De volgende les

Maak je verbinding met ons centrale dashboard om game informatie uit te wisselen.