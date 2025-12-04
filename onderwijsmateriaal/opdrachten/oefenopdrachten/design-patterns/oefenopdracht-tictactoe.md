# Design Patterns

## Oefenopdracht Tic-tac-toe

Schrijf een Tic-Tac-Toe (3-op-een-rij) spelletje.

### Maak hiertoe

- een object voor het spel en
- een object voor een zet.

### Voor deze opdracht ga je gebruik maken van

- het **Command pattern** (voor het verloop van het spel) en
- het **Model-View-Controller-pattern** (om verschillende onderdelen te scheiden), en
- een **STL container**.

### Tips en eisen voor het maken van jouw programma

- Sla het verloop van het spel (de lijst van zetten -> de 'commands') op in een **STL container**.
- Sla de huidige bordsituatie niet expliciet op: waar nodig creëer je die door **de lijst zetten** te doorlopen.
- Implementeer een **‘undo’ feature** door de laatste zet uit het spel te verwijderen.
- Scheid het spel deel van de interface (met behulp van het **MVC-pattern**).
- Bied, met **zo min mogelijk code duplicatie**, zowel een **grafische (SFML) interface** als een **text-only interface**.
- De SFML-versie moet ook van iemand kunnen worden gebruikt die kleurenblind is
(alleen kleur ter onderscheiding van de player moves is niet voldoende).
- Zorg ervoor dat beide versies makkelijk kunnen worden gebouwd.
- Documenteer in jouw README.md hoe je de applicatie bouwt.
- Als je het niet op de scherm toont, documenteer ook hoe je het programma moet gebruiken.
- De **text-only applicatie mag geen SFML-afhankelijkheden bevatten**
  (deze zou dus ook op een micro-controller moeten kunnen runnen).

**Succes!**
