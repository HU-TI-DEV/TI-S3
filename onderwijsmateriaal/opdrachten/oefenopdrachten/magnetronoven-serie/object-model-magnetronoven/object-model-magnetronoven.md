# Oefenopdracht Object Model + Object beschrijvingen Magnetronoven

We willen een Magnetronoven ontwerpen op basis van het volgende usecase diagram:
<img title="" src="ucd-magnetronoven.svg" alt="" width="552">

In onderstaande tabellen staan de usecases toegelicht:

## Usecases

| Naam         | Usecase Instellen                                                                                                                                                                                                                                                                                                                                                                                                       |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Beschrijving | * Wacht tot de deur gesloten is. <br/>* Wacht tot de kop "instellen" is ingedrukt<br/>* De display laat zien: "kies een tijd".<br/>* Via Tiptoetsen wordt een tijd ingevoerd, afgesloten met de knop "instellen".<br/>* De display laat zien: "kies een vermogen"<br/>* Via Tiptoetsen wordt een vermogen tussen de 0 en 2000 wattt ingetypt, afgesloten met de knop "instellen".<br/>* De usecase koken wordt gestart. |
| Preconditie  | De usecase koken is niet actief.                                                                                                                                                                                                                                                                                                                                                                                        |
| Postconditie | De usecase koken is actief.                                                                                                                                                                                                                                                                                                                                                                                             |
| Uitzondering | Als de deur wordt geopend, weer terug naar het begin.                                                                                                                                                                                                                                                                                                                                                                   |

| Naam         | Usecase Koken                                                                                                                                                                                                                       |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Beschrijving | * Start de ingestelde countdowntijd.<br/>* Stel de magnetronstraler in op het ingestelde vermogen. <br/>* De display laat de aftellende tijd zien.<br/>* Er klinkt een "ping" geluid<br/>* De magnetronstraler wordt uitgezet.<br/> |
| Preconditie  | De deur is gesloten en de instelling is afgerond                                                                                                                                                                                    |
| Postconditie | Het product is opgewarmd.                                                                                                                                                                                                           |
| Uitzondering | Als de deur geopend wordt, wordt de magnetronstraler uitgezet, en stopt het aftellen. Zodra de deur weer gesloten is, wordt de magnetronstraler weer aangezet op het ingestelde vermogen en wordt het aftellen voortgezet.          |

## Object Model + Object beschrijvingen

Werk nu een **Objectmodel** met bijbehorende lijst van **Object beschrijvingen** uit op basis van die twee usecases. Gebruik de methode zoals voorgedaan in [Design like a Robot!](../../../../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf).

Let daarbij op deze [criteria](../../../../../leerdoelen/portfolio-items/object-model-met-lijst.md).