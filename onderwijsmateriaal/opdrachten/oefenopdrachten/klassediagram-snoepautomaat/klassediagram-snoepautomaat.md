# Oefenopdracht Klassediagram Snoepautomaat

Beschouw het onderstaande object model voor de use case "Instellen" van de duivenschreck:
<img title="" src="om-snoepautomaat.svg" alt="" width="552">

## Klassediagram + Observer Pattern + Handler Pattern

Werk nu een **Klassediagram** uit op basis van dit Object Model. Gebruik de methode zoals voorgedaan in [Design like a Robot!](../../../../onderwijsmateriaal/readers/Design%20Like%20a%20Robot!.pdf). Maak daarbij de **Keypad** klasse herbruikbaar door toepassing van het Observer Pattern (/ Listener Pattern). Merk op dat **AfrekenController** en **ArtikelInvoerController** 'terugpraten' naar SnoepverkoopController. Breek de dependency-lussen door het tussenvoegen van abstracte interfaces via welke zij 'terugpraten'. Noem die "IArtikelInvoerControllerListener" en "IAfrekenControllerListener".

Let uiteraard ook op deze [criteria](../../../../leerdoelen/portfolio-items/klassediagram.md).