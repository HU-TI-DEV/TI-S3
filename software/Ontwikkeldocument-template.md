``Tussen backticks als deze staan cues voor het invulling geven aan de topics. Verwijder ze uiteindelijk. Dit ontwikkeldocument is bedoeld als overdrachtsdocument en naslagwerk, voor de opdrachtgever, voor eventuele toekomstige teams die verder werken aan het product, maar ook tijdens de ontwikkeling voor het huidige team. Probeer de huidige staat van de ontwikkeling altijd zo goed mogelijk gesynct te houden met het ontwikkeldocument, zodat die ook helder is voor alle teamleden. Belangrijke Tip: Een valkuil om op verdacht te zijn, is dat het ontwikkeldocument een losse verzameling van ingevulde hoofdstukjes wordt. Dat willen we dus niet. Er dient overal voldoende en heldere tekst toegevoegd te zijn die logica en samenhang (zoals tussen de opeenvolgende hoofdstukken, of voor wat betreft gemaakte keuzes) uitlegt. Tot en met het ontwerp moet het zonder extra mondelinge toelichting duidelijk, samenhangend en makkelijk leesbaar zijn voor een gemiddelde persoon met slechts lichte it-kennis. Een deel van de ontwikkeldocumentatie is afgesplitst van dit document: documentatie t.a.v. het ontwerp en realisatie van het web-subysteem (flask, mongodb, html, css, javascript) is afgesplitst in een apart, ietwat ander type ontwikkeldocument. Ander belangrijk ding: gebruik alleen links naar publieke websites of relatieve links (dus binnen de team-repo, NIET naar je persoonlijke repo), zodat uiteindelijk uit de team-repo een zip gemaakt kan worden voor de opdrachtgever, waarvan de links (nog) werken.``

# Ontwikkeldocument Project ``projectnaam``

Versie ``bla.bla.bla``
Team ``naam``

## Inhoudsopgave

