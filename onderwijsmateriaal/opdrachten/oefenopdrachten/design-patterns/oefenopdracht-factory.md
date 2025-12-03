# Design Patterns

## Oefenopdracht Factory

### Algemeen

Maak een klasse hiërarchie van beweegbare scherm-objecten.\
Handel het selecteren en bewegen af in de superklasse.

### Specifieker

Maak een factory function die de volgende scherm-objecten kan creëren:

- circle,
- rectangle,
- line en
- picture.

Ieder object heeft

- een positie, (het eerste punt) en
- een kleur (black, white, red, green, blue, yellow, magenta of cyan), behalve picture.

### Specifieke eisen

- circle heeft een **diameter**;
- line en rectangle hebben een **tweede punt**, om het einde aan te geven (positie is het eerste punt);
- picture heeft een **bestandsnaam**, het programma moet tenminste PNG-bestanden kunnen inlezen en tonen;
- de hoeveelheid van objecten is niet beperkt (je kan een testbestand krijgen met 10000+ regels),
- de getoonde scherm moet tenminste 1024 x 800 pixels groot zijn.
- Check alle **fouten** die kunnen optreden en **genereer daarvoor passende exceptions**.
  Denk aan onbekende objecten, onbekend format voor parameters, maar ook aan einde-file.

Maak een applicatie die:

- de objecten leest uit een **text file** "factory.txt" en toont,
- de gebruiker de gelegenheid biedt om objecten te **selecteren** en te **verschuiven**,
- bij het afsluiten van de applicatie de text file overschrijft met de nieuwe of aangepaste lijst van objecten (met de nieuwe posities).

Sla de (pointers naar) de objecten op in een **container**.

Tijdens het afbeelden en afhandelen van gebruikershandelingen loop je met een for( : )-loop door deze container heen.

Let op wat je doet als er een fout wordt geconstateerd in de textfile.\
Zorg er in ieder geval voor dat de gebruiker duidelijk te zien krijgt wat de fout is (Op welke lijn? Wat is fout?), en dat de text file niet overschreven wordt.

### Bestandsformaat

Er is een verplicht bestandsformaat voor het text file "factory.txt".

Hier is een kort voorbeeld:

```text
(50,50) RECTANGLE blue (150,100)
(50,90) CIRCLE red 30
(50,150) LINE yellow (150,250)
(50,300) PICTURE hu-logo.png
(300,90) CIRCLE green 70
(50,450) RECTANGLE white (450,500)
```

### Testing

- [factory-test.txt](./factory-test.txt) - test input (moet je kopieren naar "factory.txt")
- [factory-test.png](./factory-test.png) - schermafbeeld van wat je verwacht als resultaat

Voorbeeld van een test sequence:

- Render check
  - Kopieer factory-test.txt naar factory.txt.
  - Start jouw programma.
  - Maak een schermkopie.
  - Sluit jouw programma.
  - Vergelijk factory-test.png met jouw schermkopie.
    Kijk naar vaak voorkomende fouten:
    - Gebruikt CIRCLE een diameter of een radius?
    - Gebruiken RECTANGLE en LINE een start en een eindpunt of een startpunt en `size`?
- Fout check
  - Kopieer factory-test.txt naar factory.txt.
  - Open factory.txt met een editor en vervang enkele onderdelen/tekens:
    - bijvoorbeeld RECTANGLE -> RXCTANGLE
    - wis in een start/eindpunt een van de haakjes
    - verander de bestandsnaam in een PICTURE lijn
    - ...
  - Maak een kopie van factory.txt tot factory-1.txt
  - Start je programma.
    - Krijg je een duidelijke foutmelding met lijnnummer en wat er precies mis is?
    - Bonus: Het is goed als dat programma niet meteen stopt maar info voor alle foutieve regels toont.
  - Stop je programma.
  - Hernoem factory.txt naar factory-2.txt
  - Vergelijk factory-1.txt met factory-2.txt
    - Is factory-2.txt veranderd? Dat mag niet volgens de eisen.
- Select/move check
  - Kopieer factory-test.txt naar factory.txt en nog eens naar factory-1.txt.
  - Start jouw programma.
  - Selecteer enkele van de grafische elementen en verschif deze.
  - Sluit jouw programma.
  - Hernoem factory.txt naar factory-2.txt
  - Vergelijk factory-1.txt met factory-2.txt
    - Is factory-2.txt veranderd? Dat is goed!
    - Check dat alleen posities zijn veranderd (bij RECTANGLE en LINE startpunt en eindpunt)

**Succes!**
