# Object Model

Een Object Model is een diagram dat laat zien hoe software objecten met afgebakende, eigen verantwoordelijkheden met elkaar samenwerken, zodanig dat requirements waargemaakt worden.

## Criteria

- Begin in principe met per use case een **control object**. Dat is het object dat de regie heeft over de use case.
- De objecten zijn rechthoeken met daarin alleen naam en het juiste **stereotype**. De namen zijn geschreven in **klasse naam stijl** (PascalCase).
- De relaties tussen de objecten zijn pijlen met daarnaast **wat ze tegen elkaar "zeggen"**, aan elkaar geschreven in **"functienaam-stijl"** (camelCase).
- Wat ze tegen elkaar zeggen zijn **mededelingen** - knopIngedrukt(knopId), **commando's** - activeerSolenoid, of **vragen** - isKnopNeer. (en dus **NIET** knop(knopId) of solenoidActivatie())
- Als er informatie **gevraagd** wordt, gebruik dan **return value** ipv functieparameter. Niet getTemperature(temp) maar getTemperature().
- **Meegegeven informatie** bij een mededeling of commando wordt **tussen haakjes** meegegeven, zoals bij:
  knopIngedrukt(knopId) 
- De functieattribuut van die meegegeven informatie reflecteert de **betekenis**, **niet het type**.
  Dus niet knopIngedrukt(int), maar knopIngedrukt(knopId).
- Laat wat er tegen een ander object "gezegd wordt" van toepassing zijn **op het object dat het dichts bij boundary staat of boundary is**. Zeg dus niet tegen het object RodeLamp "onveiligeSituatieGedetecteerd", maar "enable" of "gaAan". Een Knop zegt daarentegen tegen een control object "knopIngedrukt(knopId)" ipv "gaLinksOfRechts(knopID)". Daardoor maximaliseer je herbruikbaarheid.
- In ieder geval **een control object per use case**.
- Een object model gaat altijd over de software van **één** computer.
  communiceren meerdere computers met elkaar, dan gaat dat via **proxy** objecten. Bijvoorbeeld een "CloudStorageProxy".
- Je wilt in principe **geen berichten met alleen 1 bool parameter**.
  dan liever twee berichten. bijv. enable, disable.
- Zorg dat **namen in objectmodel aansluiten bij de use case** waarvan afgeleid wordt.
  uc instellen -> InstelControl
  uc afrekenen -> AfrekenControl
- Laat de **directeuren niet pollen**. laat de **boundary sensor** objecten dat **zelf doen**. de sensoren sturen in de regel dus informatie (uitgaande **peilen vanuit de sensor**), ipv dat anderen er expliciet om vragen.

# Object lijst

Een lijst met de in het Object Model gebruikte objecten.

## Criteria

- Zet in de beschrijving van de objecten puur wat hun **eigen** verantwoordelijkheid is, los van de rest van het syteem.
  - Dus niet: "ButtonA stuurt buttonpressed berichten naar ControllerB". Maar wat het zelf doet, zonder expliciet andere objecten uit het systeem te noemen: ButtonA representeert de softwarekant voor een drukknopje welke automatisch terugveert als je het loslaat. 
