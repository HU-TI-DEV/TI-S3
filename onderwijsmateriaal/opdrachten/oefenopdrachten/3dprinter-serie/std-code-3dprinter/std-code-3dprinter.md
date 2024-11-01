# STD naar Code voor 3D-printer

## A) Code voor ModelSelectControl

Het uitgangspunt voor de code van ModelSelectControl zijn het klassendiagram en de bijbehorende STD:  
- **3dPrinter_Totaal-CD_postTaakstructurering.png** (welke je kreeg na de opdracht kd-3dprinter)
- **3dPrinter_Totaal-STD ModelSelectControl.png** (welke je kreeg na de opdracht std-3dprinter)

In dat geval is de taak van klasse ModelSelectControl samengevoegd met die van HoofdmenuControl.

**ModelSelectControl met een eigen taak**

Om een indruk te krijgen van hoe de code van ModelSelectControl er uit zou moeten zien, is het een  
goed idee om in de eerste instantie uit te gaan van het eenvoudigere geval dat ModelSelectControl een **eigen taak** heeft:  
[3dPrinter_Totaal-STD ModelSelectControl Own Task.png](./3dPrinter_Totaal-STD%20ModelSelectControl%20Own%20Task.png)

In dat geval zou de code er zo uit zien:  
[code_ModelSelectControlOwnTask.h](code_ModelSelectControlOwnTask.h)

- Vergelijk de STD van ModelSelectControl met die van ModelSelectControlOwnTask.  
  Wat zijn de verschillen?  
  Leg uit waar elk verschil voor nodig is.
- Bestudeer de STD van ModelSelectControlOwnTask en haar code.  
  Zorg dat je uitzoekt hoe elke regel code mapt op die STD en het klassendiagram.
- Van welke klasse is de gebruikte functie wait() een memberfunctie?
- Waarom is in dit geval de toestand "Idle" nodig (i.t.t. wanneer het geen eigen taak heeft)?
- Waarom is in dit geval een flagStart nodig?
- Waarom heeft ModelSelectControl geen member variabele van type touchDetector nodig?

**ModelSelectControl zonder een eigen taak**

Na het maken van ModelSelectControl met eigen taak kunnen we eenvoudig een variant van de code maken voor het geval het is samengevoegd met de taak van HoofdmenuControl. Dat hebben we eerder gedaan. Dat leverde toen de std: **3dPrinter_Totaal-STD ModelSelectControl.drawio.png** op.  Dat omzetten naar code levert op: [code_ModelSelectControl.h](./code_ModelSelectControl.h)

- Benoem elk van de verschillen ten opzichte van de code met eigen taak, en leg voor elk ervan uit waarom het nodig is.

## B) Code voor HoofdmenuControl

De code voor HoofdmenuControl kan worden afgeleid op basis van het klassendiagram en de STD voor HoofdmenuControl:
- 3dPrinter_Totaal-CD_postTaakstructurering.png (welke je kreeg na de opdracht kd-3dprinter)
- [3dPrinter_Totaal-STD HoofdmenuControl.png](./3dPrinter_Totaal-STD%20HoofdmenuControl.png)

Schrijf nu zelf de code voor HoofdmenuControl.  

Pas de code zodanig aan, dat hij ook de publieke functies aanbiedt die nodig zijn voor de samenvoeging van de taak van ModelSelectControl met de taak van HoofdmenuControl.

Je kunt de methode gebruiken uit "Design Like a Robot!"

Volg [deze Criteria](../../../../../leerdoelen/portfolio-items/code.md) voor de code.

## Canvas Opdracht
Lever de markdown met het resultaat van deze opdracht in op Canvas bij de opdracht "3D Printer Serie".