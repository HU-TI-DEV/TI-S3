# Oefenopdracht Networking Basics - Spelen met de ESP32
Doel van deze opdracht is om kennis te maken met de ESP32 en er meteen zoveel mogelijk networking ervaring ermee op te doen. Je mag gebruik maken van de Arduino IDE, of van de Arduino IDE examples van de arduino ide component die je binnen het test_lasergame_2 ESP32-IDF project hebt geinstalleerd. In bijvoorbeeld `test_lasergame_2\main\main_for_wifi_scan_ard_ide_with_nvs.cpp` zie je bijvoorbeeld hoe dat kan voor een wifi scan een een accesspoint. Natuurlijk ook altijd het pad naar de betreffende examples folder aan de CMakeList.txt file toevoegen. Noteer je ervaringen, leerpunten e.d. zoals gewoonlijk in je persoonlijke logboek.

## Examples
Begin met het uitproberen van de bij de ESP32 library behorende standaard examples
- Hello world
- Scanner
- Internet access
- Accesspoint
- Webserver - bedien led met GET.
- Webserver - bedien led met POST (via postman)

Vraagje daarbij: waarom is het bedienen van de led via GET vragen om problemen? (hint: denk aan caching)

## Extra opdracht: 
Bij beide webserver voorbeelden moest je de wifi-credentials hardcoden.
Voor een product dat je kunt verkopen is dat niet geschikt.

Maak dus een combi: Als je tijdens opstarten een knop ingedrukt houdt, wordt je ESP32 een accesspoint (met herkenbare naam) waar je je wifi-credentials kunt ingeven. Die worden in persistent geheugen opgeslagen. Tevens toont het accesspoint zijn ip adres.

Als je de ESP32 herstart (zonder die knop ingedrukt te houden), herstart hij, en wordt het een webserver om de led te bedienen-zoals voorheen.

## Inleveren
Lever voor elk van de bijbehorende canvas opdrachten een anchor-link in naar het kopje in je persoonlijke logboek waar je start met de opdracht. Dus een link naar je persoonlijk logboek, gevolgd door #, gevolgd door het (unieke-)kopje waar je begint.

Let daarbij op deze [criteria](../../../../leerdoelen/portfolio-items/persoonlijk-logboek.md#criteria).

NB: bestudeer de link van bovenstaande link ( klinkt dubbelop :-) ) voor een voorbeeld van een anchor-link.
