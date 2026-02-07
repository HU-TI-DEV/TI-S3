# State Transition Diagram (STD) criteria

## Algemeen 
- Het implementeert de stappen uit de bijbehorende **use case beschrijving** of **activity diagram**.
- Er is onderscheid gemaakt tussen het **interface deel** en het implementatie deel.
- De **publieke operaties** uit het klassendiagram zijn terug te vinden in het interface deel.
- Alle **synchronisatiemechanismen** uit het interface deel komen als **event** terug in het **implementatiedeel**.
- Er zijn **geneste toestanden** toegepast als dat het design vereenvoudigt.
- Er zijn **geen pseudotoestanden** gecreerd. Dus **geen** events op **uitgaande pijlen** van decision nodes en de initial node.

## Overgangen
Langs een overgangspijl wordt de volgende volgorde aangehouden, voor events, guard en actions:
```
  event [guard] / action  
```
Meerdere guards of actions worden via ; van elkaar gescheiden. Ze hoeven niet allemaal voor te komen

**Event**
Een event is een synchronisatie mechanisme van het OS waar op gewacht wordt. Dit is in de voltooid verleden tijd geformuleerd (after is de uitzondering).  
Dat kan bijvoorbeeld zijn: 
- after()               (vTaskDelay)
- buttonPressed()       (eventBit)
- spikeDetected()       (eventBit)
- temperatureUpdated()  (Queue)

**Guard**
Een guard is een if statement die instantaan wordt uitgevoerd. Dit resulteert in een decision node 

**Action**
Een action kan een stuk code zijn dat uitgevoerd wordt bij de state transistion. Het kan ook een functie aanroep van een andere klasse zijn.

## Naamgeving communicatiemechanismen
De naamgeving van functies waarmee objecten met elkaar praten is gestandaardiseerd. Hieronder de regels.

| # | Type  | Voorbeelden     | Implementatie |
|-|-|-|-|
| 1 |Aangeven dat een taak pas na *x* ms weer gestoord mag worden. |after(*x* ms) | **vTaskDelay()**   |
| 2 | Doorgeven "event" is gebeurd. <br> Naamgeving: het "ding" + voltooid tijd werkwoord.| bootButtonPressed() <br> lightDetected() | Het zetten van bitjes in **xEventGroupSetBits**. |
| 3 | Doorgeven waarde. <br> Naamgeving: het "ding" + "Updated".| counterUpdated()  | Het doorgeven van een waarde in een **Queue**.  |
| 4| Doorgeven "iets" moet worden uitgevoerd.<br> Naamgeving: gebiedende wijs werkwoord + "ding"  | playSound()<br> showScore() |  Het zetten van bitjes in **xEventGroupSetBits** van de andere taak.<br> Indien ook een waarde wordt meegegeven, dan die meegeven via een **Queue** van de andere taak (vlak voor het zetten van de **eventBit**).|
| 5| Opvragen van een waarde met is"ding" of get"waardevanding" | isBootButtonPressed()<br>getLightLevel(lightLevel)| De "is" met een **Queue** **MARIUS: VAN WELKE TAAK IS DE QUEUEU?** van lengte 1 van het type boolean. <br> De "get" met een **Queue** van lengte 1 van een ander datatype.|
|6| Opvragen van een waarde(s) dat langer duurt voordat het antwoord er is.<br> Naamgeving: query"ding"|queryPersonalData(idNumber)|De eerste taak stuurt het ding waar hij informatie over wil met een **Queue** en zet een vlag met **xEventGroupSetBits**(van die andere taak) zodat de andere taak weet dat hij aan de slag moet. De tweede taak zet een vlag met **xEventGroupSetBits** (van de eerste taak) en vult een **Queue** (met de informatie) zodat de eerste taak weet dat de informatie er is. | 

## Mapping Communicatiemechanismen

De bovenstaande communicatiemechanismen mogen op de volgende plekken voorkomen in de overgangen.
|event |[guard]| / action|
|-|-|-|
|(1)(2)(6)|(5)  |(3)(4)| 



- De **events** in de STD kunnen, zijn alleen van een van de volgende types:  
  - 
  **entry**, **do**, **exit**, **after()**, **when()**, **timerBla**, **flagBla**, of **bla=channelBla.read()**.
- Correcte verwerking van **EABs (Event Action Blocks)**.
- Moet er **gepollt** worden? vergeet dan niet tussendoor steeds te **wachten** (met after(1s) of door te wachten op een expliciet timerEvent).
