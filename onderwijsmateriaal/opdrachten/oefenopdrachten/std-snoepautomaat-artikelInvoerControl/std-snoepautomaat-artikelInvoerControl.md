# Oefenopdracht State Transition Diagram Snoepautomaat Artikelinvoer

Het invoeren van een getal is een usecase dwelke je vermoedelijk nog vaak zult tegenkomen. Bij deze opdracht ga je daar voor eens en altijd een STD voor ontwerpen.

Beschouw het onderstaande object model van de snoepautomaat:
![ObjectModel SnoepAutomaat](./om-snoepautomaat.svg)
.. of beter: gebruik de uitwerking van het klassediagram die je hebt gekregen op canvas om jezelf na te kijken bij de opdracht [klassediagram snoepautomaat](../klassediagram-snoepautomaat/klassediagram-snoepautomaat.md), als je die hebt.

## State Transition Diagram

Gegeven is de volgende usecase beschrijving van de ArtikelVerkoopController:

|Use case naam| Artikelnummer Invoeren|
|---|---|
|Beschrijving|1. Initialiseer **getal = 0**.<br> 2. Clear de display en **Toon** vervolgens "type een artikelnummer: ", gevolgd door het getal.<br> 3. Wacht op een **toetsdruk**.<br> 4. a. Als het een **cijfertoets** is: **getal = getal * 10 + "cijferwaarde van cijfertoets"**, **toon** getal op display en goto 3.<br>.....b. Als de **"enter"** toets is ingedrukt, **clear** display, het **huidige getal** kan dan als **artikelnummer** worden gemeld.<br> .....c. Als de **"del"** toets is ingedrukt, **getal = getal / 10**, goto 3.<br> .....d. Als de **"clear"** toets is ingedrukt, zet getal op 0 en goto 3.<br> .....e. Als de **"cancel"** toets is ingedrukt, wordt -1 als artikelnummer gemeld.<br> .....f. Als een andere toets is ingedrukt, negeer die dan. |
|Uitzondering| Zodra er **gedurende 10 seconden** geen toets is ingetypt, breek dan de artikelinvoer af en **notificeer de timeout**.

NB: je mag ervan uitgaan dat ArtikelInvoerController een eigen taak heeft. Hij wacht dus op het bericht startInvoer om een nieuwe invoer te starten en doet **vervolgens pas** het bovenstaande.

Werk nu op basis van het bovenstaande een **State Transition Diagram** voor de klasse ArtikelInvoerController uit. Gebruik de methode zoals voorgedaan in [STD hoofdstuk van deze ppt](../../../../programma/lesprogramma/files/Operating_Systems.pptx). 

Let daarbij op deze [criteria](../../../../leerdoelen/portfolio-items/state-transition-diagram.md).


