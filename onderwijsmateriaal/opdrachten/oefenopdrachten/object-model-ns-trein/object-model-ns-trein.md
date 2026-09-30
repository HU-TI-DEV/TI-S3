# Oefenopdracht Object Model + Object beschrijvingen NS Trein

Beschouw voor een NS-trein de volgende twee usecases:

|                | UC01 - Snelheid beheren                                                                                                                                                                                                       |
| -------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Doel           | Een machinist de snelheid van de trein laten regelen.                                                                                                                                                                         |
| Pre-condities  | De machinist is bij het systeem ingelogd.                                                                                                                                                                                     |
| Post-condities | De trein rijdt op de door de machinist ingestelde snelheid.                                                                                                                                                                   |
| Beschrijving   | 1. Wacht tot de machinist de snelheidsschuif in een andere stand zet.<br/>2. Pas de snelheid van de trein, zo snel als nog comfortabel is, aan naar de nieuw ingestelde snelheid, voor zover toegestaan (zie uitzondering 1). |
| Invariant 1    | Er is een verbinding met het regionale treinverkeersregelcentrum. Via die verbinding komt er informatie binnen over de aanbevolen en maximale snelheid voor het stuk spoor waar de trein zich bevindt.                        |
| Invariant 2    | Zolang de snelheidsschuif een sneller dan toegestane snelheid representeert, knippert een rood lampje.                                                                                                                        |
| Invariant 3    | Zolang de snelheidsschuif een toegestane, doch sneller dan comfortabele snelheid representeert, knippert een geel lampje.                                                                                                     |
| Uitzondering 1 | De snelheid wordt automatisch begrensd op de snelheid die nog net veilig is voor het betreffende stuk spoor.<br/>                                                                                                             |
| Uitzondering 2 | In het geval van een noodstop wordt de snelheid van de trein zo snel mogelijk naar nul gebracht. De usecase "Noodstop maken" neemt dat voor zijn rekening.                                                                    |

---

<br>

|                | UC02-Noodstop maken                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| -------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Doel           | De trein laten stoppen in geval van nood.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| Pre-condities  | Geen. Deze usecase moet altijd werken.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| Post-condities | De trein staat stil.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| Scenario       | Als een van de volgende gevallen optreedt:<br> - Een noodrem-trek wordt gedetecteerd.<br> - Er komt een bericht binnen van het centrale treinverkeersregelstation over een gevaarlijke situatie (bijvoorbeeld een tegenligger of obstakels op het spoor).<br>- De obstakel-sensor voor op de trein heeft een obstakel op het spoor gedetecteerd.<br><br>Dan moet:<br>- moet snelheid van de trein zo snel mogelijk naar nul worden teruggebracht: Aandrijfvermogen naar 0, Noodremsysteem in werking.<br>- moet het voorval worden geregistreerd in een log file (black box).<br>- moet er een bericht op de display van de machinist verschijnen die de aard van de noodstop toelicht. |

---

<br>

**NB:** Eigenlijk zijn dit geen optimale use case beschrijvingen, omdat er nodeloos veel ontwerpbeslissingen zijn opgenomen (het gebruik van een schuif, het knipperen van een rood lampje, het knipperen van een geel lampje). Voor een oefenopgave is dat echter handig, omdat de achteraf vrijgegeven uitwerkingen dan gebaseerd zijn op dezelfde ontwerpkeuzes.

## Object Model + Object beschrijvingen

Werk nu een **Objectmodel** met bijbehorende lijst van **Object beschrijvingen** uit op basis van die twee usecases. Gebruik de methode zoals voorgedaan in [Design like a Robot!](../../../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf).

Let daarbij op deze [criteria](../../../../leerdoelen/portfolio-items/object-model-met-lijst.md).

Probeer het eerst zonder, maar maak vervolgens ook gebruik van de eerder gemaakte [functionele decompositie van de NS](FD_NS.drawio.svg). Welk deel ervan is relevant voor deze opdracht?. Helpt de functionele decompositie bij het ontwerpen van het objectmodel?
