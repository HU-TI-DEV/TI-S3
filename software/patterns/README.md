# Design Patterns <!-- omit in toc -->

Bron: V2CPSE2 reader, TI, HU.nl

- [Introductie](#introductie)
- [1. Adapter (klasse)](#1-adapter-klasse)
- [2. Command](#2-command)
- [3. Composite](#3-composite)
- [4. Decorator](#4-decorator)
- [5. Dirty Flag](#5-dirty-flag)
- [6. Double Buffer](#6-double-buffer)
- [7. Factory](#7-factory)
- [8. Flyweight](#8-flyweight)
- [9. Game Loop](#9-game-loop)
- [10. Listener (Observer)](#10-listener-observer)
- [11. MVC](#11-mvc)
- [12. NVI](#12-nvi)
- [13. Proxy](#13-proxy)
- [14. RAII](#14-raii)
- [15. Rule-of-3](#15-rule-of-3)
- [16. SFINAE](#16-sfinae)
- [17. Singleton](#17-singleton)
- [18. Update Method / State Machine](#18-update-method--state-machine)
- [19. Handler pattern](#19-handler-pattern)


## Introductie
Design Patterns zijn manieren om code te structureren. Deze patterns hebben hun waarde in software ontwikkeling bewezen. Hieronder worden  Design Patterns en andere programmeerstrategieën besproken.

## 1. Adapter (klasse)
Een adapter-klasse wordt gebruikt om de interface van een bestaande klasse aan te passen zodat deze compatibel wordt met een andere interface die de client verwacht.
Denk in de fysieke wereld aan stroomadapters voor  mobiele telefoons: alle adapters leveren dezelfde functionaliteit (stroom) maar de stekkers kunnen verschillen (interface voor telefoontype).

## 2. Command
Het command pattern slaat een actie op als object (waarde), zodat die uitgevoerd kan worden op een ander moment dan waarop de actie ontstaat. Je gebruikt dit bijvoorbeeld om een commando op te slaan in een event queue, maar je kunt het ook gebruiken om alle commando’s die een gebruiker heeft uitgevoerd op te slaan, zodat je ze later kan herhalen. Als je dan het laatste commando negeert heb je een ‘undo’ feature.

## 3. Composite
Een composite is een object dat samengesteld is uit meerdere objecten. Het gedrag is de som van de objecten. Een voorbeeld is een schermobject dat samengesteld is uit een aantal (eenvoudigere) schermobjecten.

## 4. Decorator
Een decorator is een klasse die met behulp van een onderliggend object dat een gegeven interface implementeert, dezelfde interface biedt, maar met een veranderde of toegevoegde functionaliteit. Denk bijvoorbeeld aan een window met een draw_pixel(x,y,p) functie, waarbij de decorator zorgt dat alle schrijfacties in spiegelbeeld op de onderliggende window worden afgebeeld.

## 5. Dirty Flag
Vermijdt (her) berekening van eenzelfde waarde door de oude waarde op te slaan. Je hebt dan een Dirty Flag nodig om te weten of je de waarde opnieuw moet berekenen.

## 6. Double Buffer
Als je tijdens het bijwerken van gegevens niet geconfronteerd wil worden met een onvolledige versie van die gegevens pas je double buffering toe: er zijn twee buffers, waarvan telkens de ene wordt opgebouwd terwijl de andere gebruikt wordt.
Reader V2CPSE2 - 83

## 7. Factory
Een factory is een functie die afhankelijk van run-time gegevens verschillende typen objecten terug kan geven. In C++ betekent dit dat de factory functie een (smart) pointer teruggeeft naar de superklasse van de klassen die hij kan creëren.

## 8. Flyweight
Het flyweight pattern reduceert de omvang van (een groot aantal) objecten door de gemeenschappelijke delen niet in ieder object onder te brengen, maar in ieder object een referentie naar een gedeeld ‘template’ object op te nemen. Hetzelfde principe kan toegepast worden om de hoeveelheid code die geproduceerd wordt door verschillende instanties van een template te beperken door de gemeenschappelijk functies onder te brengen in een (niet template) superklasse.

## 9. Game Loop
Een game loop is de standaard manier om een spel te realiseren waarin de game-play (en het renderen van het beeld) doorloopt als de gebruiker niets doet, zonder multi-threading te gebruiken. Om dit te bereiken wordt na het afhandelen van input van de gebruiker de gamesituatie bijgewerkt (physics engine, autonomous characters, etc.). In de meest eenvoudige vorm gebeurt dit met een vaste hoeveelheid game-time per iteratie van de game-loop. Een complexere implementatie past de de hoeveelheid verstreken game-time per loop iteratie aan naargelang de snelheid van het systeem, zonder daarbij de realiteit van de bijwerking aan te tasten.

## 10. Listener (Observer)
Het listener pattern zorgt ervoor dat de code die een event detecteert niet hoeft te weten *welke* code dat event afhandelt. Dat zou verkeerd-om zijn: dan heeft de low-level toepassings-onafhankelijke code weet van de applicatie-specifieke code.
In plaats daarvan meldt de verwerkende code zich (als Listener) aan bij de detecterende code. De verwerkende code moet zich daartoe conformeren aan een bepaalde interface, die door de detecterende code is voorgeschreven.
Dit pattern gebruik je dus om te voorkomen dat een low-level (library) klasse afhankelijk is van een higher-level (applicatie) klasse, of om een wederzijdse (of circulaire) afhankelijkheid te doorbreken.

## 11. MVC
Het Model View Controller pattern schrijft voor dat de gegevens (Model), de manier waarop die gegevens aan de gebruiker worden getoond (View) en de manier waarop de gebruiker die gegevens kan wijzigen (Controller) gescheiden moeten worden. Dit pattern wordt veel toegepast in webapplicaties, vooral als meerdere applicaties of onderdelen van applicaties met dezelfde data moeten werken.

## 12. NVI
Het Non-Virtual Interface pattern schrijft voor dat de interface functies van een klasse die bedoeld is om te subklassen niet virtual moeten zijn. In plaats daarvan moeten die een projected virtual function aanroepen, en dat is de functie die een subklasse implementeert. Dit maakt het mogelijk dat de publieke interface anders is dan de implementatie interface. Dit kan handig zijn om duplicatie van code in alle implementaties te voorkomen, bijvoorbeeld het checken van parameters.

## 13. Proxy
Een proxy is een object dat optreedt als een plaatsvervanger voor een ander object. Het proxy object biedt dezelfde interface, en sluist alle gebruik van die interface door naar het eigenlijke object. Een proxy object wordt vaak gebruikt om een object op afstand te gebruiken: het proxy object en het eigenlijke object leven dan op verschillende computers, en een verzoek dat bij de proxy binnenkomt wordt via een communicatiekanaal doorgegeven naar het eigenlijke object (en resultaten worden teruggestuurd naar de proxy, die ze aan de aanroeper doorgeeft).

## 14. RAII
Dit is een *C++-specifiek pattern*. RAII houdt in dat een tijdelijke resource (bijvoorbeeld een gealloceerd stuk geheugen, of een file handle) wordt ondergebracht in een variabele waarvan de levensduur overeenkomt met de tijd dat de resource nodig is. De destructor van de variabele zorgt voor het vrijgeven van de resource. Hierdoor is het tijdig vrijgeven van de resource verzekerd, ook als het stuk code verlaten wordt op een bijzondere manier (bijvoorbeeld door een exceptie).

## 15. Rule-of-3
Dit is een *C++-specifiek pattern*. Als je een klasse schrijft die een resource (bijvoorbeeld gealloceerd geheugen) beheert, dan moet je deze resource 1) in de constructors reserveren, 2) in de destructor vrijgeven, en 3) in de assignment operator zorgen dat er geen dubbele verwijzingen en/of lekken ontstaan. De rule-of-3 wordt soms zo geformuleerd: Als je de noodzaak voelt 1 van deze drie soorten functies te schrijven, dan is er een grote kans dat je de andere 2 ook moet schrijven. De regel van 3 is in sommige gevallen achterhaald door het gebruik van RAII en smart pointers, die er beiden voor kunnen zorgen dat de default constructor voldoende is.

## 16. SFINAE
Dit is een *C++-specifiek principe*: bij het bepalen welke template specialisaties gebruikt gaat worden voor een ‘aanroep’ van een template, is het geen probleem als er bij het expanderen van de template header van die specialisatie iets ‘niet klopt’. Subsitute Failure Is Not An Error, maar betekent alleen dat de betreffende specialisatie dus geen kandidaat is om gebruikt te worden. Dit wordt veelvuldig gebruikt om een voor een specifiek geval passende template specialisatie te selecteren (of eigenlijk: de niet passende specialisaties uit te sluiten).

## 17. Singleton
Soms is het lastig om een object dat je overal nodig hebt en waarvan er maar 1 kan (en mag) bestaan aan iedere functie die het nodig heeft als parameter door te geven. Bekende voorbeelden zijn de printer, het beeldscherm, en de console. Het singleton pattern biedt een centrale plaats waar (een referentie of pointer naar) het betreffende object kan worden opgevraagd. Dit biedt als voordeel boven een globaal object dat als het object nooit wordt aangevraagd het ook niet aangemaakt hoeft te worden. Het singleton pattern is omstreden, omdat het een verborgen interface is van de code die er gebruik van maakt.

## 18. Update Method / State Machine
Als meerdere onderdelen van je code onafhankelijk van elkaar dingen doen en daartussen wachten op evenets of het verstrijken van tijd dan kun je die onderdelen coderen als aparte taken. Maar als je geen multitasking beschikbaar hebt dan moet je de activiteiten van die onderdelen onderbrengen in een update() functie, die wordt aangeroepen als er een event voor dat onderdeel is. De update() functie moet dan het nodige doen, zonder te gaan staan wachten.

## 19. [Handler pattern](handler_pattern.md)