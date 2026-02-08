# Programma STD <-> code

Deze les staat het ontwerpen van een STD (State Transition Diagram) centraal. De naam zegt het al, het is een diagram dat laat zien in welke toestanden een taak zich kan bevinden. Daarnaast laat het zien onder welke voorwaarden een toestand kan overgaan in een andere toestand. Deze les gaat tevens over het vertalen van een STD naar code.

## Voorbereiding
- bestudeer de kwaliteitscriteria aan een [std](../../leerdoelen/portfolio-items/state-transition-diagram.md).
- hou deze [ppt](./files/Operating_Systems.pptx) bij de hand als manual. Met name het stuk over de STD.
## Tijdens de les

Als eerste gaan we de use case van het verkeerslicht bekijken. 

>## Use Case Beschrijving — Verkeerslichtcontroller 
>### Primaire Externe Signalen  
>- **Detectie van knop A** (voetgangersaanvraag)  
>- **Detectie van voertuig via lusdetector (knop B)**  
>### Preconditions  
>- De verkeerslichtcontroller is operationeel.  
>- Het verkeerslicht ondersteunt drie toestanden: **Groen**, **Geel/Oranje**, **Rood**.  
>- De standaardtoestand is **Groen**.
>### Scenario
>1. Het systeem zet het verkeerslicht in de standaardtoestand **Groen**.
>2. Wanneer het systeem detecteert dat **Knop A** is ingedrukt zet het systeem het stoplicht op **Geel/Oranje** voor **3 seconden**. 
>3. Na die 3 seconden schakelt het systeem van:**Geel/Oranje** naar **Rood**.  
>4. Wanneer het systeem een voertuig op de lus detecteert (**knop B**) start het een Duitse knippertransitiemodus.  
>5. Het systeem voert **5 knippercycli** uit, waarbij elke cyclus bestaat uit:
>   - **Geel/Oranje gedurende 0,5 seconden**
>  - **Rood gedurende 0,5 seconden**
>6.  Na het voltooien van **5 cycli** schakelt het systeem van **Rood** naar **Groen**, en hervat het normale verkeersverloop (terug naar 1).

Zoals je ziet hebben we minimaal 2 knoppen nodig. 
Jammer genoeg hebben we wel maar 1 bruikbaar knopje op het bord! We zullen dus nog een ander pin moeten gebruiken. Bestudeer de volgende bron:  https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/PINS.md. Tip, misschien is 22 handig?  

Gelukkig hebben we al wel een RGB led. 

### De opdracht
1) Maak een STD van het verkeerslicht (mag in plantUML of in drawIO)  
2) Laat je STD aftekenen bij de docent.
3) Start met het StateMachineTemplate (zie [statemachinetemplate.zip](./files/StateMachineTemplate.zip).)
4) Pas de code aan (of begin helemaal opnieuw, wat je het prettigst vind) en zorg dat de code en STD 1-op-1 hetzelfde zijn.
5) Run het programma, en laat het runnende programma ook aftekenen bij de docent. 

### Canvas
Upload je werk naar canvas (STD <-> code Introduction). Zie de canvas opdracht hoe je dat precies moet doen.

