![logo](https://www.hu.nl/-/media/hu/afbeeldingen/algemeen/hu-logo.ashx) [](logo-id)

# Semester 3 van Technische Informatica[](title-id)

### Inhoud[](toc-id)

- [Semester 3 van Technische Informatica](#semester-3-van-technische-informatica)
  - [Inhoud](#inhoud)
    - [Een introductie](#een-introductie)
  - [Organisatie](#organisatie)
    - [Programma](#programma)
  - [Onderwijsweek A1 (2-9-2024)](#onderwijsweek-a1-2-9-2024)

---

**v0.1.0 [](version-id)** Semester 3 TI programma door HU IICT[](author-id).

---

## Een introductie

In semester 3 van Technische Informatica

### Organisatie

De contacturen zijn:

* 
* 

Ons lokaal is ....  

De docenten zijn:

* (**TM**) Teun Pieter Moddermann
* (**HS**) Harm Snippe
* (**MV**) Marius Versteegen
* (**HP**) Hagen Patzke
* (**NG**) Nick Goris

## Programma

[(alternatieve view html)](https://hu-ti-dev.github.io/TI-S3/programma/Programma_for_export_html.drawio.html)

### Opstarten

Teams gevormd, Projecten verdeeld, Project board opgezet, kennis gemaakt met de klant, Mindmap gemaakt. Start FR.

#### Week A1 (2-9-2024)

| **Dag** | **Kennissessie**                                                                                                                                  |
| ------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| ma      | <a href="./programmas/programma-kickoff.md">Kickoff - Teamvorming</a>                                                                             |
| di      | <a href="./programmas/programma-klantpraatjes.md">Klant-praatjes (2 klanten). Laat teams key drivers achterhalen</a>                              |
| wo      | <a href="./programmas/programma-systemcontext-keydrivers-applicationdrivers.md">Overige stakeholders (gebruiker) met key drivers, prioriteren</a> |
| do      | {recap FR, NFR}                                                                                                                                   |

### Sprint 1

Advies, in de vorm van Functionele Requirements, Non Functionele Requirements, UCD, UCBeschr, Activity Diagrammen en Functionele decompositie. + ESP32-IDF + mesh operationeel, evt. Hello Worlds van boundary objects.

#### Week A2 (9-9-2024)

| **Dag** | **Kennissessie**                                 |
| ------- | ------------------------------------------------ |
| ma      | {recap UCD, UC beschrijvingen}, Key Driver Graph |
| di      | {recap AD}                                       |
| wo      | ESP32-IDF basic installatie                      |
| do      | {ESP32-IDF mesh installatie + CleanRTOS}         |

#### Week A3  (16-9-2024)

| **Dag** | **Kennissessie**                      |
| ------- | ------------------------------------- |
| ma      | Functionele decompositie              |
| di      | Networking basics                     |
| wo      | Const expressions + Templates, SFINAE |
| do      | RAII                                  |

### Sprint 2

Object Model en klassediagram van het RTOS subsysteem<br>

#### Week A4 (23-9-2024)

| **Dag** | **Kennissessie**           |
| ------- | -------------------------- |
| ma      | Oefening Object Model      |
| di      | Concurrency (pc), mutex    |
| wo      | Oefening Object Model      |
| do      | Oefening Taakstructurering |

#### Week A5 (30-9-2024)

| **Dag** | **Kennissessie**                           |
| ------- | ------------------------------------------ |
| ma      | Oefening Klassediagram                     |
| di      | Oefening Observer Pattern, Handler Pattern |
| wo      | Synchronisatiemechanismen                  |
| do      | {<b>Peil 1</b>}                            |

### Sprint 3

Object Model en klassediagram van het RTOS subsysteem afmaken, implementatie van (gegeven) STD NEC protocol, start implementatie van core functionaliteit van RTOS subsysteem.

#### Week A6 (7-10-2024)

| **Dag** | **Kennissessie**                          |
| ------- | ----------------------------------------- |
| ma      | {CleanRtos, FreeRtos, Logger / Debugging} |
| di      | STD                                       |
| wo      | STD naar code                             |
| do      | Oefening STD                              |

#### Week A7 (14-10-2024)

| **Dag** | **Kennissessie**                                               |
| ------- | -------------------------------------------------------------- |
| ma      | Signalen in het frequentiedomein, fir filter, median filter    |
| di      | pid workshop (ventilatorwip-todo-offshelve-balopplank met TOF) |
| wo      | Flask, MongoDb, NoIP, Reverse Proxy, docker composer           |
| do      |                                                                |

### Sprint 4

RTOS subsysteem klaar, Linux (Lightsail) server met Flask en MongoDb draaiend. Een architectuur gemaakt voor het server-deel.<br>(requirements, usecases,&nbsp; storage model, distributie van functionaliteit over python/flask, html/css en javascript.)

#### Week A8 (21-10-2024)

| **Dag** | **Kennissessie**                       |
| ------- | -------------------------------------- |
| ma      | {HTML, CSS} (pointer naar zelfstudie)  |
| di      | {Javascript} (pointer naar zelfstudie) |
| wo      | Webarchitectuur                        |
| do      |                                        |

#### Week A9 (28-10-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | vakantie         |
| di      | vakantie         |
| wo      | vakantie         |
| do      | vakantie         |

#### Week A10 (4-11-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | Combinatoriek    |
| di      | Karnaugh         |
| wo      | Karnaugh         |
| do      | {<b>Peil 2</b>}  |

### Sprint 5

Webdeel verder klaar en geintegreerd met RTOS subsysteem.

#### Week B1 (11-11-2024)

| **Dag** | **Kennissessie**             |
| ------- | ---------------------------- |
| ma      | Quick and Dirty              |
| di      | Compact and Clean            |
| wo      | Digitale simulatie (logisim) |
| do      |                              |

#### Week B2 (18-11-2024)

| **Dag** | **Kennissessie**                                               |
| ------- | -------------------------------------------------------------- |
| ma      | Bouwen en debuggen van digitale electronica (evt (ook) in plc) |
| di      |                                                                |
| wo      | Recap Rekenen                                                  |
| do      | Recap Electro                                                  |

### Sprint 6

Werkend prototype

#### Week B3 (25-11-2024)

| **Dag** | **Kennissessie**        |
| ------- | ----------------------- |
| ma      | AC / DC                 |
| di      | Opamp versterkertrappen |
| wo      | Hartslagmeter 1/2       |
| do      | Hartslagmeter 2/2       |

#### Week B4 (2-12-2024)

| **Dag** | **Kennissessie**                               |
| ------- | ---------------------------------------------- |
| ma      |                                                |
| di      | plc workshop (bij electro) 1/3                 |
| wo      | plc workshop (bij electro) 2/3                 |
| do      | {<b>Peil 3</b>} plc workshop (bij electro) 3/3 |

### Sprint 7

UI gebruiksvriendelijk maken. Performance verbeteren. Documentatie tip-top maken

#### Week B5 (9-12-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      |                  |
| di      |                  |
| wo      |                  |
| do      |                  |

#### Week B6 (16-12-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      |                  |
| di      |                  |
| wo      |                  |
| do      |                  |

#### Week B7 (23-12-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | Vakantie         |
| di      | Vakantie         |
| wo      | Vakantie         |
| do      | Vakantie         |

#### Week B8 (30-12-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | Vakantie         |
| di      | Vakantie         |
| wo      | Vakantie         |
| do      | Vakantie         |

### Oplevering

Werkend eindproduct presenteren en demonstreren. Documentatie opleveren.

#### Week B9 (6-1-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      |                  |
| di      |                  |
| wo      |                  |
| do      | {<b>Peil 4</b>}  |

### Evaluaties

Evaluaties<br>Op een aparte branch kan alvast gewerkt worden aan eventuele verbeteringen.

#### Week B10 (13-1-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      |                  |
| di      |                  |
| wo      |                  |
| do      |                  |

### Reparatie

Week B11 en B12 zijn er voor (mogelijke) verbeteringen van het ingeleverde werk of om binnen het semester verder de excelleren. Als niet alle leeruitkomsten Op Niveau of Boven Niveau zijn dan kan in samenspraak met de docent een (realistisch) plan worden gemaakt en voer je deze werkzaamheden in deze periode uit. Verder excelleren kan bijvoorbeeld door een leeruitkomst met verbeteringen van Op Niveau naar Boven Niveau te brengen.

#### Week B11 (20-1-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | Verbeterperiode  |
| di      | Verbeterperiode  |
| wo      | Verbeterperiode  |
| do      | Verbeterperiode  |

#### Week B12 (27-1-2024)

| **Dag** | **Kennissessie** |
| ------- | ---------------- |
| ma      | Verbeterperiode  |
| di      | Verbeterperiode  |
| wo      | Verbeterperiode  |
| do      | Verbeterperiode  |

#### Docenten-info:

Deze pagina is gegenereerd uit: [./Programma.drawio](./Programma.drawio) met het volgende script: [./DrawioProgrammaNaarMd.py](./DrawioProgrammaNaarMd.py)

De alternatieve view is uit diezelfde drawio gegenereerd via export naar HTML (uncheck lightbox en uncheck zoom to fit)
