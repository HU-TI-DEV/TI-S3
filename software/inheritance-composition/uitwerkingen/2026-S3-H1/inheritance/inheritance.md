# Inheritance 

## Inhoudsopgave 

|Inheritance..............................................................................................................................1|
|---|
|Inhoudsopgave.....................................................................................................................1|
|Team....................................................................................................................................1|
|Wat is inheritance in C++?.....................................................................................................1|
|Voor- en nadelen..................................................................................................................2|
|Het Diamant Probleem......................................................................................................2|
|Voordelen.........................................................................................................................2|
|Nadelen............................................................................................................................2|
|Voorbeelden.........................................................................................................................2|
|Hoe gebruik je het in echte projecten?...................................................................................3|
|Bronnenlijst.............................................................................................................................3|



|Team||
|---|---|
|Naam|Functie|
|Yunus Kocaman|Presenteren|
|Dayenne|Presenteren|
|Christien|Schrijven|
|Hidde|Schrijven|
|Sjors|Onderzoek|
|Nick|Presenteren|
|Zakaria|Onderzoek|



## Wat is inheritance in C++? 

#### _Simpel gezegd_ 

Inheritance zet een "parent-child" relatie op tussen classes. De afgeleide class krijgt automatisch de verkrijgbare members van de base class en kan ook zijn eigen members definiëren. 

#### _Declaratie_ 

Wanneer je de klasse hond declareert van de klasse dier, maakt de compiler elke "non-private member" van dier deel van hond. Conceptueel, bevat een hond object een complete dier object als zij eerste deel, gevolgd door nieuwe members die hond toevoegt. Dat is ook te zien in de opdeling van het geheugen: de "base class" zit op de eerste bytes van het afgeleide object, en zijn eigen "members" komen later. Een "pointer" naar hond kan altijd worden geconverteerd in een "pointer" naar dier, omdat het dier deel echt aan de start van het object zit. 

#### _Acces level_ 

Daarnaast heeft elke klasse een access level. Simpel gezegd houdt dat in dat een klasse bestaat uit onderdelen, denk aan variabelen en functies bijvoorbeeld. En die onderdelen hebben kunnen een laagje daaroverheen hebben. Bijvoorbeeld publieke variabelen en functies zijn toegankelijk voor andere klassen om te gebruiken en aan te passen. 

Protected is alleen te gebruiken door andere klassen, als de betreffende klasse overerft van de klasse waar de protected onderdelen zich bevinden. En private is volledig beschermd voor andere klassen. Oftewel alleen toegankelijk voor de klasse waar de onderdelen zijn aangemaakt. 

## Voor- en nadelen 

#### _Het Diamant Probleem_ 

Het diamant probleem gebeurt in c++ bij gelijk <u>durige inheritance wanneer meerdere afgeleide</u> klassen van twee andere afgeleide klassen met dezelfde base class. Dit zorgt voor onduidelijkheid omdat de nieuwe klasse twee kopieën van dezelfde base class krijgt. Dan is member toegankelijkheid onduidelijk. 

C++ lost dit probleem op met virtuele inheritance. Virtuele inheritance zorgt dat maar een gedeelde instantie van de base class bestaat, dan maakt het niet uit hoe vaak het geërfd wordt. 

#### _Voordelen_ 

Inheritance heeft een aan voordelen. Doordat code wordt hergebruikt verminder je dubbele code blokken. Ook Is het Makkelijk uitbreidbaar als je extra eigenschappen aan bepaalde code wil toevoegen. Omdat je hierdoor minder code hebt en het belangrijkste op één centrale plek te vinden is, is de het makkelijk te onderhouden. Ook krijg je hierdoor een hiërarchie tussen je classes. Het zorgt er ook voor dat polymorfisme door virual functies gerund kan worden. 

#### _Nadelen_ 

Toch zijn er ook een aantal nadelen aan inheritance. Zo kan het zijn dat het toch lastiger wordt om bepaalde programma’s te onderhouden. Dit komt doordat als je de base class verandert, gelijk alle dervived classes veranderd. De dervided classes worden hierdoor ook heel afhankelijk van de base. Ook wordt de code lastiger om te lezen, omdat je telkens weer bij een andere class moet kijken. Daarnaast bestaat er een kans dat functies per ongeluk meerdere betekenissen krijgt, waardoor er misverstanden kunnen ontstaan in de verwachtingen van de uitkomst van de code 

## Voorbeelden 

Dan weer terug naar het programmeren van inheritance. Stel we maken de class “dier”. Iets wat elk dier kan doen is geluid maken, dus daar maken we een functie van. 



<img title="" src="attachments\1_inheritance.png" alt="" width="500">


Daarnaast willen we een specifiek dier maken, bijvoorbeeld een hond of een kat. Een hond en een kat maken allebei geluid, maar het geluid zelf is anders. 

In de code pakken we de eigenschappen van de class “Animal” en voegen een extra aparte eigenschap toe. 

<img title="" src="attachments\2_inheritance.png" alt="" width="500">

