# Object Model

Een Object Model is een diagram dat laat zien hoe software objecten met afgebakende, eigen verantwoordelijkheden met elkaar samenwerken, zodanig dat requirements waargemaakt worden.

## Criteria

- De objecten zijn rechthoeken met daarin alleen naam en het juiste **stereotype**. De namen zijn geschreven in **klasse naam stijl** (PascalCase).
- De relaties tussen de objecten zijn pijlen met daarnaast **wat ze tegen elkaar "zeggen"**, aan elkaar geschreven in **"functienaam-stijl"** (camelCase).
- In ieder geval een control object per use case.

# Object lijst

Een lijst met de in het Object Model gebruikte objecten.

## Criteria

- Zet in de beschrijving van de objecten puur wat hun **eigen** verantwoordelijkheid is, los van de rest van het syteem.
  - Dus niet: "ButtonA stuurt buttonpressed berichten naar ControllerB". Maar wat het zelf doet, zonder expliciet andere objecten uit het systeem te noemen: ButtonA representeert de softwarekant voor een drukknopje welke automatisch terugveert als je het loslaat. 
