# State Transition Diagram (STD) criteria

## Algemeen 
- Het implementeert de stappen uit de bijbehorende **use case beschrijving** of **activity diagram**.
- Een STD beschrijft het gedrag van 1 task (thread) van het operating system.  
- Er is onderscheid gemaakt tussen het **interface deel** en het implementatie deel.
- De **publieke operaties** uit het klassendiagram zijn terug te vinden in het interface deel.
- **Alle synchronisatiemechanismen** uit het interface deel komen als **event** terug in het **implementatiedeel**.
- Er zijn **geneste toestanden** toegepast als dat het design vereenvoudigt.
- Er zijn **geen pseudotoestanden** gecreerd. Dus **geen** events op **uitgaande pijlen** van decision nodes en de initial node.
- Moet er **gepollt** worden? vergeet dan niet tussendoor steeds te **wachten** (met after(1s) of door te wachten op een expliciet timerEvent).

## Overgangen
Langs een overgangspijl wordt de volgende volgorde aangehouden, voor events, guard en actions:
```
  event [guard] / action  
```
Meerdere guards of actions worden via ; van elkaar gescheiden. Ze hoeven niet allemaal voor te komen

**Event**
Een event is een synchronisatie mechanisme van het OS waar op gewacht wordt.  
Dat kan bijvoorbeeld zijn: 
- after()               (vTaskDelay)
- buttonPressed()       (eventBit)
- spikeDetected()       (eventBit)
- temperatureSet()      (Queue & eventBit)

**Guard**
Een guard zijn de condities van een if statement die direct (zonder dat er ergens op gewacht wordt) wordt uitgevoerd. Dit kan op twee manieren worden toegepast:
  1) Als uitgangen van een decision node.
  2) Als enkele pijl,  Deze manier kan enkel in de vorm ```event [guard]``` aangezien de state anders "blocking" zou worden (de state moet altijd de macht uit handen geven).

**Action**
Een action kan een stuk code zijn dat uitgevoerd wordt bij de state transition. Het kan ook een functie aanroep van een andere klasse zijn. Cruciaal is dat een action direct wordt uitgevoerd, zonder wacht toestanden. 

## Naamgeving communicatiemechanismen
De naamgeving van functies/mechanismen waarmee objecten met elkaar praten is gestandaardiseerd. Hieronder de regels.

| # | Type  | Naam in het STD | Functienaam | Implementatie |
|-|-|-|-|-|
| 1 |Aangeven dat een taak pas na *x* ms weer gestoord mag worden. |after(*x* ms)|vTaskDelay() | **vTaskDelay<sup>2</sup>**<br> hij mag door als de tijd verstreken is.   |
| 2 | "event" is gebeurd. <br>*Naam functie:*<br> "ding"+voltooidtijdwerkwoord. <br><br>Andere taak heeft opdracht gegeven om iets te doen. <br>*Naam functie:*<br>gebiedendewijswerkwoord+"ding"  | eventBitBootButtonPressed <br> eventBitLightDetected<br><br>eventBitPlaySound<br>eventBitShowScore|bootButtonPressed()<sup>1</sup> <br> lightDetected()<sup>1</sup><br><br> playSound()<sup>1</sup><br>showScore()<sup>1</sup>|De state wacht op: **xEventGroupWaitBits<sup>2</sup>**<br> hij mag door als: **xEventGroupSetBits<sup>3</sup>**. |
| 3 | Er is een waarde door gegeven van een andere taak. <br> *Naam functie:*<br> "ding"+Set.| eventBitCounterSet |counterSet()<sup>1</sup>  | De state wacht op: **xEventGroupWaitBits<sup>2</sup>** <br> Hij mag door als: <br> Het doorgeven van een waarde in een **Queue<sup>3</sup>** en daarna zetten van bitjes in **xEventGroupSetBits<sup>3</sup>**.  |
| 4 | Checken of er een waarde is door gegeven. <br> *Naam functie:*<br> "ding" +Updated.| Je kan een guard zetten of er iets in de queue is aangekomen: uxQueueMessagesWaiting ("naam Queue") > 0 |counterUpdated()<sup>1</sup>  | Het doorgeven van een waarde in een **Queue<sup>3</sup>**.  |
| 5| Doorgeven "iets" moet worden uitgevoerd in een andere STD/taak.<br> *Naam functie:*<br>gebiedendewijswerkwoord+"ding"<br><br> Doorgeven "iets" is gebeurd. <br>*Naam functie:*<br> "ding"+voltooidtijdwerkwoord.<br><br> |*objectName*.playSound<br>*objectName*.showScore<br><br> *objectName*.bootButtonPressed <br> *objectName*.lightDetected|playSound()<sup>4</sup><br> showScore(score)<sup>4</sup><br><br>bootButtonPressed()<sup>4</sup> <br> lightDetected()<sup>4</sup> |  Het zetten van bitjes in **xEventGroupSetBits** van de andere taak.<br> Indien ook een waarde wordt meegegeven, dan die meegeven via een **Queue** van de andere taak (vlak voor het zetten van de **eventBit**).|
| 6| Opvragen van een waarde van een andere taak.<br> *Naam functie:*<br>is+"ding" of <br> get+"waardevanding" | *objectName*.isBootButtonPressed()<br>*objectName*.getLightLevel(lightLevel)|isBootButtonPressed()<sup>4</sup><br>getLightLevel(lightLevel<sup>4</sup>|  De "is" met een **Queue**<sup>5</sup> van lengte 1 van het type boolean. Hij geeft een boolean als return value terug. <br> De "get" met een **Queue**<sup>5</sup> van lengte 1 van een ander datatype. De function past de waarde van de parameter aan (die als reference is meegegeven). |


**<sup>1</sup>** Dit zijn publieke functies van **deze** std/taak. Ze worden benoemd in de << interface >> van **deze** std. Ze worden aangeroepen in een **andere** std/task.  
**<sup>2</sup>** Uitgevoerd in de state van de klasse van **deze** std/taak. Meestal aan het eind van de case van de switchcase.  
**<sup>3</sup>** Een **andere** klasse (met een andere std/taak) roept een publieke functie aan in de klasse van **deze** std/taak. Deze publieke functie staat in de << interface >> van **deze** std. In de functie worden eventbits gezet of queues gevuld.  
**<sup>4</sup>** Dit zijn publieke functies van een **andere** std/taak. Ze worden benoemd in de << interface >> van de **andere** std. De instantiatie van een object van die andere STD/taal wordt in het schema aangegeven met **objectName**. Ze worden aangeroepen in **deze** std/task.  
**<sup>5</sup>** De queue "is" van de **andere** std/taak.

## Mapping Communicatiemechanismen

De bovenstaande communicatiemechanismen mogen op de volgende plekken voorkomen in de overgangen.
|event |[guard]| / action|
|-|-|-|
|(1)(2)(3)|(4)(6)  |(5)(6) | 

(4), (5) en (6) kunnen ook worden gebruikt in de body van de state (als een entry / event).


