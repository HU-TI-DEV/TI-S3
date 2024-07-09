![logo](https://www.hu.nl/-/media/hu/afbeeldingen/algemeen/hu-logo.ashx)

# Semester 3 van Technische Informatica

### Inhoud

- [Semester 3 van Technische Informatica](#semester-3-van-technische-informatica)
  - [Organisatie](#organisatie)
  - [Programma](#programma)
    - [Week A1 (2-9-2024)](#week-a1-2-9-2024)
    - [Week A2 (9-9-2024)](#week-a2-9-9-2024)
    - [Week A3 (16-9-2024)](#week-a3-16-9-2024)
    - [Week A4 (23-9-2024)](#week-a4-23-9-2024)
    - [Week A5 (30-9-2024)](#week-a5-30-9-2024)
    - [Week A6 (7-10-2024)](#week-a6-7-10-2024)
    - [Week A7 (14-10-2024)](#week-a7-14-10-2024)
    - [Week A8 (21-10-2024)](#week-a8-21-10-2024)
    - [Week A9 (28-10-2024)](#week-a9-28-10-2024)
    - [Week A10 (4-11-2024)](#week-a10-4-11-2024)
    - [Week B1 (11-11-2024)](#week-b1-11-11-2024)
    - [Week B2 (18-11-2024)](#week-b2-18-11-2024)
    - [Week B3 (25-11-2024)](#week-b3-25-11-2024)
    - [Week B4 (2-12-2024)](#week-b4-2-12-2024)
    - [Week B5 (9-12-2024)](#week-b5-9-12-2024)
    - [Week B6 (16-12-2024)](#week-b6-16-12-2024)
    - [Week B7 (23-12-2024)](#week-b7-23-12-2024)
    - [Week B8 (30-12-2024)](#week-b8-30-12-2024)
    - [Week B9 (6-1-2025)](#week-b9-6-1-2025)
    - [Week B10 (13-1-2025)](#week-b10-13-1-2025)
    - [Week B11 (20-1-2025)](#week-b11-20-1-2025)
    - [Week B12 (27-1-2025)](#week-b12-27-1-2025)
---

**v0.1.0** Semester 3 TI programma door HU IICT.

---

### Organisatie

Ons lokaal is HL15-1.096 

De contacturen zijn:
|dag|van|tot|
|---|---|---|
|ma|9:00|13:00|
|di|9:00|13:00|
|wo|13:00|17:00|
|do|13:00|17:00|

De docenten zijn:

- (**TM**) Teun Pieter Moddermann
- (**HS**) Harm Snippe
- (**HP**) Hagen Patzke
- (**MV**) Marius Versteegen
- (**BB**) Bart Bozon

De studentassistenten zijn:

- (**TB**) Tobias Bosch
- (**LH**) Loïs den Hartogh
- (**LK**) Liam Kortekaas
- (**TM**) Tim van Mourik

## Programma
[(alternatieve view html)](https://hu-ti-dev.github.io/TI-S3/programma/Programma_for_export_html.drawio.html)

### Opstarten

Teams gevormd, Projecten verdeeld, Project board opgezet, kennis gemaakt met de klant, Mindmap gemaakt. Start FR.

#### Week A1 (2-9-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | <a href="./programmas/programma-kickoff.md">Kickoff - Klantpraatjes - Teamvorming</a>&nbsp;(HS, TP, GP, HP) |
| di | <a href="./programmas/programma-systemcontext-keydrivers-applicationdrivers.md">Journalling - overige stakeholders - key drivers, prioriteren</a>&nbsp; (MV, HP, BB) |
| wo | {recap FR, NFR}&nbsp; (MV,HP, BB) |
| do | Uitje naar lasfabriek? |


### Sprint 1

Advies, in de vorm van Functionele Requirements, Non Functionele Requirements, UCD, UCBeschr, Activity Diagrammen en Functionele decompositie. + ESP32-IDF + mesh operationeel, evt. Hello Worlds van boundary objects.

#### Week A2 (9-9-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | {recap UCD, UC beschrijvingen}, Key Driver Graph&nbsp; (MV,HP,&nbsp;BB) |
| di | {recap AD}&nbsp; (MV,HP,&nbsp;BB) |
| wo | ESP32-IDF basic installatie&nbsp; (MV,HP,&nbsp;BB) |
| do | {ESP32-IDF mesh installatie + CleanRTOS}&nbsp; (MV,HP,&nbsp;BB) |
#### Week A3 (16-9-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Functionele decompositie&nbsp; (MV,HP,&nbsp;BB) |
| di | Networking basics&nbsp; (MV,&nbsp;BB, HP) |
| wo | Oefening Object Model&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| do | Concurrency (pc), mutex&nbsp; &nbsp; (MV,HP,&nbsp;BB) |


### Sprint 2

Object Model en klassediagram van het RTOS subsysteem<br>

#### Week A4 (23-9-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Oefening Object Model&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| di | Oefening Taakstructurering&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| wo | Oefening Klassediagram&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| do | Const expressions + Templates, SFINAE&nbsp; &nbsp; (MV,HP,&nbsp;BB) |
#### Week A5 (30-9-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Oefening Observer Pattern, Handler Pattern&nbsp; &nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| di | Synchronisatiemechanismen&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| wo | RAII&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
| do | {<b>Peil 1</b>} |


### Sprint 3

Object Model en klassediagram van het RTOS subsysteem afmaken, implementatie van (gegeven) STD NEC protocol, start implementatie van core functionaliteit van RTOS subsysteem.

#### Week A6 (7-10-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | {CleanRtos, FreeRtos, Logger / Debugging}&nbsp; &nbsp; (MV,HP,&nbsp;BB) |
| di | STD&nbsp; &nbsp; (MV,HP,&nbsp;BB) |
| wo | STD naar code&nbsp; &nbsp; (MV,HP,&nbsp;BB) |
| do | Oefening STD&nbsp; &nbsp;(MV,HP,&nbsp;BB) |
#### Week A7 (14-10-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Signalen in het frequentiedomein, fir filter, median filter&nbsp; (BB, MV) |
| di | pid workshop (ventilatorwip-todo-offshelve-balopplank met TOF) (BB, MV) |
| wo | Flask, MongoDb, NoIP, Reverse Proxy, docker composer (MV, HP) |
| do |  |


### Sprint 4

RTOS subsysteem klaar, Linux (Lightsail) server met Flask en MongoDb draaiend. Een architectuur gemaakt voor het server-deel.<br>(requirements, usecases,&nbsp; storage model, distributie van functionaliteit over python/flask, html/css en javascript.)

#### Week A8 (21-10-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | {HTML, CSS} (pointer naar zelfstudie)&nbsp; (MV, HP) |
| di | {Javascript} (pointer naar zelfstudie)&nbsp; &nbsp; (MV, HP) |
| wo | Webarchitectuur&nbsp; &nbsp; (MV, HP, BB) |
| do |  |
#### Week A9 (28-10-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | vakantie |
| di | vakantie |
| wo | vakantie |
| do | vakantie |
#### Week A10 (4-11-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Combinatoriek&nbsp; &nbsp; (MV, BB, HP) |
| di | Karnaugh&nbsp; &nbsp; &nbsp; (MV, BB, HP) |
| wo | Karnaugh&nbsp; &nbsp; &nbsp; (MV, BB, HP) |
| do | {<b>Peil 2</b>} |


### Sprint 5

Webdeel verder klaar en geintegreerd met RTOS subsysteem.

#### Week B1 (11-11-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Quick and Dirty&nbsp; &nbsp; &nbsp;(MV, BB, HP) |
| di | Compact and Clean&nbsp; &nbsp;(MV, BB, HP) |
| wo | Digitale simulatie (logisim)&nbsp; &nbsp;(MV, BB, HP) |
| do |  |
#### Week B2 (18-11-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Bouwen en debuggen van digitale electronica (evt (ook) in plc)&nbsp; (MV, BB, HP) |
| di |  |
| wo | Recap Rekenen&nbsp; &nbsp;(BB, MV, HP) |
| do | Recap Electro&nbsp; &nbsp;(BB, MV, HP) |


### Sprint 6

Werkend prototype

#### Week B3 (25-11-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | AC / DC&nbsp; &nbsp;(MV, BB, HP) |
| di | Opamp versterkertrappen&nbsp; &nbsp; (MV, BB, HP) |
| wo | Hartslagmeter 1/2&nbsp; &nbsp; (MV, BB, HP) |
| do | Hartslagmeter 2/2&nbsp; &nbsp; (MV, BB, HP) |
#### Week B4 (2-12-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma |  |
| di | plc workshop (bij electro) 1/4&nbsp; (MV, HP) |
| wo | plc workshop (bij electro) 2/4&nbsp; &nbsp;(MV, HP) |
| do | {<b>Peil 3</b>} plc workshop (bij electro) 3/4&nbsp; &nbsp;(MV, HP) |


### Sprint 7

UI gebruiksvriendelijk maken. Performance verbeteren. Documentatie tip-top maken

#### Week B5 (9-12-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | plc workshop (bij electro) 4/4&nbsp; &nbsp; (MV, HP) |
| di |  |
| wo |  |
| do |  |
#### Week B6 (16-12-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma |  |
| di |  |
| wo |  |
| do |  |
#### Week B7 (23-12-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Vakantie |
| di | Vakantie |
| wo | Vakantie |
| do | Vakantie |
#### Week B8 (30-12-2024)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Vakantie |
| di | Vakantie |
| wo | Vakantie |
| do | Vakantie |


### Oplevering

Werkend eindproduct presenteren en demonstreren. Documentatie opleveren.

#### Week B9 (6-1-2025)

| **Dag** | **Kennissessie** |
|---|---|
| ma |  |
| di |  |
| wo |  |
| do | {<b>Peil 4</b>} |


### Evaluaties

Evaluaties<br>Op een aparte branch kan alvast gewerkt worden aan eventuele verbeteringen.

#### Week B10 (13-1-2025)

| **Dag** | **Kennissessie** |
|---|---|
| ma |  |
| di |  |
| wo |  |
| do |  |


### Reparatie

Week B11 en B12 zijn er voor (mogelijke) verbeteringen van het ingeleverde werk of om binnen het semester verder de excelleren. Als niet alle leeruitkomsten Op Niveau of Boven Niveau zijn dan kan in samenspraak met de docent een (realistisch) plan worden gemaakt en voer je deze werkzaamheden in deze periode uit. Verder excelleren kan bijvoorbeeld door een leeruitkomst met verbeteringen van Op Niveau naar Boven Niveau te brengen.

#### Week B11 (20-1-2025)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Verbeterperiode |
| di | Verbeterperiode |
| wo | Verbeterperiode |
| do | Verbeterperiode |
#### Week B12 (27-1-2025)

| **Dag** | **Kennissessie** |
|---|---|
| ma | Verbeterperiode |
| di | Verbeterperiode |
| wo | Verbeterperiode |
| do | Verbeterperiode |


#### Docenten-info:

Deze pagina is gegenereerd uit: [./Programma.drawio](./Programma.drawio) met het volgende script: [./DrawioProgrammaNaarMd.py](./DrawioProgrammaNaarMd.py)

De alternatieve view is uit diezelfde drawio gegenereerd via export naar HTML (uncheck lightbox en uncheck zoom to fit)
