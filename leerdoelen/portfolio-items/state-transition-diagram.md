# State Transition Diagram (STD)
Document met eigen (deel van) een State Transition Diagram.
## Criteria 
- Het implementeert de stappen uit de bijbehorende **use case beschrijving** of **activity diagram**.
- Er is onderscheid gemaakt tussen het **interface deel** en het implementatie deel.
- De **publieke operaties** uit het klassendiagram zijn terug te vinden in het interface deel.
- Alle **synchronisatiemechanismen** uit het interface deel komen als **event** terug in het **implementatiedeel**.
- Er zijn **geneste toestanden** toegepast als dat het design vereenvoudigt.
- Er zijn **geen pseudotoestanden** gecreerd. Dus **geen** events op **uitgaande pijlen** van decision nodes en de initial node.

### Overgangen
- Langs een overgangspijl wordt de volgende volgorde aangehouden, voor events, guard en actions. Meerdere guards of actions worden via ; van elkaar gescheiden:
```
  event [guard] / action  
'''
**Event**
Een event is een synchronisatie mechanisme van het OS waar op gewacht wordt. Dit is in de voltooid verleden tijd geformuleerd (after is de uitzondering):
Dat kan bijvoorbeeld zijn: 
- after()               (vTaskDelay)
- buttonPressed()       (eventBit)
- spikeDetected()       (eventBit)
- temperatureUpdated()  (Queue)

**Guard**
Een guard is een if statement die instantaan wordt uitgevoerd. Dit resulteert vaak in een decision node (ALTIJD?)

**Action**
Een action kan een stuk code zijn dat uitgevoerd wordt bij de state transistion. HET KAN OOK EEN FUNCTIEAANROEP VAN EEN ANDERE KLASSE ZIJN??? COMMAND?
 
WAT IS EEN COMMAND DAN? IS DAT EEN ACTION?
Command
Show/Sound, gebiedende wijs
 Zet een event bit
Potentieel ook waarde met queue meegeven
Vragen, zetten geen vlag, bv query
Get (waarde)
Is (boolean?)
Query (vraag, kan lang duren voordat antwoord er is, dus duurt voordat antwoord er is dus hier wel vlag of que zet!!)
Dus Marius roept publieke functie van database aan.
Bart roetp Marius publikee fungctie met : antwoor dis bla, en marius zijn publike functie szet MARIUS zijn vlag en zet data in quueue.
Medeling (voltooide tijd), vlag wordt gezet.
Pressed  (bv button)
Updated, waarde gezet. (bv counterUpdated)
Measured /deteceted, etc…



TODO 



- De **events** in de STD kunnen, zijn alleen van een van de volgende types:  
  - 
  **entry**, **do**, **exit**, **after()**, **when()**, **timerBla**, **flagBla**, of **bla=channelBla.read()**.
- Correcte verwerking van **EABs (Event Action Blocks)**.
- Moet er **gepollt** worden? vergeet dan niet tussendoor steeds te **wachten** (met after(1s) of door te wachten op een expliciet timerEvent).
