# Programma STD <-> code - KlikAanKlikUit

Deze les gaat over het ontwerpen van een STD (State Transition Diagram) en het vertalen naar CleanRTOS code.

## Voorbereiding

- Lees blz 47 tm blz 52 van [Design like a robot!](../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf) door.
- Check het [State Transition Diagram (STD) van KlikAanKlikUit](../../onderwijsmateriaal/opdrachten/oefenopdrachten/std-klik-aan-klik-uit/KlikAan-KlikUit-1.png).
- Kijk in de code van test_lasergame_2 -> apps -> KlikAanKlikUit

## Tijdens en na de les

- Build en run KliKAanKlikUit.
  - Als je een ESP32-C6 gebruikt: zoek uit wat er moet worden veranderd om het daar te runnen.
- Wat gebeurt als je de knop indrukt?
- Welke onderdelen missen in het State Transition Diagram?
- Wat kan je minimaal toevoegen in het STD en de code om het bruikbaar werkend te krijgen?

### Optioneel

- Maak een map 'test' aan en schrijf unit-tests voor KlikAanKlikUit en Button.
- Als we willen dat een lange druk op de knop de LED alleen een keer omschakeld
  - Wat moeten we in het State Transition Diagram veranderen?
  - Hoe kunnen we dit door toeveogingen alleen in de klas KlikAanKlikUit implementeren?
  - Hoe kunnen we dit door toeveogingen alleen in de klas Button implementeren?
