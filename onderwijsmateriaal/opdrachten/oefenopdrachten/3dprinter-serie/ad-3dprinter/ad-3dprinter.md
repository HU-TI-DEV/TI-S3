
## 3D Printen

Ga voor de use case voor het 3D Printen uit van de beschrijving **UC03_3DPrinten** die je hebt gekregen als uitwerking waarmee je jezelf kon nakijken bij de uc-3dprinter opdracht.

Een bekend spreekwoord zegt "Een plaatje zegt meer dan 1000 woorden".  
Vooral als het wat complexer wordt, met conditionele sprongen e.d, is het fijner en overzichtelijker om het in een plaatje weer te geven, een zogenaamd activity diagram.

Om de bovenstaande use case overzichtelijk te houden, en niet te groot, zijn wat complexe brokken van de functionaliteit afgesplitst: ProcessM en ProcessG.  
Die functionaliteit heeft niet direct met de actoren van de 3dPrinter als geheel te maken. Puristisch gezien zijn het dan ook geen echte sub-usecases.  
(je zou ze wel kunnen zien als use cases van een deelsysteem bij genest design - maar dat doen we niet bij dit vak).

Om te laten zien wat ProcessM en ProcessG doen, zullen we aparte activity diagrammen ontwerpen.

### A) Activity Diagram voor 3DPrinten

- Ga voor jezelf na of de gegeven use case beschrijving geschikt is, uitgaande van: [GCode](../bronnen/g-code.md)
- Maak het bijbehorende activity diagram af, uitgaande van dit raamwerk: 
[act_3DPrinten_Scaffold.drawio](./act_3DPrinten_Scaffold.drawio)

Let daarbij op [deze Criteria voor Activity Diagrammen](../../../../../leerdoelen/portfolio-items/activity-diagram.md)

## B) Activity Diagram voor ProcessM

- Maak het activity diagram af voor ProcessM, uitgaande van dit raamwerk: [act_ProcessM_Scaffold.drawio](./act_ProcessM_Scaffold.drawio)

## C) Activity Diagram voor ProcessG

- Lees voorafgaand aan deze opdracht wat ProcessXYZEF doet in de toelichting van de volgende opdracht.
- Maak het activity diagram af voor ProcessG, uitgaande van dit raamwerk: [act_ProcessG_Scaffold.drawio](./act_ProcessG_Scaffold.drawio)


## D) Activity Diagram voor ProcessXYZEF

ProcessXYZEF zorgt dat de waarden van X, Y, Z en E uit de gelezen regel gcode zorgen voor een correcte update van tgtExt, tgtX, tgtY en tgtZ, gegeven de huidige instellingen voor de (boolean) waardes absMoving en absExtruding. Verder stelt het de feedrate in op basis van de waarde van F.

- Maak het activity diagram af voor ProcessXYZEF, uitgaande van dit raamwerk: [act_ProcessXYZEF_Scaffold](./act_ProcessXYZEF_Scaffold.drawio)

## E) Activity Diagram voor GNot1

ProcessGNot1 zorgt voor een correcte afhandeling van alle G commandos behalve het commando met G=1.

- Maak het activity diagram af voor ProcessGNot1, uitgaande van dit raamwerk: [act_ProcessGNot1_Scaffold.drawio](./act_ProcessGNot1_Scaffold.drawio)

## Canvas Opdracht
Lever de markdown met het resultaat van deze opdracht in op Canvas bij de opdracht "3D Printer Serie".