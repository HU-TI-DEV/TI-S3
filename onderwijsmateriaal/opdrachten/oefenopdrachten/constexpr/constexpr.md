# Oefenopdracht constexpr

## A. Eerste test
Opdracht:
- Test deze cpp code: [constexpr_sin.cpp](constexpr_sin.cpp)
- Vervang de functiebody van constexprSin tijdelijk door: return sin(x); en run opnieuw.
- Zet de functiebody met de Taylor-reeks implementatie terug. 

Vraag:
- Waarom gebruikten we een Taylor-reeks implementatie?
  - **-> [vervang door je antwoord]**

## B. Nauwkeurigheidstest
Opdracht:
- Voeg code toe die de maximale fout weergeeft tussen sin(x) en sinDegrees(x) voor integer hoeken in het bereik van 0..259 graden.

Vraag:
- Welke fout meet je? 
  - **-> [vervang door je antwoord]**

Opdracht:
- Verklein die maximale fout eens met tenminste factor miljard. 

Vraag:
- Daarvoor hoefts slechts 1 getal aangepast te worden, welk getal en hoeveel?
  - **-> [vervang door je antwoord]**

## C. Snelheidstest
Opdracht:
- Voeg code toe die het snelheidsverschil laat zien tussen sin() en sinDegrees(x).

Vragen:
- Verklaar het snelheidsverschil.
  - **-> [vervang door je antwoord]**

- Verlaagt de eerder genoemde extra nauwkeurigheid de gemeten snelheid?
  - **-> [vervang door je antwoord]**
- Waarom wel/niet?

## D. Cosdegrees
- Voeg ook een functie cosDegrees(x) toe, op dezelfde leest geschoeid.
- Voeg die ook toe aan de tests.
- Voeg onderstaand een link toe naar je resulterende cpp code:
  - **-> [vervang door je antwoord]**

## E. const
Je zou het ook kunnen oplossen zonder constexpr, door direct na start van het programma de tabellen uit te rekenen. Je kunt dan zelfs sin() en cos() gebruiken voor het invullen van de tabellen. Dus eenvoudiger code. Vervolgens heb je met sinDegrees en cosDegrees weer vergelijkbare performance. 

Vraag:
- Is het altijd het best om constexpr te gebruiken? Licht je antwoord toe. 
- **-> [vervang door je antwoord]**