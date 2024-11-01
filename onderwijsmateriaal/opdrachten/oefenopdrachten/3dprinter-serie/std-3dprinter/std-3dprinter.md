
## Uitgangspunt
Ga bij deze opdracht uit van de uitwerking van het klassediagram dat je hebt gekregen om jezelf na te kijken na het maken van de opdracht kd-3dprinter: **3dPrinter_Totaal-CD_postTaakstructurering.png**.

## A) HoofdmenuControl
Gebruik voor deze opdracht de use case beschrijving **UC01_HoofdmenuNavigeren**, welke je hebt gekregen na de opdracht uc-3dprinter.

Voor dit diagram kun je het volgende STD afleiden: [std_HoofdmenuControl.drawio](./std_HoofdmenuControl.drawio)

- Bestudeer de STD. Kun je je vinden in het resultaat? Wat zou je zelf anders gedaan hebben?
- Welke toestanden bevat het diagram?
- Welke events?
- Welke synchronisatiemechanismen?
- Waarom `flagStart` ipv `startQueue`?
- Waarom `flagStart.set()` i.p.v. `bFlagStart = true`?
- Wat is `&ta`? Waarom wordt dat in een Queue opgeslagen, en niet in een Pool?
- Waarom vindt er bij de start van de STD `taQueue.clear()` plaats?
- Welke guards?
- Wat is er handig aan het gebruik van de "lokale convenience functies"?
- Waarom staat de guard `[pTa==&taPrinten]` in het STD model en niet als een `if` statement in een locale convenience functie?

## B) PrinterOnderhoudControl
Gebruik voor deze opdracht de use case beschrijving **UC04_PrinterOnderhouden**, welke je hebt gekregen na de opdracht uc-3dprinter.

UC05_ExtruderLeegmaken en UC06_ExtruderLadenMetNieuwMateriaal lijken erg op elkaar (de extruder beweegt alleen de andere kant op). Ze worden daarom uitgevoerd door `ExtruderLadenOfLegenControl`. Een boolean `bLaden` bepaalt of die control gaat Laden of Legen.

- **Maak de STD van `PrinterOnderhoudControl`**. Je kunt daarbij uitgaan van het volgende raamwerk: [std_PrinterOnderhoudControl_Scaffold.drawio](./std_PrinterOnderhoudControl_Scaffold.drawio)
- **Waarom staat `ExtruderLadenOfLegenControl` er afgebeeld als een composite state**, in plaats van middels een actie zoals `extruderLadenOfLegenControl.startLadenOfLegen(bLaden)`?
- **Wat is er handig aan de convenience functie `toonPrinterOnderhoudMenu`?**  
  Waarom hoeven de bijbehorende acties niet individueel in de STD te worden weergegeven?

## C) ModelSelectControl
Gebruik voor deze opdracht de use case beschrijving **UC02_3DModelSelecteren**, welke je hebt gekregen na de opdracht uc-3dprinter.

**En dit:**

- Maak de STD van `ModelSelectControl`. Je kunt daarbij uitgaan van het volgende raamwerk: [std_ModelSelectControl_Scaffold.drawio](./std_ModelSelectControl_Scaffold.drawio)
- Wat is het voordeel van de convenience functies?
- Wat is het voordeel van de lijst met constantes?
- Waarom mogen ze worden afgesplitst van het diagram?
- Waarom heb je gekozen voor de synchronisatiemechanismen die je gekozen hebt in de interface?
- Waarom heeft het STD een eindnode?
- In welk geval zou je geen eindnode nodig hebben?

Let daarbij op deze [STD citeria](../../../../../leerdoelen/portfolio-items/state-transition-diagram.md)

## Canvas Opdracht
Lever de markdown met het resultaat van deze opdracht in op Canvas bij de opdracht "3D Printer Serie".