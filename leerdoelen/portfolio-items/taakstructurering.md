# Taakstructurering
Taakstructurering bestaat uit 2 delen:
- Het alloceren van prioriteiten aan de taken in een Taakstructureringstabel, zodat de meest tijdkritische taken de grootste kans hebben om hun deadlines te halen.
- Het samenvoegen van zoveel mogelijk taken (voor zover dat niet tot onoverzichtelijkheid leidt) in een Taaksamenvoegingstabel, om het aantal taken en daarmee de kosten van task-switching te beperken.

# Taakstructureringstabel
De taakstructureringstabel heeft de kolommen: Object, Taaksoort, Periode, Deadline, Prioriteit. In de tabel wordt aan elk object al dan niet een taak toegekend.

## Criteria voor de Taakstructureringstabel
- De namen van alle objecten uit de eerdere Object lijst (bij het Object model) zijn vertegenwoordigd in de eerste kolom.
- De deadlines zijn realistisch gekozen: zo groot mogelijk, waarbij het nog net geen probleem of irritatie oplevert.
- Als er sprake is van periodes, worden die groter of gelijk gekozen aan de deadline van de bijbehorende taak.
- De sortering van prioriteiten is omgekeerd aan die van de grootte van de deadlines.
- De mogelijke taaksoorten zijn "Periodiek" "Demand driven" en "Geen".
- Iets wat vrijwel instantaan iets doet, heeft geen eigen taak nodig.
- Iets dat altijd periodiek iets doet, is een periodieke taak.
- Overig is "Demand driven".

# Taaksamenvoegingstabel
De taaksamenvoegingstabel laat zien welke objecten zijn samengevoegd in 1 taak.
## Criteria voor de Taaksamenvoegingstabel
- De taaksamenvoegingstabel heeft kolommen voor (naam van de) Taak, Object(en), Taaksoort, Periode, Deadline, Prioriteit.
- In de objectenkolom staan achter elke taak de objecten opgesomd die zijn samengenomen in de taak.
- Als taken zijn samengevoegd wordt de deadline van de samengevoegde taak gelijk aan de kleinste deadline van de constituerende taken.
- Periodieke taken kunnen alleen samengevoegd worden op grond van Temporele Cohesie als de periodes gelijk zijn.
- In de toelichtende tekst bij de tabel worden de gronden van de taaksamenvoeging beargumenteerd (Control Cohesie, Temporele Cohesie of Sequentiële Cohesie).