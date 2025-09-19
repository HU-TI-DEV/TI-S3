# Programma CYD drawables

Deze les gaat over het tekenen van pixels, lijnen en andere figuren op een scherm.

## Voorbereiding

Lees over [algorithmes en het tekenen van lijnen](https://en.wikipedia.org/wiki/Line_drawing_algorithm)

## De opdracht

Bij deze opdracht is weer een voorbeeld project. Een aantal onderdelen ontbreken deze implementer je zelf. Het project heeft al deels de structuur die we ook bij de Game opdracht verwachten.

  Je zal merken dat de kleuren nog niet helemaal correct werken. De code is geoptimaliseerd voor CYD3.2. De Backlight is aangesloten op verschillende pinnen dit moet je dus mogelijk aanpassen. Met het voorbeeld dat je krijgt moet je minimaal pixels kunnen tekenen.

De 2.8-inch TFT LCD op de CYD heeft een ILI9341 driver chip voor het weergeven van beelden. We maken gebruik van de [Espressif implementatie voor de esp_lcd component](https://components.espressif.com/components/espressif/esp_lcd_ili9341/versions/2.0.1/readme). Bekijk in het voorbeeldproject hoe deze is toegevoegd via managed components aan het project door het aanmaken van een idf_component.yml bestand.


## Tijdens en na de les

- Krijg je theorie over het tekenen van pixels en lijnen
- Implementeer je de drawables uitbreiding voor de Ili9341 Display wrapper
- Je kunt de volgende figuren tekenen: lijn, rechthoek, vierkant

### Optioneel

- De drawables uitbreiden met de volgende primitives: cirkel en driehoek
- Implementeer een fill voor de figuren

### De volgende les

In het vervolg van deze les leer je over het maken van een backbuffer, tekenen van sprites en het tonen van fonts.
