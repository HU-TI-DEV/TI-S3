
# Activity Diagrammen
Activity diagrammen geven overzichtelijk weer **wat** het systeem moet gaan doen. Ze kunnen bijvoorbeeld gebruikt worden om usecase beschrijvingen visueel te verduidelijken.

## Criteria 
- Elk activity diagram start met een start node.
- Waar een stap alleen op iets wacht, is dat in principe geimplementeerd met een event (in plaats van een guard).
- Bij decision nodes worden events of guards gebruikt, maar niet beide gemixt.
- Als guards worden gebruikt, gaat het om directe beslissingen.
- Het afbreken van een verzameling activiteiten kan elegant met een "interruptable activity region"
- Een activity kan een eenvoudige action zijn of een compleet ander activity diagram. Geef laatstgenoemde aan dmv omgekeerde drietand of rechthoekige bounds.
- Top level activity diagrammen hebben geen eind-node, maar zijn cyclisch.
- Activity diagrammen die onderdeel uitmaken van een hoger niveau activity diagram hebben wel een eindnode.