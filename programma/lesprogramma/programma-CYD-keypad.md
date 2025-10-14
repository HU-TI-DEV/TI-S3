# Programma CYD Keypad

## Voorbereiding
- Lees over [Lambda's](https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp)
- Bestudeer het volgende schema:

![K845037](./images/K845037.png)
- Wat gebeurt er met $OUT$ als 1 van de knoppen wordt ingedrukt?
- het schema hoort bij het volgende bordje:
  
![K845037](./images/K845037-board.png)
   
## Tijdens de les
Tijdens de les kan ADC uitlezen met eerder geschreven code. Deze waarden (raw values) kan je gebruiken om keypad [template project](../../software/CYD/AnalogButtonReader/) aan te vullen.

In de main introduceren we een lambda functie. Een lambda is een inline anonieme functie. We zouden een functie kunnen schrijven:
```cpp
void myButtonHandler(Button button) {
    // the switch case
}
```

En dit vervolgens zo doorgeven:
```cpp
buttons.setCallback(myButtonHandler);
``` 

Een lambda geeft ons de mogelijkheid om gedrag direct bij de aanroep te defineren:
```cpp
buttons.setCallback([&](Button button) {
    switch (button) {
        // etc.
    }
});
```
Waarom gebruiken we & in de capture? Is het in dit geval strict noodzakelijk? Wanneer zou dit nuttig zijn?

**Opdracht Keypad**
- Experimenteer eerst met het bordje. Meet welke spanningen je krijgt als je een knopje indrukt. Klopt het met wat je verwacht/berekend had?
- Er is bij deze opdracht een [template project](../../software/CYD/AnalogButtonReader/). Vul de relevante code aan, de treshold values in de `AnalogButtonReader.cpp` en maak een correcte switch case in main.cpp.
- Geef voor elke knop die wordt ingedrukt de naam van de knop weer in een console output.   
- Zorg dat er relevant doxygen commentaar aan je code is toegevoegd. 

## Na de les
- Werk verder aan de opdrachten als je het nog niet af hebt. 
- Je kan deze code later gebruiken om een entity aan te sturen in je game-loop.

## Canvas

Voor de opdracht is een canvas entry, namelijk:
  - ESP32 ADC & Keypad

Bestudeer de canvas opdracht om te zien wat je precies moet inleveren. 

## Optioneel

- De adc.h library gebruikt in dit voorbeeld is `depricated` kan je de code aanpassen zodat dit ook werkt met de adc_onshot driver?