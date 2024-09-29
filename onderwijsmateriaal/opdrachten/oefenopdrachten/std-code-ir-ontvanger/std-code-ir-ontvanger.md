# Opdracht STD naar Code - IR ontvanger
Bij deze opdracht zet je zelf een **STD van een communicatieprotocol** om **naar werkende code**. In dit geval het NEC-infrarood protocol. Superhandig om te hebben - je kunt daarmee je huidige en toekomstige projecten eenvoudig infrarood afstandsbedienbaar mee maken.

- Houd tijdens het maken van deze opdracht in je **logboek** bij waar je tegenaan loopt.
- [Lees hier](../../../../hardware-interfacing/infraroodcommunicatie/infraroodcommunicatie.md) over infrarood communicatie en in het bijzonder over het NEC-protocol.
- Zet [deze](./NEC%20Protocol%20with%20flexibelized%20amount%20of%20bytes-SignalPauseDetector.svg) en [deze](./NEC%20Protocol%20with%20flexibelized%20amount%20of%20bytes-NecReceiver.svg) STDs voor een **NEC-infrarood-ontvanger** om naar code in **CleanRTOS** (het zou kunnen dat er nog ergens een klein foutje in zit, als dat zo is hoor ik het graag).
- **Test** het resultaat met zo'n standaard-cheapo infrarood **afstandsbediening**: als je een cijfer op de afstandsbediening intypt, zie je dat in de console/(serial-)monitor van de pc waar de esp32 aan hangt, verschijnen.
- Lever de uiteindelijke code, inclusief de testcode (de tweede commit) pas in op de bijbehorende canvas opdracht **zodra de test succesvol is**.

Let daarbij op deze [criteria](../../../../leerdoelen/portfolio-items/code.md).

## Tips: 
- Gebruik een **logic analyser** om het signaal dat op de input-pin van je microcontroller staat (die is aangesloten op de TSOP IR ontvanger) terwijl je met de afstandsbediening er berichten naartoe stuurt. Dan weet je meteen zeker of die goed is aangesloten en de batterij van je afstandsbediening nog vol is.
- Houd er rekening mee dat deze opdracht meestal **meer dan een middag** in beslag neemt. Vermoedelijk heb je ook de vrijdag nodig.