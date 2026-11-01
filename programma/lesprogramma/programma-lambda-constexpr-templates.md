# Programma Lambda, `constexpr` en Templates

**Lambda**'s zijn functies/methoden zonder naam en zonder verplicht voorafgaande declaratie, soms ook "Anonymous Functions"genoemd.
Niet alleen C++ ondersteund lambda's, ook met talen zoals Python, JavScript, C#, Go, Swift, Kotlin en Rust kan je deze gebruiken.

Met **`constexpr`** kan je het compiler al werk laten doen ('during compile-time') waar je in jouw programma alleen de resultaten van wil gebruiken. Bijvoorbeeld kan je een lijst met waardes laten berekenen zonder daarvoor een apart programma te schrijven dat bijvoorbeeld het resultaat van de berekening als een *.hpp bestand opslaat. In het geval van `constexpr` betreft dat vaak berekeningen. Vandaar dat we ook even stilstaan bij twee in de IT veelgebruikte **numerieke rekenmethoden** (numerieke wiskunde).

**Templates** gebruik je al vaker, bijvoorbeeld `vector` van de [Standard Template Library (STL)](https://www.w3schools.com/cpp/cpp_data_structures.asp). Het ultieme doel van Templates is dat de compiler ons schrijfwerk afneemt. Heel nuttig! Vandaar is het belangrijk te weten hoe je Templates herkent en zelf kan gebruiken.

## Voorbereiding

Lesmateriaal over de onderwerpen:

- [Lambda's](../../software/lambdas/)
- [constexpr](../../software/constexpr/) en [numerieke wiskunde](../../software/numerieke-wiskunde/numerieke-wiskunde.md)
- [Templates](../../software/templates/)

Externe bronnen:

- Lees hier over [C++ Lambda Functions](https://www.w3schools.com/cpp/cpp_functions_lambda.asp) (w3schools, dank aan Myrthe Matthee).
- Lees hier over [constexpr in C++](https://www.geeksforgeeks.org/understanding-constexper-specifier-in-cpp/).
- Kijk deze [video over Templates](https://www.youtube.com/watch?v=I-hZkUa9mIs)
- En eventueel nog [deze video van Marius Versteegen over constexpr en Templates](https://youtu.be/yaPNw6C1fYg)

### Tijdens en na de les

Maak de volgende oefenopdrachten en upload je resultaten naar de bijbehorende Canvas Opdracht:

- Voor het [CYD Keypad](programma-CYD-keypad.md) heb je al met Lambda's gewerkt. Maak deze nu af als nog niet gebeurt!
- [Opdracht Constexpr](../../onderwijsmateriaal/opdrachten/oefenopdrachten/constexpr/constexpr.md)
- [Opdracht Templates](../../onderwijsmateriaal/opdrachten/oefenopdrachten/templates/templates.md)
