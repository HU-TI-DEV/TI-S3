# CleanRTOS Logging en Debugging Oefenopdracht - Pong

## Introductie

Je gaat nu een pong-spelletje voor de text-console, op basis van CleanRTOS debuggen.
Maak daarbij gebruik van het log object om tussentijdse resultaten te loggen, en van de bijbehorende drukknop om die tussentijdse resultaten op de console weer te geven.

## Opzet

- Kopieer de pong folder (dat is een subfolder van de plek waar dit .md document staat) in de apps folder van je test_lasergame_template_2 project

- Gebruik in de Main.cpp:
  
  - #include <Pong2.ino>

- Gebruik in de includedirs section van CMakeLists.txt:
  
  - "../apps/pong"

- Sluit 3 knoppen aan op de juiste pinnen: Eentje voor de logger, eentje voor "links" en eentje voor "rechts".

- Vergeet niet de pulldown weerstanden!

## Debugging

Als het goed is, flasht de applicatie (na idf.py flash monitor in de test_lasergame_2 project folder) zonder compilefouten. Alleen werkt de applicatie (nog-) niet naar behoren. Aan jou de taak om de fouten op te lossen.

Goddank is de codeur niet als een kip zonder kop begonnen te programmeren, maar heeft eerst een [Object Model](./pong/pong.svg) gemaakt. Dat geeft je zonder een regel code bestudeerd te hebben een snelle indruk van hoe een en ander zou moeten werken. (STD's erbij zou natuurlijk helemaal ideaal geweest zijn)

Het debuggen kun je doen met de volgende cycli:

- Test wat het spel doet.

- Voeg logs toe (voor zover niet al aanwezig). Vuistregel voor goede plekken daarvoor:
  
  - In elke publieke functie loggen dat ze is aangeroepen, inclusief de paramaters erbij.
    Daarmee krijg je goed beeld van wat de taken tegen elkaar zeggen.
  - Aan het begin van elke state-handling (na een case statement) de naam van de state loggen.
    Daarmee krijg je een goed beeld van in welke state taken zich bevinden.

- Bedenk (met hulp van het Object Model) wat er zou moeten gebeuren.

- Implementeer een fix.

- goto eerste bulletpoint.