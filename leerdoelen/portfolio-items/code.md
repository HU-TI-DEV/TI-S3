# Code

## Criteria 
- **In sync** met het **klassediagram** en **STD** welke aan de klasse ten grondslag ligt.
- Elke **`<<isActive>>`** klasse moet **afgeleid** zijn van (CleanRTOS) Task, en heeft een **main()** functie met een infinite loop.
- Als je op **meerdere waitables** tegelijk wacht (tot een of meerdere ervan vuren), gebruik dan **waitAny** gevolgd door **hasFired**. hasFired gebruikt de laastste info van een waitAny aanroep.
- Een **enum** om de toestanden mee te duiden.
- **Member** variabelen en references zoals aangegeven in het klassediagram.
- Een **constructor** die eventuele reference members initialiseert en/of **zichzelf als listener** aan members toevoegt en/of **members aanmeldt** bij een handler.
- Voor elke functie uit de **STD interface** moet er een gelijknamige publieke **functie** zijn.
- Duidelijke en consistente **naamgeving**.
- Goed **gepartitioneerd**. Scheiding van functionaliteit over functies en objecten.
- **Niet te lange** functies.
- Goede **opsplitsing** van verantwoordelijkheden.
- **Commentaar** waar nodig: niet wat maar **waarom**.
- **Geen magical constants**.
- **Geen duplicate code**.