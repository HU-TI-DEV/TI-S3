# Use Case diagram

Een diagram waarin overzichtelijk relaties tussen use cases en actoren wordt weergegeven.

## Criteria

- De systeemgrens wordt met een rechthoek aangegeven.
- Menselijke actoren worden aangegeven als poppetjes.
- Actoren staan buiten de systeemgrens.
- Niet-menselijke actoren worden aangegeven als rechthoek met naam erin (bijvoorbeeld omgevingstemperatuur) met daarboven het stereotype `<<actor>>`.
- Usecases onderling correct relateren middels `<<include>>` en `<<extend>>` waar nodig (alleen hierarchische functionele afhankelijkheid vormt het bestaansrecht van zo'n relatie).
- `<<include>>` relaties impliceren dat de usecase aan het uiteinde van de pijl altijd wordt uitgevoerd, vanuit en als onderdeel van de usecase aan het begin van de pijl.
- `<<extend>>` relaties impliceren dat de usecase aan het begin van de pijl optioneel wordt uitgevoerd, vanuit en als onderdeel van de usecase aan het eind van de pijl.
- Zodanig definieren de relaties tussen de usecases een functionele hierarchie.
- Een actor verbonden via een lijn (zonder pijlpunten) met zo'n usecase impliceert dat die actor mogelijk ook interacteert met de usecases in de hierarchie onder de betreffende usecase, dus zijn extra lijnen vanuit die actor naar die hierarchie onder de usecase waarmee hij verbonden is, niet nodig.
- Alle usecases die staan aan de top van een hierarchy, moeten gerelateerd zijn aan tenminsten 1 actor.