Als we nu een van deze dieren aanmaken en de functie sound() aanroept, maken ze allebei geluid, maar wel een ander soort geluid. 

## Hoe gebruik je het in echte projecten? 

Overerving is uiteraard ontzettend vaak voorkomend in C++ projecten. Oftewel een voorbeeld vinden was geen probleem. Het eerste voorbeeld is een project waar wij al mee te maken hebben gehad tijdens S3. 

<u>https://github.com/nepbuur1/test_lasergame_2_rework_CleanGUI_godmode</u> 

Pong is een voorbeeldspelletje gemaakt door de HU docent Marius Versteegen. Het spelletje is natuurlijk gebaseerd het oude arcade spelletje uit de 1973. Uit verschillende architectuur onderdelen en code voorbeelden kunnen we duidelijk laten zien waar overerving is toegepast. En hiermee een direct voorbeeld kunnen tonen. Wij pakken alleen de voorbeelden uit "pong_simple_frt". 

#### _Klasse diagram_ 

<img title="" src="attachments\3_inheritance.png" alt="" width="500">

In dit klasse diagram is te zien hoe overerving is toegepast. Vandaag gaan we 1 voorbeeld hieruit pakken. En wij gebruiken "IButtonListener" om te laten zien. (Zie natuurlijk ook in het klasse diagram de holle pijl met de gestippelde lijn tussen "StartPageControl" & "IButtonListener".) 

#### _IButtonListener_ 

Om de relatie beter te begrijp bekijken we eerst de code van "IButtonListener". 
```
// by Marius Versteegen, 2024 #pragma once #include "crt_IButton.h" namespace crt { 

// Note: Forward referencing with IButton because of mutual dependency could have// been avoided if not IButton* but an enum value would be passed to identify the button. 
// But I like to avoid the hassle of bookkeeping enums. 
// Mutual dependency of pure abstract interfaces is perfectly sound. 

class IButton; class IButtonListener { 
    public: virtual void buttonPressed(IButton* pButton)=0; virtual void buttonReleased(IButton* pButton) = 0; 
    }; 
}; 
```
Zie voor de overeenkomsten tussen het klasse diagram en de regels code. 


<img title="" src="attachments\4_inheritance.png" alt="" width="500">


Hier wordt de overerving duidelijk gemaakt. 
```
class StartPageControl : public IButtonListener
```
En vervolgens de uitwerking van de functie "buttonPressed()" binnen in "StartPageControl". 

```
void buttonPressed(IButton* pButton) { ESP_LOGI("pong_simple_frt", "%s", pButton->getButtonName()); if(pButton == pStartPageStartButton) { 

xEventGroupSetBits(eventGroup, eventBitStartPressed); } else { ;// not interested. } } 
```

Hier kun je zien dat "StartPageControl.h" in de functie "buttonPressed()" bepaald wat er gebeurt als de knop wordt ingedrukt. In deze specifieke functie wordt eerst de naam van de knop weergeven. Dan wordt er gecheckt of de startKnop ingedrukt. Als dit van toepassing is dan worden de bitjes gezet zodat het startScherm opent. 

#### _Conclusie_ 

Dit project laat zien hoe je overerving kan worden toegepast in C++. Door de button listener kan StartPageControl zelf ook werken als een listener en controleren of de startKnop wordt ingedrukt. 

### Geen compositie maar inheritance 

Wanneer kies je nu eigenlijk? Waarom Gebruik je niet gewoon compositie? Een van de reden om inheritance te gebruiken kan zijn om het gebruik van code te verminderen. Je hoeft bestaande eigenschappen en methoden hierdoor niet opnieuw te implementeren. Ook kun je polymorfisme door middel van inheritance implementeren. Door Polymorfisme kun je verschillende child classes via één parent class behandelen. Daarnaast krijgen child classes direct toegang tot de publieke en protected functionaliteit van de parent. Als laatst creëer je een logische structuur. Je kunt namelijk een algemene klasse maken waar specifiekere klassen van afgeleid zijn. 

#### _Bronnenlijst_ 

GeeksforGeeks. (2025, July 23). _Inheritance ambiguity in C++_ . GeeksforGeeks. https://www.geeksforgeeks.org/cpp/inheritance-ambiguity-in-cpp/ 

GeeksforGeeks. (2026a, May 28). _Diamond Problem in C++_ . GeeksforGeeks. https://www.geeksforgeeks.org/cpp/diamond-problem-in-cpp/ 

GeeksforGeeks. (2026b, June 24). _Inheritance in C++_ . GeeksforGeeks. https://www.geeksforgeeks.org/cpp/inheritance-in-c/ 

GeeksforGeeks. (2026c, June 24). _Inheritance in C++_ . GeeksforGeeks. https://www.geeksforgeeks.org/cpp/inheritance-in-c/ 

Portfolio Courses. (2022, March 10). _Introduction to Inheritance | C++ Tutorial_ [Video]. YouTube. https://www.youtube.com/watch?v=rJlJ8qqVm3k 

Programming Line. (2026, July 18). _C++ Inheritance explained_ . https://learn.programmingline.com/learn/cpp/cpp-inheritance 

