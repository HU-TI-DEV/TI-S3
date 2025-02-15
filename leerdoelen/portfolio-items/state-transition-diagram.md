# State Transition Diagram (STD)
Document met eigen (deel van) een State Transition Diagram.
## Criteria 
- Het implementeert de stappen uit de bijbehorende **use case beschrijving** of **state transition diagram**.
- Er is onderscheid gemaakt tussen het **interface deel** en het implementatie deel.
- De **publieke operaties** uit het klassendiagram zijn terug te vinden in het interface deel.
- Alle **synchronisatiemechanismen** uit het interface deel komen als **event** terug in het **implementatiedeel**.
- Er zijn **geneste toestanden** toegepast als dat het design vereenvoudigt.
- Correcte verwerking van **EABs (Event Action Blocks)**.
- De **events** in de STD kunnen, zijn alleen van een van de volgende types:  
  **entry**, **do**, **exit**, **after()**, **when()**, **timerBla**, **flagBla**, of **bla=channelBla.read()**.
- Er zijn **geen pseudotoestanden** gecreerd. Dus **geen** events op **uitgaande pijlen** van decision nodes en de initial node.
- Moet er **gepollt** worden? vergeet dan niet tussendoor steeds te **wachten** (met after(1s) of door te wachten op een expliciet timerEvent).
