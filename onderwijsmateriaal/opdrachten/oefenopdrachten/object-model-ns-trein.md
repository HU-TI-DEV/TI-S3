# Oefenopdracht Object Model + Object beschrijvingen NS Trein

Beschouw voor een NS-trein de volgende twee usecases:

||UC01 - Snelheid beheren|
|---|---|
|Doel|Een machinist de snelheid van de trein laten regelen.|
|Pre-condities|De machinist is bij het systeem ingelogd.|
|Post-condities|De trein rijdt op de door de machinist ingestelde snelheid.|
|Beschrijving|De machinist kan middels een schuif de door hem gewenste snelheid instellen. De trein neemt dan zo snel als nog comfortabel is, de door hem ingestelde snelheid aan. Er is een verbinding met het regionale treinverkeersregelcentrum. Via die verbinding komt er informatie binnen over de aanbevolen en maximale snelheid voor het stuk spoor waar de trein zich bevindt. De snelheid wordt automatisch begrensd op de snelheid die nog net veilig is voor het betreffende stuk spoor. Als de machinist toch sneller probeert in te stellen, geeft een knipperend rood lampje dat weer. De machinist kan de snelheid wel hoger instellen dan de maximaal aanbevolen comfortabele snelheid voor het betreffende stuk spoor. Dat wordt dan door een geel knipperend lampje weergegeven.|
|Uitzonderingen|In het geval van een noodstop wordt de snelheid van de trein zo snel mogelijk naar nul gebracht. De usecase "Noodstop maken" neemt dat voor zijn rekening.|

---
<br>

||UC02-Noodstop maken|
|---|---|
|Doel|De trein laten stoppen in geval van nood.|
|Pre-condities|Geen. Deze usecase moet altijd werken.|
|Post-condities| De trein staat stil.|
|Scenario|Als een van de volgende gevallen optreedt:<br> - Iemand trekt aan een noodrem.<br> - Het centrale treinverkeersregelstation detecteert een gevaarlijke situatie (bijvoorbeeld een tegenligger of obstakels op het spoor).<br>- De obstakel-sensor voor op de trein heeft een obstakel op het spoor gedetecteerd.<br><br>Dan:<br>- moet snelheid van de trein zo snel mogelijk naar nul worden teruggebracht: Aandrijfvermogen naar 0, Noodremsysteem in werking.<br>- moet het voorval worden geregistreerd in een log file (black box).<br>- moet er een bericht op de display van de machinist verschijnen die de aard van de noodstop toelicht.|
---
<br>

**NB:** Eigenlijk zijn dit geen optimale use case beschrijvingen, omdat er nodeloos veel ontwerpbeslissingen zijn opgenomen (het gebruik van een schuif, het knipperen van een rood lampje, het knipperen van een geel lampje). Voor een oefenopgave is dat echter handig, omdat de achteraf vrijgegeven uitwerkingen dan gebaseerd zijn op dezelfde ontwerpkeuzes.

## Object Model + Object beschrijvingen
Werk nu een **Objectmodel** met bijbehorende lijst van **Object beschrijvingen** uit op basis van die twee usecases. Gebruik de methode zoals voorgedaan in [Design like a Robot!](../../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf).

Let daarbij op deze [criteria](../../../leerdoelen/portfolio-items/object-model-met-lijst.md).