# Code

## Criteria 
- **In sync** met het klassediagram en STD, waar van toepassing.
- Elke **`<<isActive>>`** klasse moet **afgeleid** zijn van (CleanRTOS) Task, en heeft een **main()** functie met een infinite loop.
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