# Oefenopdracht Klassediagram Duivenschreck Instellen

Beschouw het onderstaande object model voor de use case "Instellen" van de duivenschreck:
<img title="" src="objectmodel-duivenschreck-instelcontrol.svg" alt="" width="552">

## Klassediagram + Observer Pattern

Werk nu een **Klassediagram** uit op basis van dit Object Model. Gebruik de methode zoals voorgedaan in [Design like a Robot!](../../../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf). Maak daarbij de TipToets klasse herbruikbaar door toepassing van het Observer Pattern (/ Listener Pattern).

Let daarbij op deze [criteria](../../../../leerdoelen/portfolio-items/klassediagram.md).

Onderstaande usecase geeft een indruk van hoe een en ander werkt.

| **Use case naam**   | *Instellen* |
|---------------------|-------------|
| **Doel**            | Instellen van het Duiven Schreck device |
| **Preconditie**      | De 3 rgb leds geven de actuele instelling weer voor licht, servo en geluid. |
| **Beschrijving**     | **0**. De 3 rgb leds geven de **actuele instelling** weer voor licht, servo en geluid.<br> **1**. Als op tip-toets **"enable"** wordt gedrukt, wordt het instellen **gestart**: de rgb-led voor **"licht"** gaat **geel knipperen**, en wordt gewacht op de volgende tip-toets aanslag.<br> **2**. Als op tip-toets **"enable"** wordt gedrukt, wordt de instelling **lichtEnabled** op **true** gezet, en wordt de rgb-led voor **"licht"** op **groen** gezet. Als daarentegen op **"disable"** wordt gedrukt, wordt de instelling **lichtEnabled** op **false** gezet, en de bijbehorende rgb-led op **rood**. Vervolgens gaat de volgende led (voor servo) geel knipperen.<br> **3**. De instelling voor de instellingen **servoEnabled** en **geluidEnabled** gaan op **soortgelijke manier**.<br> **4**. Na afloop van de keuze voor geluidEnabled: ga terug naar 0. |