- [Inleiding](#inleiding)
- [Leeswijzer](#leeswijzer)
- [Uitgangspunten](#uitgangspunten)
  - [Systeem Context](#systeem-context)
  - [Identificatie en prioritering van Key Drivers](#identificatie-en-prioritering-van-key-drivers)
- [Requirements](#requirements)
  - [Functionele Requirements](#functionele-requirements)
  - [Niet-Functionele Requirements](#niet-functionele-requirements)
  - [Constraints](#constraints)
  - [Use Cases](#use-cases)
  - [Activity Diagrammen](#activity-diagrammen)
  - [Requirements Traceability Diagrammen](#requirements-traceability-diagrammen)
- [Ontwerp](#ontwerp)
  - [Functionele Decompositie](#functionele-decompositie)
  - [Object Modellen](#objectmodellen)
  - [Lijst met Objecten](#lijst-met-objecten)
  - [Taakstructurering](#taakstructurering)
    - [Taaksoort en deadline](#taaksoort-en-deadline)
    - [Taken samenvoegen](#taken-samenvoegen)
  - [Klassediagrammen](#klassediagrammen)
  - [STD's](#stds)
- [Realisatie](#realisatie)
  - [Fysieke View](#fysieke-view)
  - [Code](#code)
  - [Unit-Tests](#unit-tests)
  - [Integratie-Tests](#integratie-tests)
  - [Eindresultaat](#eindresultaat)
- [Conclusie en Advies](#conclusie-en-advies)
- [Appendices](#appendices)
  - [Appendix 1: Mindmaps](#appendix-1-mindmaps)
  - [Appendix 2: Gespreksverslagen](#notities-bij-kickoff-meeting)
  - [Appendix 3: Verbeteronderzoeksverslagen](#appendix-3-verbeteronderzoeksverslagen)
  - [Appendix 4: Referenties](#appendix-4-referenties)

## Inleiding

``Van wie komt de opdracht? Waar gaat de opdracht in hoofdlijnen over? Leg verder uit dat dit document bedoeld is om op heldere wijze overzicht en samenhang te geven voor het team tijdens het werken aan het project, en na afloop als overdrachts-document voor eventuele follow-ups.``

## Leeswijzer

``leg uit wat er in de hoogste-niveau-hoofdstukken wordt behandeld en hoe deze onderwerpen met elkaar in verband staan``

## Uitgangspunten

``Leg uit dat dit hoofdstuk de uitgangspunten voor de requirements inventariseert. Verwijs naar een appendix met genoteerde input (verslag van speech, gespreksverslagen) van de opdrachtgever - (de echte, tijdens de kickoff-meeting of diens vervanger (Marius,Bart) erna) ``

### Systeem Context

``Modelleer en beschrijf de Systeem Context – gebruik een systeem context diagram. Onderdelen van binnen je System of Interest horen er niet in thuis. Een decompositie van je systeem ook niet. Zijn er geen belangrijke actoren vergeten? Tip: maak eerst met je team een mindmap (zie appendix)``

### Identificatie en prioritering van Key Drivers

``Voor semester 3 beperken we ons tot 3 stakeholders: opdrachtgever, klant en gebruiker. Geef middels een tabel een overzicht van de key drivers weer. Belangrijkere key drivers staan hoger in de tabel. Er is ook een kolom die aangeeft voor welke stakeholder het van toepassing is, en een kolom voor omschrijving. Licht de ordening van de key drivers toe in de begeleidende tekst.``

## Requirements

``leg uit hoe de requirements opgesteld worden door de samenhang te verwoorden van de onderwerpen uit de sub-hoofdstukken.``

### Functionele Requirements

``Beschrijf de relevante functionele requirements``

| Naam                | ``F01 - Houvast``                                       |
| ------------------- | ------------------------------------------------------- |
| Omschrijving        |                                                         |
| Rationale           | ``reden, verband met key driver of parent-requirement`` |
| Business prioriteit | ``MoSCoW``                                              |

``etc..``

### Niet-Functionele Requirements

``Beschrijf de relevante Niet-Functionele Requirements``

| Naam                | ``NF03 - Betrouwbaarheid``                                                                                                           |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| Omschrijving        | ``quantificeerbare of anderszins meetbare omschrijving ``                                                                            |
| Rationale           | ``reden: wat zou er anders mis gaan?``                                                                                               |
| Business prioriteit | ``MoSCoW. Deze regel alleen gebruiken bij niet quantificeerbare opdrachtgever-bepaalde ontwerp/realisatie keuzes, anders weglaten.`` |

``etc..``

### Constraints

``Beschrijf de relevante Constraints``

| Naam         | ``C02 - Jaarlijkse onderhoudskosten``                     |
| ------------ | --------------------------------------------------------- |
| Omschrijving | ``quantificeerbare of anderszins meetbare omschrijving `` |
| Rationale    | ``reden: waarom kan het niet anders?``                    |

### Key Driver Graph

``Zet op deze plek de Key Driver Graph. Een horizontaal weergegeven hierarchie die de onderlinge afhankelijkheden tussen key drivers, derived application drivers, functionele en non-functionele requirements``.

### Use Cases

`` Een of meerdere use case diagram(men) met bijbehorende use case beschrijvingen ``

| Naam           | ``UC04 - Lamp Selecteren``                                                                                                                                                                                                                 |
| -------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Actor          | ``gebruiker``                                                                                                                                                                                                                              |
| Samenvatting   | ``evt. een beschrijving, voor zover de naam het niet al voldoende dekt``                                                                                                                                                                   |
| Preconditie    | ``alleen voor zover niet triviaal. typisch alleen nodig indien onderdeel van een parent-usecase, bijvoorbeeld "Lamp Selectie Menu" is geselecteerd in het hoofdmenu``                                                                      |
| Scenario       | ``voorbeeld van een typische volgorde van interacties, bij voorkeur geschreven vanuit het gezichtspunt van het systeem.``                                                                                                                  |
| Scenario 2     | ``... indien nodig additionele``                                                                                                                                                                                                           |
| Invariant      | ``Iets waarvoor het systeem voortdurend zorgt, waardoor dat niet steeds herhaald hoeft te worden. (kan soms van toepassing zijn. Bijvoorbeeld: 'ten alle tijde kan "apply" worden geselecteerd om aangepaste eigenschappen op te slaan')`` |
| Postconditie   | ``alleen voor zover niet triviaal. typisch alleen indien onderdeel van parent-usecase. bijvoorbeeld teruggekeerd naar het parent menu``                                                                                                    |
| Uitzonderingen | ``alleen als er tijdens het scenario iets gebeurt wat niet in lijn is met de oorspronkelijke bedoeling van de usecase.``                                                                                                                   |

### Activity Diagrammen

`` Voor belangrijke, wat complexere usecases kan het extra verduidelijking opleveren om er SysML - activity diagrammen bij te maken. ``

### Requirements Traceability Diagrammen

`` Laat met een Traceability diagram het verband zien tussen requirements (die ook onderling hierarchisch verband kunnen hebben), usecases en klassen. Die klassen worden pas later tijdens de ontwerpfase bekend. Initieel kun je de kolom voor klassen dus leeg laten. Ook het toevoegen van een tweede Traceability diagram, maar dan een die de verbanden tussen requirements, usecases en fysieke blocks is aanbevolen. Ook daarvoor geldt dat de fysieke blocks pas later tijdens de ontwerpfase bekend worden. ``

## Ontwerp

``leg uit hoe het ontwerp volgt door het volgen van de stappen die in de sub-hoofdstukken worden behandeld en hoe deze onderwerpen met elkaar in verband staan``

### Functionele decompositie

`` Geef met een functionele decompositie van het systeem grafisch weer hoe de verschillende functies (uit de functionele requirements) van het systeem met elkaar samenhangen. Dat geeft goede handvaten voor de decompositie van software en hardware verder op de rit. ``

### Objectmodellen

`` Ontwerp, uitgaande van use case beschrijvingen en activity diagrammen, de delen van het objectmodel die dat kunnen waarmaken. Beperk de interactie met het web-subsysteem tot een enkel object (een web proxy object oid). Een gedetailleerde uitwerking van het web-subsysteem is in een apart ontwikkeldocument te vinden.``

#### Lijst met Objecten

`` Voeg elk object uit de objectmodellen toe in de "lijst met objecten" Let op dat de beschrijvingen niet de relatie tussen de objecten duiden, maar louter wat objecten "los bekeken" doen. Dus niet: InstelControl stuurt een signaal naar .. Maar Instelcontrol is de "dirigent" van de usecase "Instellen" (meteen link toevoegen naar die usecase).``

| Object Naam   | Stereotype | Beschrijving                                                    |
| ------------- | ---------- | --------------------------------------------------------------- |
| InstelControl | Control    | "Dirigent" van de use case "Instellen" (zie use case Instellen) |
| Display       | Boundary   | Stuurt display hardware aan.                                    |
| etc..         |            |                                                                 |

### Taakstructurering

``leg uit wat het doel is van taakstructurering en hoe de deelstappen (sub-hoofdstukken) samen dat doel reliseren``

#### Taaksoort en deadline

`` Maak een tabel die per object taaksoort, deadline, periode en prioriteit weergeeft. Belangrijk: Deadline is zo lang mogelijk waarbij het nog net geen irritatie oplevert. Deadline <= Periode, Prioriteit is omgekeerd evenredig met deadline ``

| Object Naam   | Taaksoort     | Periode | Deadline | Prioriteit |
| ------------- | ------------- | ------- | -------- | ---------- |
| InstelControl | Demand Driven |         | 30ms     | 1          |
| PlusKnop      | Periodiek     | 60ms    | 60ms     | 2          |
| etc..         |               |         |          |            |

#### Taken samenvoegen

`` Maak een tabel waarin je laat zien welke objecten een eigen taak hebben en van welke de taken worden samenvoegd in een enkele "Taak". Noem in het laatste geval het object (bijvoorbeeld een handler) dat eigenaar wordt van die Taak als eerste.``

| Taak Naam  | Object Naam                            | Taaksoort     | Periode | Deadline | Prioriteit |
| ---------- | -------------------------------------- | ------------- | ------- | -------- | ---------- |
| InstelTaak | InstelControl                          | Demand Driven |         | 30ms     | 1          |
| ButtonTaak | <u>ButtonHandler</u> PlusKnop, MinKnop | Periodiek     | 60ms    | 60ms     | 2          |
| etc..      |                                        |               |         |          |            |

### Klassediagrammen

`` Ontwerp, uitgaande van de objectmodellen de bijbehorende klassediagrammen. Vergroot eventueel in latere verbeteringsronden de herbruikbaarheid en het gebruiksgemak van de klassen door het toepassen van geschikte Design Patterns of templating. Voeg de klassen ook toe in de Requirements Traceability diagrammen zodat duidelijk is welke requirements de klasse adresseert``

### STD's

``Ontwerp voor elke Taak de STD van de bijbehorende klasse(n), indien van toepassing vanuit activity diagram of usecase beschrijving, protocol of anderszins. Belangrijk: alle toestanden moeten gerepresenteerd worden in het diagram. Code zonder toestanden en zonder directe invloed op de flow tussen de toestanden kunnen gerepresenteerd worden door calls naar helper-functies. Vergeet niet bovenaan een geschikte STD-interface toe te voegen``

## Realisatie

``leg uit waarin de realisatie zich onderscheidt van het ontwerp, en noem kort de rollen van de subhoofdstukken``

### Fysieke View

``Ontwerp de fysieke decompositie (een SysML Bdd). (de functionele decompositie biedt daarvoor meestal goede aanknopingspunten). Verduidelijk fysieke compositie-relaties middels "Constraints" (NB: dat zijn in dit geval gekwantificeerde ontwerpkeuzes die zowel uit de eerdere constraints als de niet-functionele requirements bestaan.``

### Code

``Ontwerp vanuit de STD's de bijbehorende code. Geef waar nodig additionele toelichting. Voeg per STD een link toe naar de betreffende code in de team repo. Voeg ook links naar de overige code toe``

### Unit Tests

``Voeg in dit hoofdstuk sub-hoofdstukken toe met Unit Tests, elk bestaande uit een Testplan, een link naar de testcode, een samenvatting van de bevindingen van de meest recente uitvoer van die test en een link naar een bestand met die meest recente test-output.``

### Integratie Tests

``Voeg in dit hoofdstuk sub-hoofdstukken toe met Integratie Tests, elk bestaande uit een Testplan, een link naar de testcode, een samenvatting van de bevindingen van de meest recente uitvoer van die test en een link naar een bestand met die meest recente test-output. Belangrijke integratie-tests zijn uiteraard ook de tests van het complete product. Hoe goed doet het product wat het moet doen?``

``Verder zou je in dit hoofdstuk Realisatie ook subhoofdstukken kunnen opnemen met : beslissingstabellen, waarin gemaakte realisatiekeuzes worden verantwoord, Failure Mode Effect Analyses, en andere realisatie gerelateerde overwegingen.``

### Eindresultaat

`` Nog eens op een rijtje de behaalde functionaliteiten en de performance. ``

## Conclusie en Advies

`` Reflecteer op in welke mate de aanvankelijk opgestelde requirements daadwerkelijk zijn behaald. Geef goed onderbouwde aanbevelingen t.a.v. mogelijke toekomstige doorontwikkeling.`` 

## Appendices

### Appendix 1: Mindmaps

`` Bijvoorbeeld voorafgaand aan het maken van het systeem context diagram is een mooi moment om met zijn allen een mindmap te maken die een samenhang duidt van alles wat je als team maar kunt bedenken in relatie tot het systeem. ``

### Appendix 2: Gespreksverslagen

#### Notities bij Kickoff-Meeting

``... etc``

### Appendix 3: Upgradeonderzoeksverslagen

``zet hier een lijst met links naar de upgradeonderzoeksverslagen. Licht het toe met wat tekst met de belangrijkste samenvatttingen ervan.``

### Appendix 4: Referenties

`` lijst 3rd party materiaal waar naar verwezen is. Boeken, site-links.``

`` Verder mogelijk nog appendices over: de geschiedenis van de ontwikkeling van het product in grote lijnen (inclusief inmiddels afgeschoten tussenproducten), over het opzetten van de ontwikkelomgevingen, over hoe te debuggen. Houdt het bij samenvattende dingen. Lange teksten (zoals testuitvoer) niet in de appendices maar via links naar bestanden opnemen.``
