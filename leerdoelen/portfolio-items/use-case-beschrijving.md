# Use Case beschrijving

Een tabel met de eigenschappen van een use case.

## Criteria

- Als je een use case verzint, begin dan met een (hoog) **(eind-) doel**. De usecase is een reeks acties om een dat doel te bereiken.
  Dus niet "aanzetten", "wielen laten draaien", "kaart weergeven", maar "traject navigeren".

- Andere usecases afsplitsen als de use case beschrijving te groot wordt.

- De zo **afgesplitse use cases** linken aan de bron use case in het use case diagram via **extend** of **include** relaties.

- Alternatief kan een reden zijn usecases af te splitsen als er dingen "**parallel**" moeten gebeuren. Want uiteindelijk wil je dat het scenario van een enkele usecase door een enkele taak uitgevoerd kan worden.

- Stapsgewijze beschrijving van scenario(s) -
  Doe alsof het systeem al bestaat en **beschrijf vanuit het systeem** de interacties met de actors, en welke stappen het doorloopt.

- **Nummer** de stappen bij voorkeur.

- Houd de stappen **klein en concreet**. Dus NIET: "kan met knopjes worden ingesteld", maar "1. wacht op een knopdruk".    "2. als het de spatie was, dan .. , als het .. ", etc.

- Voldoende **gedetailleerd** - zodat duidelijk is wat / welk gedrag er gemaakt moet gaan worden.

- Beschrijving van het **doel** van de usecase.

- Voldoende **specifiek**. Niet "de actor", maar "de machinist".

- **Uitzondering** alleen als er iets gebeurt wat eigenlijk **niet de bedoeling** was.

- Geef bij een **uitzondering** ook aan wat er in dat geval dan **wel** gebeurt.

- **Pre en Postconditie** typisch als de use case **deel uitmaakt** van een grotere, omvattende use case.

- **Invariant** om continue herhaling van dezelfde als-dan te voorkomen, of om aan te geven dat er iets parallel gebeurt.

- De naam van use case benadrukt de **functie**, dus **werkwoordelijk**. Dus niet: "Instellingen" maar "Instellen".

- Noem in use case beschrijving **niet** "het systeem" of "het apparaat". NIET het systeem wacht 5 minuten maar: na 5 minuten .. of .. wacht 5 minuten.

- Noem in use case beschrijving **niet** nodeloos (software) componenten.
  NIET start een timer van 5 minuten maar: na 5 minuten ..
  NIET start de steppermotor om de arm naar links te bewegen maar: de arm wordt naar links bewogen.

- NB: liefst zou je elke use case beschrijving in **twee smaken** hebben: eentje vanuit de gebruiker geformuleerd: "druk op knop A" en eentje vanuit het systeem: "wacht tot knop A is ingedrukt". De eerste variant is geschikter om te communiceren met de klant, de tweede is geschikter om te communiceren met de developers. Maar vanuit het oogpunt van beperkte tijd kiezen we bij onze cursus voor de tweede variant.
