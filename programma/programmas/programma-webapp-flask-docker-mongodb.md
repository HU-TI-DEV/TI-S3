# Programma WebApp Flask Docker MongoDB
Tijdens dit semester gaan jullie als onderdeel van het project een **webapplicatie** ontwikkelen op basis van **Flask, Vanilla Javascript, HTML, CSS en MongoDB**.  

De webapplicatie wordt gehost op een set docker containers, welke met een enkel **docker-compose** commando opgezet kunnen worden. In combinatie met het gebruik van github zorgt dat ervoor dat de webapplicatie eenvoudig naar believen op verschillende servers kan worden opgezet.

Ook de **ESP32s** van jullie project zullen communiceren met het bijbehorende backend.

## Voorbeeld WebApp
Bij het opzetten van zo'n webapplicatie komt veel kijken. 

Om jullie op weg te helpen hebben we een **voorbeeld van zo'n webapplicatie** voor jullie gemaakt (een 5 op een rij spel).

## Voorbereiding
Scan alvast wat door:  
- [log_Opzetten_van_Server_en_Webapplicatie.md](../../infrastructuur/ServerMetWebApplicatie/log_Opzetten_van_Server_en_Webapplicatie.md)
- [VoorbeeldWebApp_Gomoku/README.md](https://github.com/HU-TI-DEV/VoorbeeldWebApp_Gomoku/blob/main/README.md)
- [VoorbeeldWebApp_Gomoku/Gomoku_WebApp_Design.md](https://github.com/HU-TI-DEV/VoorbeeldWebApp_Gomoku/blob/main/docs/gomoku_webapp/Gomoku_WebApp_Design.md)

en/of kijk [deze inleidende video - TODO](TODO)

## Tijdens een na de les
Tijdens en na de les zet ieder zijn individuele ontwikkelserver met webapplicatie op. Dat komt neer op de volgende Canvas opdracht.  

### Canvas Opdracht "Ontwikkelserver met Webapplicatie"
Gebruik voor deze opdracht het materiaal uit de voorbereiding.  

Net als bij het opzetten van de ESP32 ontwikkelomgeving, is het belangrijk dat je **aantekeningen** maakt in je persoonlijk logboek.

Lever bij de **Canvas opdracht** "Ontwikkelserver met Webapplicatie" links (en commit-links) in van:
- De **hash** naar het kopje in je **persoonlijk logboek** waar je aantekeningen hebt gemaakt over het opzetten van de server en webapplicatie.
- Een **document** genaamd **OnwikkelserverMetWebAppOpdracht.md** met daarin het volgende:
  - Een mid-game **screenshot** van de werkende webapplicatie.
  - Maak een **screenshot** van de inhoud van een geregistreerde, gespeelde game in een database entry van MongoDB atlas.
  - **Licht toe** wat er is opgeslagen.
  - Kijk Flask code in app.py door, en geef een **korte beschrijving** van je indruk over **hoe Flask in zijn algemeen ongeveer werkt**.
  - Bestudeer de docker-compose.yml en de Dockerfile files. Leg in detail uit **wat de regels uit deze files doen** en hoe ze samenwerken.
  - Geef een **samenvatting** van hoe een (officieus) **Page Design Model** de opbouw en het gedrag van een webpagina beschrijft.

Haal na het uploaden feedback op, en upload die feedback ook in de opdracht. (uploaden van verwerkingsresultaat is in dit geval niet nodig).

### Ruim plannen
Evenals het opzetten van de ESP32 omgeving kan het opzetten van de webapplicatie omgeving meer tijd kosten dan je denkt. **Plan daarom ruim in**, en begin op tijd. Dan moet het mogelijk zijn om het voor de deadline klaar te hebben.