# Networking voorbeeld

Tijdens dit semester ga je met je team een networking oplossing maken.

Om een snel overzicht te krijgen van wat daarbij komt kijken, bestuderen we een praktisch voorbeeld.

[Dit plaatje](./img/Networking_Personal_Example.drawio.svg) geeft zo'n voorbeeld. Dit voorbeeld laat zien hoe het surfen werkt naar mijn persoonlijk gehoste website www.pikido.com.

Het is een vrij groot plaatje. Scroll eerst eens naar links, dan bespreken we dat eerst.

## Client-Server
Op het web zijn er i.h.a. clients die data opvragen en servers die die data leveren. We gaan er in dit geval vanuit dat de client een PC is met browser en de server een machine is die een website host.

## Ip nummers
Je kunt het een beetje vergelijken met opbellen: de client belt de server op en vraagt om informatie. Als 'telefoonnummer' wordt een ip-nummer gebruikt.

## URL in de browser
In dit voorbeeld veronderstellen we een client PC met browser, ergens in Hamburg, Duitsland. In de browser wordt de url ingetypt: https://www.pikido.com/teambuilder

Dat bevat de volgende 3 delen informatie:
- De domeinnaam: www.pikido.com
- Een subpagina: /teambuilder
- Een port: 443 (https betekent default port 443, http betekent default port 80)

## DNS
Om het bij de domeinnaam behorende ip-nummer te achterhalen, maakt je browser eerst contact met een bekend ip-nummer van een DNS, een Domain Name Server. Dat is een soort van telefoonboek die voor elke domeinnaam bijhoudt wat het bijbehorende ip nummer is.
Die DNS stuurt het ip nummer naar je browser, zodat je browser dat kan "bellen".

## Domain Registrar
Hoe komt dat ip nummer in dat telefoonboek? De DNS krijgt daarvoor informatie van een zogenaamde Domain Name Registrar. Je kunt daar een domeinnaam huren. Typisch kun je je domein naam koppelen aan een vast ip-adres (dat kost steeds meer geld) of koppelen aan een kleine webserver welke het dynamische ip-adres van je server retourneert.
In dit geval is dat een server van NOIP.com. De pikido-server draait periodiek een DUC (Dynamic Update Client) script, die stuurt het dynamische ip-adres van de router voor de pikido-server naar NOIP.com, zodat die het kan doorgeven aan de DNS server zodra deze er om vraagt.

## Internet = web van verbonden netwerken
Het internet bestaat uit (lokale-)netwerken welke verbonden zijn. Op de grenzen van die netwerken bevinden zich routers (of switches). De client PC, de servers van domain name registrar, NOIP.com en pikido.com zitten allemaal op hun eigen lokale netwerk welke via een router verbonden is met een internet provider. Om het een beetje overzichtelijk te houden is in het plaatje alleen de router van de pikido server afgebeeld.

## Bericht reist naar de router waar de server achter zit
Enfin, even terug naar onze client, die heeft van de DNS het ip-adres van pikido.com gekregen, en "belt" daarmee in bij zijn ISP (Internet Service Provider). 

Bijvoorbeeld UPC, Ziggo, AOL of een andere grote jongen. Via de netwerken van die internet-service-providers komt het bericht uiteindelijk terecht bij de service-provider van de router van het lokale netwerk waar achter zich de pikido server bevindt.

## ip-adres = adres van de router
Het ip-adres dat gereist heeft, is het ip-adres van de router van dat lokale netwerk. Binnen dat lokale netwerk heeft de server, laten we zeggen een Raspberry PI4 een eigen lokaal ip-adres, maar daar weet de Client PC in Duitsland niets van.

## Lokaal ip adres 
Het is handig om dat lokale ip-adres statisch in te stellen, zodat je het tijdens het testen makkelijk kunt vinden (door dat ip-adres in de browser in te typen vanaf je thuis pc).

## Wat doet de router met het binnenkomende bericht
In de router staat ingesteld dat als verkeer binnenkomt op een zekere port, naar welk lokaal ip adres het dan moet worden geforward.
In dit geval wordt port 443 (https verkeer) geforward naar de Raspberry PI4 waar mijn server op draait.
Daar komt het bericht (verzoek tot het weergeven van de content van https://www.pikido.com/teambuilder) dus terecht.

## De server - Ubuntu
De server zelf draait een Ubuntu 22.04LTS instance. Dat is handig, want die draait op Raspberry PI4, Amazon Lightsail en Windows WSL. Als je je content in git hebt staan, kun je die dus heel makkelijk op een andere server installeren als het nodig is. 
Amazon Lightsail is handig, maar kost maandelijks geld. Raspberry PI4 is goedkoop en verbruikt weinig stroom, maar gaat uit als de stroom uitvalt. Windows WSL is handig en snel als het gaat om developing (maar te duur in stroomverbruik om echt als server aan te laten staan).

## Docker - compose
Binnen de server wordt een verzameling docker containers gestart (dat zijn die cylinders). Dat zijn containers met web-gebaseerde applicaties. Die kunnen met elkaar praten en kunnen web-requests afhandelen.
Via een enkel docker-compose commando kunnen ze allemaal in een keer opgestart of gestopt worden.

## Reverse Proxy
De "poortwachter" van de docker containers is een container waarop een zogenaamde "reverse proxy" draait. Die stuurt binnenkomend verkeer door naar de docker container waar het voor bedoeld is. In dit geval stuurt de reverse proxy berichten met een url die begint met www.pikido.com/teambuilder door naar een container waar de flask applicatie draait met teambuilder software. Berichten afkomstig van www.rsibehandeling.eu stuurde het door naar een docker container met een nginx server (Website2). (sidenote: die domeinnaam heb ik laten verlopen. ik gebruik nu alleen rsihulpmiddelen.nl). Optioneel zou je de reverse proxy ook kunnen laten doorlinken naar docker containers op andere servers. Bijvoorbeeld zware jobs kun je beter uitvoeren op aparte servers zodat de responsitiviteit van je webpaginas er niet onder lijdt.
Zo kun je een heel serverpark in je huiskamer achter je reverse proxy hangen. In mijn buurt wordt binnenkort glasvezel van Open Dutch Fiber aangelegd. Je kunt dan een Odido abonnement nemen met maar liefst 8Gbs up en down. Bandbreedte is dan niet zo gauw een beperkende factor meer.

## Andere handige containers
Handige containers die we al genoemd hebben zijn de flask (python-backend) server en de nginx (html-frontend) server. Een database is ook vrijwel altijd van de partij. Zelf gebruik ik daarvoor ene container met MongoDB server. Als laatste is er nog een certbot applicatie. Die zorgt voor automatische certificaatuitgiftes, zodat je niet elk jaar voor elke domein naam een certificaat(-verlenging) hoeft te kopen.

## www
Waarom starten al mijn domeinnamen met www, vraag je je vast af? De reden is dat de eerder genoemde truc waarmee je kunt voorkomen een statisch ip adres aan te schaffen, anders niet lijkt te kunnen werken.