# Te verwerken tekst - Design like a Robot!
Hieronder staat nog onverwerkte tekst uit het  [pdf document Design like a Robot!](../Design%20Like%20a%20Robot!.pdf). Dit document zal langzaam opgesplitst worden in meerdere .md -files. Je kunt dit volgen in de [README.md file](README.md).

# ----

Object model met object beschrijvingen voor het Trilapparaat
We lopen voor het trilapparaat gewoon de bovengenoemde stappen voor het opstellen van een
object model door.
Stap 1: Maak een controller object aan voor elke use case.
Nog even kijken naar het use case diagram:
Toevoegen aan het object model
Aha, we hadden twee use cases: “Instellen” en “Trilbesturing”. Voor elke use case moesten we een
controller object aanmaken. Mooie compacte namen voor de bijbehorende controller objecten lijken
me “InstelControl” en “TrilControl”. Er mogen geen spaties of speciale karakters in de namen zitten.
Die voegen we toe aan het object model:
Eventueel stereotype aangeven
Voor objecten uit een van de categorien <<control>>, <<boundary>> en <<entity>> moeten we nog
een stereotype weergeven boven de naam.
Bij onze controller objecten moeten we dus het stereotype <<control>> boven de naam noteren:
Beschrijving toevoegen aan de lijst met objecten
Elk van de gevonden objecten voegen we toe aan de lijst met objecten, en we voegen een
beschrijving toe. In dit stadium weten we alleen dat deze twee objecten de bijbehorende use case
voor hun rekening moeten nemen. Voor nu vullen we dat dus in:
Object Naam Stereotype Beschrijving
InstelControl Control “Dirigent” van use case “Instellen” (zie use case beschrijving)
TrilControl Control “Dirigent” van use case “Trillen” (zie use case beschrijving)
Stap 2: Verwerk de use case beschrijvingen zin voor zin
We beginnen met de use case “Instellen”.
Lees een zin
We lezen de eerste zin van de use case:
“De ingestelde trilfrequentie wordt op de display weergegeven.”
Bedenk welke “dingen” je systeem nodig heeft om te kunnen doen wat er staat.
In deze zin bedenk ik dat de volgende dingen van belang zijn:
 een “ingestelde trilfrequentie”
 een display
In dit geval is dat extra makkelijk, omdat deze “dingen” al voorkomen in de zin als zelfstandige
naamwoorden. Dat is typisch het geval als de usecase is geformuleerd vanuit het perspectief van het
apparaat.
Stel nu dat de usecase zou zijn gespecificeerd vanuit het perspectief van de persoon. Dan had er
bijvoorbeeld kunnen staan: “de operator verifieert de ingestelde trilfrequentie visueel”. In zo’n vager
geformuleerd geval zul je zelf moeten bedenken met welke “dingen” je dat mogelijk kunt maken. Je
kunt dan kiezen voor een display, maar bijvoorbeeld ook voor een analoge wijzer die uitslaat.
Misschien bedenk je in het geval van een display dat je het alleen wilt als er een knop wordt
ingedrukt. In dat geval heb je er ook een knop voor nodig.
Maak voor elk van de “dingen” een object aan
 Een data‐gegeven als trilfrequentie kunnen we modelleren als entity object. Ik noem het
“Trilfrequentie”.
 Voor de display maken we een boundary object aan. Ik noem het “Display”. Het is een
software object dat hardware (in dit geval een display) aanstuurt.
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl Control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl Control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie Entity Bevat de ingestelde trilfrequentie.
Display Boundary Stuurt de display hardware aan.
Databeheer
Publieke data
NB: we hebben het hier over “publieke data” die wordt uitgewisseld tussen objecten. Als het slechts
binnen een object gebruikt wordt, kan het verborgen kunnen blijven, en zien we het niet in het
objectmodel terug.
Waar “zit” die publieke data nu?
In het algemeen probeer je voor elke publieke data in je systeem te laten beheren door een enkele
“(hoofd‐) eigenaar”. Als je de data wilt opvragen, kun je die eigenaar raadplegen. Wil je de data
veranderen, dan kun je dat bij die eigenaar aanvragen. Je kunt ervoor kiezen om een entity object
(hoofd‐) eigenaar te maken, of een ander object.
Wat is netjes? Data beheer door entity object of ander object?
Het is in het algemeen netjes dat data wordt beheerd in het object waar het het meest mee
verbonden is / wordt “gebruikt”. In dat geval hoef je er geen apart entity object voor te maken, en
encapsuleer je de data in het betreffende object.
De trilfrequentie wordt weliswaar ingesteld in InstelControl, maar wordt echt gebruikt in TrilControl,
je zou het dus prima kunnen encapsuleren in TrilControl.
Maar wanneer gebruik je dan een entity object?
Dat kun je gebruiken in de volgende gevallen:
 Datapakket
 Geen logische eigenaar
Datapakket
Het had ook kunnen zijn dat trilfrequentie data is die in samenhang met andere data als een geheel
kan worden gezien, behandeld, weggeschreven of verzonden, als datapakket. In dat geval is het
netter om die bij mekaar horende data te bundelen in een apart “entity object”.
Bijvoorbeeld als de data zich bevindt in traag geheugen, en/of om bij mekaar horende data logisch te
groeperen en/of als de data om de een of andere reden geencapsuleerd moet worden. Bijvoorbeeld
bij een database of bij data die via encryptie wordt opgeslagen en opgevraagd.
Bij ons trilapparaat is er alleen een Trilfrequentie die ingesteld moet worden. In een wat
ingewikkelder, realistischer voorbeeld wil je misschien meerdere data instellen, die tesamen een
entiteit “programma” vormen. Dat bevat dan bijvoorbeeld Trilfrequentie, Trilintensiteit en Loopduur.
Je kunt zo’n entiteit dan bijvoorbeeld in zijn geheel aanpassen met InstelControl en eventueel lezen
of schrijven naar disk met een DiskControl.
Stel nu dat je in zo’n geval DiskControl weglaat, en de entiteit “programma” als geheel alleen wordt
gebruikt door InstelControl. Het gaat dan alleen nog om een conceptuele groepering van data. In dat
geval zou je er ook voor kunnen kiezen om die data toch te encapsuleren in InstelControl (in plaats
van in een apart entity object. Dat is een kwestie van smaak.
Geen logische eigenaar
In het geval van de Trilfrequentie is het wel duidelijk dat die het meest verbonden is met TrilControl.
Het kan ook voorkomen dat je data tegenkomt die door meerdere objecten wordt gebruikt, maar
waarvan het niet duidelijk het meest bij een enkel object hoort.
Ook in zo’n geval is het netter om een apart entity object eigenaar voor die data te laten zijn.
Databeheer
Voor het Trilapparaat kies ik voor een apart entity object, puur om ook een entity object in het
design te laten voorkomen. Als extra argument zou ik kunnen gebruiken dat ik voorzie dat het aantal
instellingen in de toekomst wellicht zal worden uitgebreid, en dat het dan conceptueel overzichtelijk
is als de instellingen in een aparte entity gebundeld zijn.
Maar zoals je misschien al uit het bovenstaande verhaal hebt opgemerkt, was het bij dit minimale
Trilapparaat eigenlijk niet nodig.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Instellen” was:
“De ingestelde trilfrequentie wordt op de display weergegeven.”
Die zin wordt uitgevoerd (zoals de meeste zinnen in de use case instellen ) door het object
InstelControl. Dus: InstelControl zegt “geef trilfrequentie weer” tegen het Display object.
Maar goed, een Display is een display, en weet niets van trilfrequenties. We passen dit bevel dus een
beetje aan, naar: “showMessage(trilfrequentie)”. Dus zonder spaties, en met bericht en “payload”
netjes gescheiden.
Even verder denken: InstelControl geeft dus de trilfrequentie door aan de Display, maar hoe komt
InstelControl daar aan? We hadden besloten om de trilfrequentie in een TrilFrequentie entity op te
slaan, dus InstelControl zal de trilfrequentie daar op moeten vragen. InstelControl zegt dus tegen
TrilFrequentie “geefTrilFrequentie”, of gebruikelijker, met het engelse get: “getTrilFrequentie”.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Onderstaand is dat gedaan voor de berichten showMessage(trilfrequentie) en getTrilFrequentie.
Met dezelfde stappen kunnen we de andere zinnen van deze use case verwerken.
Op naar de volgende zin dus!
Lees een zin
We lezen de tweede zin van de use case Instellen:
“Met de plus en min knop kan dat getal aangepast worden.”
Identificeer de “dingen”
In deze zin zie ik de volgende dingen (zelfstandig naamwoorden):
 Een plus knop
 Een min knop
Maak voor elk van de “dingen” een object aan
 Voor elk van beide knoppen maken we een boundary object aan. Het zijn software objecten
die hardware (in dit geval een pin van de chip waar een button aanvast zit) uitlezen.
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie entity Bevat de ingestelde trilfrequentie.
Display boundary Stuurt de display hardware aan.
PlusKnop boundary Een knop die terugveert.
MinKnop boundary Een knop die terugveert.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Instellen” was:
“Met de plus en min knop kan dat getal aangepast worden.”
We hebben het over de use case Instellen, dus het object dat dat doet moet InstelControl zijn.
 De plus en min knoppen moeten dus melden aan InstelControl dat ze ingedrukt zijn.
 Vervolgens kan InstelControl de frequentie uitlezen uit TrilFrequentie, aanpassen, en er weer
naar terugschrijven.
Kortom:
 PlusKnop zegt “meldKnopIngedrukt(plusKnopID)” tegen InstelControl. plusKnopID is daarbij
een int of enum die aangeeft om welke knop het gaat. Gebruikelijker is de engelse variant:
“buttonpressed(plusKnopID)”. Voor de MinKnop geldt iets soortgelijks.
 InstelControl zegt “getTrilfrequentie” en “setTrilfrequentie(nieuweFrequentie)” tegen de
TrilFrequentie entity.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, volgende zin!
Lees een zin
We lezen de volgende zin van de use case Instellen:
“Het getal moet tussen de 1 en de 100 (Hz) blijven.”
Identificeer de “dingen”
Dat “getal” is de trilfrequentie. Die hebben we al. Verder geen (nieuwe‐) “dingen” hier. We lezen we
de beschrijving van use case instellen, dus dit is iets waar InstelControl voor moet gaan zorgen in zijn
Std.
Volgende zin!
Lees een zin
We lezen de volgende zin van de use case Instellen:
“Als na de laatste trilfrequentie‐aanpassing een minuut lang geen nieuwe trilfrequentie‐aanpassing
volgde, wordt die laatste nieuwe trilfrequentie gelogd naar een remote database.”
Identificeer de “dingen”
In deze zin zie ik de volgende nieuwe dingen (zelfstandig naamwoorden):
 Een minuut
 Een remote database
Maak voor elk van de “dingen” een object aan
 Er moet een tijd worden gemeten (een minuut), in een soort van “time out” situatie. In de
theorie hebben we gezien dat we voor waitables zoals timers geen object in het object
model hoeven aan te maken.
 Voor de remote database maken we een boundary object aan. We zouden het nauwkeuriger
kunnen specificeren als “proxy” object (maar laten dat hier achterwege).
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie entity Bevat de ingestelde trilfrequentie.
Display boundary Stuurt de display hardware aan.
PlusKnop boundary Een knop die terugveert.
MinKnop boundary Een knop die terugveert.
RemoteDatabase boundary Een object via welke data uitgewisseld kan worden met een
database elders.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Instellen” was:
“Als na de laatste trilfrequentie‐aanpassing een minuut lang geen nieuwe trilfrequentie‐aanpassing
volgde, wordt die laatste nieuwe trilfrequentie gelogd naar een remote database.”
We hebben het over de use case Instellen, dus InstellenControl moet (een bepaalde tijd na voor het
laatst indrukken van een knop) de nieuwe trilfrequentie loggen naar de remote database.
 InstelControl zegt tegen de RemoteDatabase kan zeggen “log deze trilfrequentie”. Mooi
opgesplitst in bericht en payload zou dat worden: log(trilfrequentie).
Kortom:
 InstelControl zegt log(trilfrequentie) tegen RemoteDatabase.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, volgende zin!
Lees een zin
We lezen de volgende zin van de use case Instellen:
“Dat laatste kan enige seconden duren.”
Identificeer de “dingen”
In deze zin zie ik de volgende dingen (zelfstandig naamwoorden): seconden. Maar dit zijn geen
seconden die we zelf willen maken. We hoeven voor waitables zoals timers ueberhaupt geen
objecten aan te maken.
Volgende zin!
Lees een zin
We lezen de volgende zin van de use case Instellen:
“Zodra de noodknop is ingeslagen kan de frequentie niet meer worden aangepast, en toont het
display “Emergency Stop”.”
Identificeer de “dingen”
In deze zin zie ik de volgende nieuwe dingen (zelfstandig naamwoorden):
 Een noodknop
Maak voor elk van de “dingen” een object aan
 Voor de noodknop maken we een boundary object aan.
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl Control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl Control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie Entity Bevat de ingestelde trilfrequentie.
Display boundary Stuurt de display hardware aan.
PlusKnop boundary Een knop die terugveert.
MinKnop boundary Een knop die terugveert.
NoodKnop boundary Een knop die kan worden ingeslagen en weer uitgetrokken.
RemoteDatabase boundary Een object via welke data uitgewisseld kan worden met een
database elders.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Instellen” was:
“Zodra de noodknop is ingeslagen kan de frequentie niet meer worden aangepast, en toont het
display “Emergency Stop”.”
We hebben het over de use case Instellen, dus InstellenControl moet het object zijn dat luistert naar
het de noodknop en moet zorgen dat er iets op het display verschijnt.
Kortom:
 Noodknop zegt buttonpressed(noodKnopId) tegen InstelControl.
 InstelControl zegt showmessage(“Emergency Stop”) tegen Display.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, volgende zin!
Lees een zin
We lezen de volgende zin van de use case Instellen:
“Zodra de noodknop weer is omhooggetrokken kan de bovenstaande use case weer hervat worden.”
Identificeer de “dingen”
In deze zin staan geen nieuwe “dingen”. Wel staat er iets over een al toegevoegd ding, de Noodknop.
We gaan daarom door naar de volgende stap:
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
We hebben het over de use case Instellen, dus InstelControl moet het object zijn dat luistert naar het
de noodknop en moet zorgen dat het frequentie‐instellen wordt hervat zodra de noodknop weer is
omhooggetrokken. De Noodknop moet dus tegen InstelControl zeggen dat hij “weer omhoog
getrokken is”. We kunnen daar een mooi algemeen engels bericht met payload voor maken:
buttonReleased(buttonId).
Kortom:
 Noodknop zegt buttonReleased(noodKnopId) tegen InstelControl.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, we we hebben nu alle zinnen van de beschrijving van de use case “Instellen”.
Stoiceins gaan we verder met de volgende use case: “Trillen”.
Lees een zin
We lezen de eerste zin van de use case Trillen:
“Als deze use case start, trilt het apparaat niet.”
Identificeer de “dingen”
In deze zin zie ik de volgende nieuwe dingen (zelfstandig naamwoorden):
 Het apparaat. “Het apparaat” is kennelijk iets dat al dan niet kan trillen. In de casus hebben
we gezien dat dat gebeurt door een electromagneet aan of uit te schakelen. Het ligt dus voor
de hand om een object aan te maken dat de electromagneet aan of uit kan schakelen.
Maak voor elk van de “dingen” een object aan
 We maken een boundary object Electromagneet aan. Dat is een software object dat kan
zorgen dat er stroom wordt gezet – of niet – op een hardwarematige electromagneet.
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl Control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl Control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie Entity Bevat de ingestelde trilfrequentie.
Display Boundary Stuurt de display hardware aan.
PlusKnop Boundary Een knop die terugveert.
MinKnop Boundary Een knop die terugveert.
NoodKnop Boundary Een knop die kan worden ingeslagen en weer uitgetrokken.
Electromagneet Boundary Een electromagneet die kan worden aan en uitgezet.
RemoteDatabase Boundary Een object via welke data uitgewisseld kan worden met een
database elders.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Trillen” was:
“Als deze use case start, trilt het apparaat niet.“
We hebben het over de use case Trillen, dus TrilControl moet het object zijn dat zorgt dat de
electromagneet na opstarten uit staat.
Kortom:
 TrilControl zegt zetUit tegen Electromagneet.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Volgende zin!
Lees een zin
We lezen de volgende zin van de use case Trillen:
“Met het indrukken van de tril knop wordt het trillen in de actueel ingestelde trilfrequentie
getoggeld.”
Identificeer de “dingen”
In deze zin zie ik de volgende nieuwe dingen:
 Een trilknop
 Er moet ook iets gebeuren in een bepaalde frequentie, ofwel met bepaalde
tussentijdsintervallen. Die tijdsintervallen zou je kunnen maken met een timer.
Net als andere waitables hoeven we daar geen object voor aan te maken in het object model.
Maak voor elk van de “dingen” een object aan
 Voor de trilknop maken we een boundary object TrilKnop aan.
Zoals altijd voegen we de nieuwe objecten toe in 3 stappen:
Toevoegen aan het object model + stereotype erbij
Beschrijving toevoegen aan de lijst met objecten
Object Naam Stereotype Beschrijving
InstelControl Control “Dirigent” van use case “Instellen” (zie use case beschrijving).
TrilControl Control “Dirigent” van use case “Trillen” (zie use case beschrijving).
Trilfequentie Entity Bevat de ingestelde trilfrequentie.
Display Boundary Stuurt de display hardware aan.
PlusKnop Boundary Een knop die terugveert.
MinKnop Boundary Een knop die terugveert.
NoodKnop boundary Een knop die kan worden ingeslagen en weer uitgetrokken.
TrilKnop Boundary Een knop die terugveert.
RemoteDatabase Boundary Een object via welke data uitgewisseld kan worden met een
database elders.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
De zin uit de use case “Trillen” was:
“Met het indrukken van de tril knop wordt het trillen in de actueel ingestelde trilfrequentie
getoggeld.”
 We hebben het over de use case Trillen, dus TrilControl moet het object zijn dat luistert naar
het de TrilKnop en moet zorgen dat het trillen aan of uit wordt gezet. Maar wat is trillen? Dat
is het aan en weer uitzetten van de electromagneet. In het huidige object model kan
TrilControl al ZetUit zeggen tegen de electromagneet. Om te kunnen laten trillen moet hij
dus ook “zet aan” kunnen zeggen.
 Verder moet het trillen gebeuren met de actueel ingestelde frequentie. Het zou dus handig
zijn als TrilControl tegen de Trilfrequentie entity “getTrilFrequentie” zou kunnen zeggen.
Kortom:
 TrilKnop zegt buttonPressed(trilKnopID) tegen TrilControl
 TrilControl zegt zetAan tegen Electromagneet.
 TrilControl zegt getTrilfrequentie tegen Trilfrequentie.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, volgende zin!
Lees een zin
We lezen de volgende zin van de use case Trillen:
“Zodra de noodknop is ingeslagen stopt het trillen, en wordt de tril knop genegeerd.”
Identificeer de “dingen”
Alle dingen in die zin: noodknop, tril knop, trillen (van de electromagneet en TrilControl) staan al in
het object model. We hoeven dus geen object toe te voegen.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
 We hebben het over de use case Trillen, dus TrilControl moet het object zijn dat in deze zin
luistert naar het de NoodKnop en moet zorgen dat alles tot stilstand komt.
NoodKnop moet TrilControl dus laten weten dat hij is ingedrukt.
Kortom:
 NoodKnop zegt buttonPressed(noodKnopID) tegen TrilControl.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Mooi, volgende zin!
Lees een zin
We lezen de volgende zin van de use case Trillen:
“Zodra de noodknop weer is omhooggetrokken kan deze use case weer hervat worden.”
Identificeer de “dingen”
Alle dingen in die zin staan al in het object model. We hoeven dus geen object toe te voegen.
Ga na welk “ding” iets tegen welk “ander ding” “zegt”
 We hebben het over de use case Trillen, dus TrilControl moet het object zijn dat in deze zin
luistert naar het de NoodKnop en moet zorgen dat de TrilControl zijn normale werk weer kan
gaan doen.
NoodKnop moet TrilControl dus laten weten dat hij is uitgetrokken.
Kortom:
 NoodKnop zegt buttonReleased(noodKnopID) tegen TrilControl.
Zet wat er “wordt gezegd” als bericht langs een pijl vanuit het sprekende object naar het
luisterende object.
Dat was de laatste zin van de laatste use case.
Taakstructurering
Zodra de lijst van objecten en hun beschrijvingen compleet is, moet aan elk van de objecten een van
de volgende “taaksoorten” worden toegekend:
1. IO (input output) : dat zijn taken van boundary objecten.
Daarbij moet ook het subtype worden aangegeven:
a. Periodical
‐> wanneer iets met vast interval moet worden gedaan, zoals pollen.
b. Event driven
‐> wanneer er iets wordt gedaan na optreden van een hardware interrupt (komt
verder niet voor in deze cursus)
c. Demand driven
‐> overig: gaat pas iets doen als er een bericht binnenkomt.
1. Intern : dat zijn taken van overige objecten.
a. Periodical
‐> wanneer iets met vast interval moet worden gedaan, zoals pollen.
b. Demand driven
‐> overig: gaat pas iets doen als er een bericht binnenkomt.
1. Geen taak
Soms kun je direct al besluiten dat een object geen eigen taak nodig heeft, bijvoorbeeld als
hetgeen wat hij doet vrijwel instantaan is. Voorbeelden: entitiy objecten, leds.
Taakstructurerings‐tabel
De objecten en hun klassificering zet je op een rijtje in een tabel:
Objecten Taaksoort Periode Deadline Prioriteit
Behalve de objectnaam en de taaksoort vul je per object ook een deadline en eventueel een periode
in.
Periode
Objecten met als taaksoort “Periodical IO of Periodical intern” komen met de regelmaat van een klok
in actie om iets te doen.
Deadline
Een deadline is de tijd die het object er over mag doen om “zijn ding te doen” nadat hij de beurt
heeft gekregen.
NB:
 Als iets niet heel tijd‐kritisch is (bijvoorbeeld het doorgeven van de hoeveelheid zon voor een
zonnescherm), dan mag daar best lang (een minuut?) over gedaan worden. Dat het in
praktijk binnen een microseconde afgehandeld wordt, speelt daarbij geen rol.
 Andersom, als je gebonden bent aan bepaalde hardware die nu eenmaal niet snel is
(bijvoorbeeld als een refresh van je display 200ms kost), en je zou een deadline van kleiner
dan 200ms kiezen, dan zou je meteen kunnen ophouden: je weet dan bij voorbaat dat die
deadline nooit gehaald zal worden met dat display.
 Een deadline zegt niet dat de betreffende taak al die tijd de thread voor zichzelf mag houden.
Het object met de kleinste deadline moet immers ook zijn deadline kunnen halen.
Bijvoorbeeld, je hebt:
o Een BitSend object met een deadline van 50uS
o Een display met een deadline van 200ms.
De display mag dan weliswaar in totaal 200ms over zijn update doen, maar hij moet
binnen die tijd vaak genoeg zijn thread afstaan (middels een hwlib_waitus(1)
bijvoorbeeld)) om ervoor te zorgen dat het BitSend object vaak genoeg de kans krijgt
om zijn deadline te halen. “vaak genoeg” betekent in dit geval dat elk tijdsinterval
dat display de thread voor zich alleen claimt “substantieel lager” moet zijn dan 50us.
Laten we zeggen: 10us.
Prioriteit
Nadat alle deadlines zijn ingevuld, geef je de objecten prioriteiten. Hogere prioriteiten hebben lagere
nummers. Dus prioriteit 1 is een hogere prioriteit dan prioriteit 2. Vuistregel: des te korter de
deadline, des te hoger de prioriteit.
Taakstructurering
In het voorgaande hebben we op basis van de gegeven use cases en hun beschrijvingen een object
model gemaakt, compleet met een lijst van objecten en hun beschrijvingen:
Taaksoort en deadline
Eerst vullen we per object de taaksoort en de deadline in:
Objecten Taaksoort Periode Deadline Prioriteit
InstelControl Intern, Demand Driven 30ms
TrilControl Intern, Demand Driven 30ms
Trilfequentie Geen
Display IO, Demand Driven 200ms
PlusKnop IO, Periodical 60ms
MinKnop IO, Periodical 60ms
NoodKnop IO, Periodical 60ms
TrilKnop IO, Periodical 60ms
RemoteDatabase IO, Demand Driven 3 minuten
Het waarom:
 Display
De display kan niet veel sneller dan in 200ms zijn update uitvoeren, en dat is al aan de lange
kant, dus ik kies zijn deadline scherp op 200ms. Tijdens die 200ms wil ik niet dat de
aanroepende taak geblokkeerd wordt: ik wil dat de frequentie direct kan reageren op +‐, en
dat er naar de noodknop geluisterd kan blijven worden. Daarom kies ik ervoor om de Display
een eigen taak te geven. De display is een boundary object. Het is dus een IO‐taak. De display
hoeft alleen iets te gaan doen als er nieuwe informatie naar geschreven wordt. Hij is dus
demand driven.
 InstelControl en TrilControl
De uit de use cases afkomstige control taken zijn altijd interne taken. Meestal zijn ze Demand
Driven. Dat betekent dat ze pas iets gaan doen als er een event binnenkomt.
Ik heb voor beide een deadline van 30ms gekozen. In het geval van InstelControl wil je dat
het niet te lang duurt na het indrukken van een knop dat de nieuwe frequentie naar het
display wordt geschreven. Dat display is al traag genoeg. Daar hoeft niet veel meer bij te
komen. De totale worst‐case tijd van het knop indrukken tot het moment dat je de nieuwe
tekst op de display ziet afgebeeld, bestaat namelijk uit de som van de periode van de knop,
de deadline van de knop, de deadline van InstelControl en de deadline van de display.
 TrilFrequentie
TrilFrequentie is een entiteit. Een ding met getters en setters. Vaak werken die functies bijna
instantaan, en is de overhead van een aparte taak niet de moeite waard. Dus: geen taak.
 RemoteDatabase
De aansturing van de RemoteDatabase is “fire and forget”. Je stuurt er iets naartoe, en het
wordt wel afgehandeld. Dat mag best een tijdje duren, zolang er maar een voldoende groot
channel wordt gebruikt om de log‐opdrachten te bufferen.
Periodetijden
Vervolgens kunnen we de voor de periodieke taken de periodetijden invullen:
Objecten Taaksoort Periode Deadline Prioriteit
InstelControl Intern, Demand Driven 30ms 1
TrilControl Intern, Demand Driven 30ms 1
Trilfequentie Geen
Display IO, Demand Driven 200ms
PlusKnop IO, Periodical 60ms 60ms
MinKnop IO, Periodical 60ms 60ms
NoodKnop IO, Periodical 60ms 60ms
TrilKnop IO, Periodical 60ms 60ms
RemoteDatabase IO, Demand Driven 3 minuten
Vuistregel: kies een periodetijd die gelijk is aan de deadline. Dan is de taak binnen een periode
afgehandeld. NB: de worst case tijd van afhandeling is de som van periodetijd en deadline.
Neem bijvoorbeeld de PlusKnop. Die wordt eens per 60ms gepollt. Het kan zijn dat het poll‐moment
viel net voordat de knop werd ingedrukt. Het indrukken van de knop wordt kan dus pas bij het
volgende poll‐moment, 60ms later, beginnen te worden gedetecteerd. Stel dat dat 60ms zou duren,
dan zou de totale tijd tussen het indrukken van de drukknop en het versturen van het bericht
buttonpressed dus 60ms + 60ms = 120ms zijn. In de praktijk is de detectie niet veel meer dan het
uitlezen van een pin en wat logica, en neemt die slechts een microseconde of minder in beslag. In de
praktijk is in dit geval dus de periodetijd bepalend.
Prioriteiten
Vervolgens kiezen we de prioriteiten. De hoogste prioriteit, 1 (sommigen kiezen 0) is voor de taak
met de kortste deadline (30ms). Dat zijn hier beide contol taken. Daarna volgen de knoppen, de
Display en als laatste de RemoteDatabase
Objecten Taaksoort Periode Deadline Prioriteit
InstelControl Intern, Demand Driven 30ms 1
TrilControl Intern, Demand Driven 30ms 1
Trilfequentie Geen
Display IO, Demand Driven 200ms 3
PlusKnop IO, Periodical 60ms 60ms 2
MinKnop IO, Periodical 60ms 60ms 2
NoodKnop IO, Periodical 60ms 60ms 2
TrilKnop IO, Periodical 60ms 60ms 2
RemoteDatabase IO, Demand Driven 3 minuten 4
Taken samenvoegen
Het laatste deel van de taakstructurering bestaat uit het eventueel samenvoegen van taken. Dat
samenvoegen kan op grond van verschillende soorten “cohesie” (dat is een ander woord voor
“samenhang”).
Je kunt die samenhang op vele fancy wijzen ontdekken en toepassen maar wij adviseren om het
alleen te doen volgens deze vuistregels
(reden: het moet zoden zetten en dingen niet veel complexer maken):
 Temporele Cohesie:
Periodieke taken met dezelfde periode, deadline en prioriteit kun je samennemen.
 Control cohesie:
Demand Driven taken die alleen worden aangestuurd door een enkel ander object kun je
soms samenvoegen met dat andere object. Dat kan alleen als wat ze moeten doen
“acceptabel kort is”.
Voorbeeld: in het object model zien we dat Display alleen door InstelControl wordt
aangestuurd. In de taakstructureringstabel zien we dat de Display een deadline heeft van
200ms. Als het acceptabel zou zijn dat het InstelControl 200ms moet wachten tot de display
update klaar is voordat het kan reageren op nieuwe frequentie‐aanpassingen, dan zouden
we de taak van de display dus kunnen samenvoegen met die van InstelControl.
Het lijkt mijn echter fijner dat de trilfrequentieaanpassing zo snel mogelijk wordt verwerkt na
het indrukken van een knop. Vandaar dat ik ervoor heb gekozen om display zijn eigen taak te
laten houden.
 Sequentiele cohesie:
Als er een aantal objecten altijd vlak na elkaar hun ding moeten doen kun je hun taken
samenvoegen. In deze cursus ben ik dat tot nog toe niet tegengekomen.
Wat betekent “Samenvoegen”
Dat kan twee dingen betekenen:
1. Een van de objecten verliest zijn taak. De dingen van het andere object worden (ook) in de
thread van de taak van de aanroeper uitgevoerd.
1. In het geval van temporele cohesie:
Alle betrokken objecten verliezen hun eigen taak. Er komt een extra “Handler” object met
een taak. Vanuit dat object worden periodiek “update” functies van de betrokken objecten
aangeroepen. Zodoende voeren alle betrokken objecten periodiek hun “ding” uit zonder dat
elk van hen een eigen taak nodig heeft.
Waarom Samenvoegen
Elke taak heeft een zekere overhead in cpu time en geheugen. Het doel van taken was om dingen
overzichtelijker te maken. Door het samenvoegen van taken kan een balans worden gevonden tussen
die twee wensen. Neem bijvoorbeeld de snoepautomaat. Die had 40 buttons en 40 actuatoren om
de candy bars uit te werpen. Zonder handler objecten zou je daar 80 afzonderlijke taken voor nodig
hebben gehad. Met handler objecten kun je dat op nog steeds overzichtelijke manier met 2 taken af.
Taken Samenvoegen
In het voorgaande kwamen we uit op onderstaande tabel:
Objecten Taaksoort Periode Deadline Prioriteit
InstelControl Intern, Demand Driven 30ms 1
TrilControl Intern, Demand Driven 30ms 1
Trilfequentie Geen
Display IO, Demand Driven 200ms 3
PlusKnop IO, Periodical 60ms 60ms 2
MinKnop IO, Periodical 60ms 60ms 2
NoodKnop IO, Periodical 60ms 60ms 2
TrilKnop IO, Periodical 60ms 60ms 2
RemoteDatabase IO, Demand Driven 3 minuten 4
Contol cohesie?
RemoteDatabase en Display worden alleen aangestuurd door InstelControl. We kunnen dus even
bekijken of control cohesie voor hen van toepassing is.
Voor Display geen control cohesie:
(onderstaande is ook als voorbeeld gebruikt in de voorgaande theorie)
 In het object model zien we dat Display alleen door InstelControl wordt aangestuurd. In de
taakstructureringstabel zien we dat de Display een deadline heeft van 200ms. Als het
acceptabel zou zijn dat het InstelControl 200ms moet wachten tot de display update klaar is
voordat het kan reageren op nieuwe frequentie‐aanpassingen, dan zouden we de taak van
de display dus kunnen samenvoegen met die van InstelControl.
Het lijkt mijn echter fijner dat de trilfrequentieaanpassing zo snel mogelijk wordt verwerkt na
het indrukken van een knop. Vandaar dat ik ervoor heb gekozen om display zijn eigen taak te
laten houden.
Voor RemoteDatabase geen control cohesie:
 De deadline van RemoteDatabase is zelfs groter dan die van Display. Op dezelfde gronden
kunnen we voor dit object dus besluiten om geen samenvoeging op basis van control cohesie
toe te passen.
Temporele Cohesie
Er zijn 4 periodieke taken die knop‐berichten versturen. Ze pollen met dezelfde periode en deadline,
en hebben dezelfde prioriteit. In de voorgaande theorie zagen we dat je in zo’n geval de taken kunt
samenvoegen in een taak die een nieuw object heeft: een zogenaamd Handler object.
In dit geval komt er dus een ButtonHandler object dat de taak heeft, en elke 60ms voor elke knop de
update() functie aanroept.
Nu voegen we een extra kolom aan de linkerkant van de taakstructureringstabel toe waar we de
naam van de taak invullen. Normaal gesproken is dat de naam van het object dat de taak heeft, maar
dan met het woord “Taak” in de naam. In de kolom Objecten staan alle objecten die worden
uitgevoerd in de betreffende taak. Het eerste object is het object dat de taak heeft (in dit geval van
ButtonTaak is dat dus de ButtonHandler).
Taak Objecten Taaksoort Periode Deadline Prioriteit
InstelTaak InstelControl Intern, Demand
Driven
30ms 1
TrilTaak TrilControl Intern, Demand
Driven
30ms 1
Trilfequentie Geen
DisplayTaak Display IO, Demand Driven 200ms 3
ButtonTaak ButtonHandler,
PlusKnop, MinKnop,
NoodKnop,
TrilKnop
IO, Periodical 60ms 60ms 2
DatabaseTaak RemoteDatabase IO, Demand Driven 3 minuten 4
Sidenote: of toetsen nu automatisch terugveren of niet, de berichten die ze verzenden
(buttonpressed en buttonreleased) zullen in het algemeen vergelijkbaar zijn.
Klassediagram maken
Het opstellen van het klassediagram kan in de volgende stappen worden gedaan:
1. Initiele Klassen
Maak een kopie van het object model. Vervang alle overeenkomstige objecten door klassen.
1. Publieke operaties
Schuif de berichten langs de pijlen in de richting van de pijl door naar de klasse die zich daar
bevindt. Het bericht wordt daar geimplementeerd als publieke functie. Met andere woorden:
elk bericht wordt een publieke operatie bij zijn ontvanger.
1. Verwijder dubbele pijlen
Dubbele pijlen zijn dubbelop in een klassediagram.
1. Representeer gelijksoortige objecten door een enkele klasse
2. Composition / Member variabelen
Het is handig dat wanneer je een object aanmaakt, dat dat object zelf automatisch zoveel
mogelijk de objecten aanmaakt die hij nodig heeft. Dat doe je door het toevoegen van de
benodigde objecten als private member variabelen in de member sectie van de klasse.
Probeer dus als het even kan composition toe te passen.
Vuistregel: als een object A alleen communiceert met object B, kun je overwegen om B
eigenaar te maken van object A. Test dan nog even of “B heeft een A” natuurlijk klinkt.
Regel: Zodra B eigenaar is van object A, kan een composition‐relatie van B naar A worden
getekend (het zwarte wiebertje aan de kant van de eigenaar).
Als er al een pijl van B naar A liep, mag deze dan worden verwijderd.
Immers: eigenaarschap impliceert kennen: als je een member variabele hebt, kun je zijn
member functies aanroepen. Je hebt daar dan geen reference meer voor nodig.
1. Member references
De pijlen in het klassediagram die niet zijn omgezet in composition relaties betekenen alleen
nog “kennen”, geen eigenaarschap (want de pijlen die eigenaarschap vertegenwoordigden
zijn in de vorige stap al omgezet naar compositie‐relaties). Voeg voor elk object dat een
klasse “kent” een private member reference variabele toe.
1. Listener Patterns
Klassen die berichten versturen naar andere klassen moeten die andere klassen kennen.
Daardoor werken ze alleen met die andere klassen. Als je klassen algemener
toepasbaar/herbruikbaar wilt maken, moet je ze hun berichten laten sturen naar een
zogenaamde “Listener”. Dat is een interface klasse die de juiste functies voor de berichten
bevat. Zodoende kunnen alle klassen die afleiden van zo’n interface klasse (ook toekomstige
klassen) probleemloos naar de verstuurde berichten “luisteren”. Buttons zijn bijvoorbeeld
typisch klassen die je in meerdere designs wilt kunnen hergebruiken. (TODO: insert doc over
listener patterns).
1. Markeer isActive
Markeer klassen die een taak hebben met het (extra) stereotype <<isActive>>.
1. Voeg Handler klassen toe
Voeg de extra Handler klassen toe die zijn ontstaan als gevolg van de taaksamenvoeging van
periodieke taken.
1.  Weak dependencies
Het kan zijn dat een klasse in een van de functie‐parameters van een van zijn functie een
klasse gebruikt waarvan hij verder geen member of reference member heeft. In dat geval
laat je de afhankelijkheid zien mbv een “weak dependency” relatie (een gestippelde pijl).
Voorbeeld: Stel je voor dat je Display klasse een DrawRect(rect:Rect) functie heeft.
De Rect wordt alleen als tijdelijke variabele meegegeven aan de DrawRect functie. De Display
klasse heeft verder geen members of member references van type Rect. In dat geval is de
Dislay “weak dependent” van Rect, en loopt er een gestippelde pijl van Display naar Rect om
dat aan te geven. Hetzelfde geldt als een tijdelijk object van een klasse in een functiebody
wordt aangemaakt. Bijvoorbeeld als je display klasse de functie update() heeft, en die functie
in zijn body een tijdelijk Rect object aanmaakt.
Het nut van het ook het weergeven van de weak dependencies is dat als je bijvoorbeeld een
library van je klassen wilt maken, dat je ziet van welke andere libraries die allemaal
afhankelijk moet zijn en waarom.
1.  Multiplicity
Zorg dat aan het uiteinde van de de associatiepijlen en de compositie‐relaties de juiste
multipliciteit in het klassediagram is aangegeven.
Tel eenvoudigweg hoeveel members en reference members een klasse heeft.
Voorbeelden:
a. 1..3 betekent: 1 tot 3.
Bijvoorbeeld in het geval van een array met 3 entries waar pointers in opgeslagen
kunnen worden.
b. * betekent: 0 of meer.
Bijvoorbeeld in het geval van een vector.
c. 2..* betekent: 2 of meer.
Bijvoorbeeld: .. ik kan even niets bedenken. Dit komt niet vaak voor.
d. Niets aangeven betekent: 1.
Klassediagram maken
Stap 1: initiele klassen
 Maak een kopie van het object model.
 Vervang alle objecten door klassen.
Dit was het object model waar we op waren uitgekomen:
Onderstaand zijn de objecten vervangen door klassen (dwz de blokken krijgen 3 compartimenten per
blok). NB: het mag nog geen klasse‐diagram heten, maar dit is de eerste stap in de transitie van
Object model naar Klasse diagram.
Stap 2: publieke operaties
Schuif de berichten langs de pijlen in de richting van de pijl door naar de klasse die zich daar bevindt.
Het bericht wordt daar geimplementeerd als publieke functie. Met andere woorden: elk bericht
wordt een publieke operatie bij zijn ontvanger.
Voorbeelden:
 In bovenstaande diagram zie je dat InstelControl het bericht getTrilfrequentie stuurt naar de
entiteit Trilfrequentie. Daarom geven we de entiteit Trilfrequentie een publieke functie met
de naam getTrilfrequentie.
 Je ziet dat de PlusKnop een bericht buttonPressed(plusKnopID) stuurt naar InstelControl. Dat
bericht is van dezelfde vorm als het bericht buttonPressed(minKnopID) dat MinKnop stuurt
naar InstelControl. We geven InstelControl daarom een publieke functie
buttonPressed(buttonID:eButtonID). Voor de functieparameter buttonID kies ik een enum
type, genaamd eButtonID: enum eButtonID {PlusKnopID,MinKnopID,NoodKnopID,TrilKnopID}.
Zo kan aan de functie buttonpressed een identifier van de knop worden meegegeven. Binnen
de functie kan dan middels bijvoorbeeld een switch statement gekeken worden om welke
knop het gaat en welke dus actie nodig is.
 Je ziet verder dat InstelControl twee verschillende showMessage berichten stuurt naar de
Display. Ik kies ervoor om Display een publieke functie showMessage(str:string) te geven. Het
string argument is flexibel genoeg om de twee verschillende berichten te kunnen
overbrengen.
Na het omzetten van de berichten in publieke operaties ziet ons halffabrikaat klassediagram er zo uit:
Stap 3: verwijder dubbele pijlen
In het bovenstaande diagram zie je vanuit InstelControl twee pijlen lopen naar Trilfrequentie. Een
enkele pijl volstaat om aan te geven dat functies uit de klasse Trilfrequentie worden aangeroepen
vanuit de klasse InstelControl. Na weglaten van een van beide pijlen blijft dit dus over:
Stap 4: Representeer gelijksoortige objecten door een enkele
klasse
In het bovenstaande diagram zijn PlusKnop en MinKnop 100% gelijksoortig: beide roepen ze de
functie buttonPressed en buttonReleased van een object van klasse InstelControl aan. We kunnen
daarom de objecten PlusKnop en MinKnop prima instanties maken van een enkele klasse. Die klasse
noem ik InstelControlKnop.
Na deze samenvoeging ziet het klassediagram‐halffabrikaat er zo uit:
NB: NoodKnop kunnen we (nog) niet samenvoegen met InstelControlKnop, want objecten van type
NoodKnop sturen hun berichten ook naar een object van type TrilControl.
Stap 5: Composition / Member variabelen
Het is handig dat wanneer je een object aanmaakt, dat dat object zelf automatisch zoveel mogelijk de
objecten aanmaakt die hij nodig heeft. Dat doe je door het toevoegen van de benodigde objecten als
private member variabelen in de member sectie van de klasse.
Vuistregel: als een object A alleen communiceert met object B, kun je overwegen om B eigenaar te
maken van object A. Test dan nog even of “B heeft een A” natuurlijk klinkt.
 Display, InstelControlKnop en RemoteDatabase communiceren alle alleen met InstelControl.
Het licht daarom voor de hand om hen allen een member variabele van InstelControl te
maken. Zodra je een InstelControl object aanmaakt, worden dan automatisch objecten van
de genoemde klassen aangemaakt. Dat hoeft de programmeur die een instantie van
InstelControl codeert dan niet meer zelf “handmatig” te doen, waardoor zijn code compacter
en overzichtelijker wordt.
Gevolgen:
o De pijlen vanuit InstelControl naar Display en RemoteDatabase kunnen worden
vervangen door een compositie‐relatie.
o Er komt ook een compositie‐relatie van InstelControl naar InstelControlKnop.
De pijl vanuit InstelControlKnop naar InstelControl wordt daar NIET door vervangen.
Immers: composition impliceert alleen dat de eigenaar zijn eigendom kent. Zonder
de extra pijl vanuit eigendom naar eigenaar zou niet duidelijk zijn dat in dit geval het
eigendom de eigenaar moet kennen. InstelControlKnop moet zijn eigenaar
InstelControl immers kennen om er buttonPressed berichten naartoe te kunnen
sturen.
NB: InstelControlKnop is de klasse waarmee de objecten PlusKnop en MinKnop uit
het object model worden geinstantieerd. InstelControl krijgt dus de members
plusKnop en minKnop, beide van klasse InstelControlKnop.
 TrilKnop en Electromagneet communiceren alleen met TrilControl. Het licht dus voor de hand
om die twee objecten als members toe te voegen aan TrilControl.
Gevolgen:
o De pijl vanuit TrilControl naar Electromagneet kan worden vervangen door een
compositie‐relatie.
o Er komt ook een compositie‐relatie van TrilControl naar TrilKnop.
De pijl vanuit TrilKnop naar TrilControl wordt daar NIET door vervangen. TrilKnop
moet zijn eigenaar TrilControl immers kennen om er buttonPressed berichten
naartoe te kunnen sturen.
 NoodKnop stuurt zowel berichten naar InstelControl als naar TrilControl. Het is dus niet
logisch om InstelControl of TrilControl eigenaar te maken van Noodknop (een object kan
immers maar eigendom van een ander object zijn).
 Trilfrequentie ontvangt berichten van zowel InstelControl als van TrilControl. Om dezelfde
reden kies ik ervoor om het een globaal object te laten zijn, en het niet in eigendom te geven
van InstelControl of TrilControl.
In het geval van Trilfrequentie zou je echter kunnen betogen dat het meer hoort bij
InstelControl dan bij TrilControl: InstelControl is “de bron” van de informatie. TrilControl
vraagt die alleen even op. Het zou dus ook verdedigbaar zijn geweest om Trilfrequentie een
composite member te maken van InstelControl.
In dat geval zou TrilControl er niet direct bij kunnen. Je zou dan bijvoorbeeld InstelControl
een getTrilfrequentie member functie kunnen geven die dan door TrilControl wordt
aangeroepen en de aanroep doorspeelt naar Trilfrequentie.
Na het toepassen van bovenstaande compositie ziet het klassediagram er zo uit:
Stap 6: Member References
De pijlen in het klassediagram die niet zijn omgezet in composition relaties betekenen alleen nog
“kennen”, geen eigenaarschap (want de pijlen die eigenaarschap vertegenwoordigden zijn in de
vorige stap al omgezet naar compositie‐relaties). Voeg voor elk object dat een klasse “kent” een
private member reference variabele toe.
Bijvoorbeeld:
 InstelControl kent een object van type Trilfrequentie. We voegen dus een reference member
variabele van het type Trilfrequentie& toe aan InstelControl.
Etc..
Na deze exercitie ziet het klassediagram er als volgt uit:
Stap 7: Listener Patterns toepassen
Klassen die berichten versturen naar andere klassen moeten die andere klassen kennen. Daardoor
werken ze alleen met die andere klassen. Als je klassen algemener toepasbaar/herbruikbaar wilt
maken, moet je ze hun berichten laten sturen naar een zogenaamde “Listener”. Dat is een interface
klasse die de juiste functies voor de berichten bevat. Zodoende kunnen alle klassen die afleiden van
zo’n interface klasse (ook toekomstige klassen) probleemloos naar de verstuurde berichten
“luisteren”. Buttons zijn bijvoorbeeld typisch klassen die je in meerdere designs wilt kunnen
hergebruiken.
 ButtonListener
In bovenstaand diagram zien we verschillende klassen die alle bedoeld zijn om knopinstanties
te maken. Ze fungeren hetzelfde. Alleen zijn de klassen die naar hun berichten
luisteren anders. De belangrijkste regel van bijna alle patterns is: “abstraheer het
veranderlijke”. Anders gezegd: verschuil alles wat kan veranderen achter een abstracte
interface. Bij een listener pattern is dat niet anders. Het veranderlijke is de listener. Dus moet
er een abstracte interface komen voor de listener. In dit geval noemen we die
“ButtonListener”. Zodra die interface er is, kunnen de knoppen voortaan altijd tegen
diezelfde interface praten in plaats van tegen een specifieke klasse als InstelControl of
TrilControl. We hoeven dan dus slechts een maal een Button klasse te maken met
bijbehorende ButtonListener interface. Die kunnen we dan in alle situaties hergebruiken.
 Button.addButtonListener
Sommige Buttons, zoals NoodKnop, sturen berichten naar meerdere listeners. In het
algemeen zul je aan een knop daarom meerdere listeners willen kunnen opgeven waar hij
zijn berichten naar moet versturen. Dat kan bijvoorbeeld door het toevoegen van een
pointer naar een ButtonListener aan een array van pointers naar ButtonListener. De functie
die dat doet noem ik addButtonListener.
 Alleen voor klassen die berichten versturen
NB: Het listener pattern kun je alleen toepassen op klassen die berichten versturen.
Een actuator als bijvoorbeeld een Servo, die alleen berichten ontvangt, kun je ook wel
abstraheren met een interface. Maar dat is dan geen listener pattern (de Servo hoeft geen
lijst met listeners bij te houden).
In onderstaande klassediagram is het listener pattern toegepast op de knoppen.
Nu valt op:
 Alle Knop Klassen zijn vervangen door een one and only knop klasse, genaamd Button.
 InstelControl en TrilControl krijgen nog steeds dezelfde berichten binnen voor de buttons,
maar dit keer lopen die berichten via de ButtonListener.
 Door middel van het stereotype <<interface>> is aangegeven dat ButtonListener een
interface klasse is.
 Het is ook te zien aan de inheritance relatie via welke van ButtonListener wordt geerft: die
heeft om die reden (erven van een interface) een gestippelde lijn.
 Voordat het listener pattern was toegepast, kenden bijvoorbeeld TrilControl en TrilKnop
elkaar. Er was sprake van een circular dependency. Dat geeft bij het programmeren onhandig
gedoe met forward declarations (om het kip‐ei probleem te doorbreken voor de compiler).
 Nadat het listener pattern is toegepast, is er geen circular dependency meer: TrilControl kent
de Button klasse en de ButtonListener klasse waarvan hij afleidt. De Button kent alleen de
ButtonListener klasse. Er is geen circeltje van afhankelijkheden meer voor de compiler.
Een weak dependency – of toch een normale associatie voor het noodKnop object?
In een klassediagram gaat een deel van de informatie uit het object model verloren. Toch kun je aan
de member variabelen plusKnop, minKnop en trilKnop nog zien welke knoppen InstelControl en
TrilControl heeft, en er dus vermoedelijk naar luistert.
Zoals gezegd, het mooist is als elke klasse die luistert naar objecten, aan die objecten zichzelf als
listener toevoegt (via een aanroep van addButtonListener). De geeigende plek daarvoor is de
constructor.
Nu was er ook een knop object, genaamd NoodKnop, die geen eigendom is van InstelControl en
TrilControl, maar waarvan InstelControl en TrilControl toch berichten willen ontvangen.
Je kunt dan bijvoorbeeld een reference naar NoodKnop meegeven aan de constructor van
InstelControl. Die kan dan die reference gebruiken om van dat NoodKnop object addButtonListener
aan te roepen:
class InstelControl : ButtonListener
{
Button plusKnop;
Button minKnop;
InstelControl(Button& noodKnop)
{
plusKnop.addButtonListener(this);
minKnop.addButtonListener(this);
noodKnop.addButtonListener(this);
}
…etc
Naar het noodknop object zou InstelControl dan een weak dependency hebben.
Aan een weak dependency kun je alleen niet zien of de dependency een functieparameter betreft of
de functiebody. Het dwingt ook niet de aanwezigheid van een reference variabele af.
Je kunt de reference member ook opslaan (hoewel InstelControl hem later niet meer nodig heeft):
class InstelControl : ButtonListener
{
Button plusKnop;
Button minKnop;
Button& noodKnop;
InstelControl(Button& noodKnop):noodKnop(noodKnop)
{
plusKnop.addButtonListener(this);
minKnop.addButtonListener(this);
noodKnop.addButtonListener(this);
}
…etc
In dat geval is het zowel in de member sectie in de code van de klasse als in de member sectie van
het klasse diagram duidelijker dat InstelControl ook berichten verwacht van een permanent
aanwezige knop met de naam noodKnop. Om die reden kies ik voor die oplossing. InstelControl en
TrilControl krijgen dus ook een reference member noodKnop:Button&. InstelControl heeft dus
sommige buttons, maar refereert alleen naar andere. Om dat te weer te geven voegen we naast de
compositiepijl tussen TrilControl en Button ook nog een gewone associatiepijl toe:
Stap 8: Markeer isActive
Markeer klassen die een taak hebben met het (extra) stereotype <<isActive>>.
Stap 9: Voeg Handler klassen toe
Voeg de extra Handler klassen toe die zijn ontstaan als gevolg van de taaksamenvoeging van
periodieke taken.
Bij de stap taakstructurering / taaksamenvoeging is voorzien dat het een goed idee is om een
extra <<isActive>> ButtonHandler klasse aan te roepen die voor alle Button objecten een update()
functie aanroept. De Button objecten hebben dan geen eigen taak meer nodig.
Zo gezegd, zo gedaan:
Merk op: omdat we nu een ButtonHandler gebruiken, konden we <<isActive>> bij de Button
weghalen.
Stap 10: Weak dependencies
Weak dependencies
Het kan zijn dat een klasse in een van de functie‐parameters of in zijn functiebody van een van zijn
functie een klasse gebruikt waarvan hij verder geen member of reference member heeft. In dat geval
laat je de afhankelijkheid zien mbv een “weak dependency” relatie (een gestippelde pijl).
InstelControl en TrilControl kennen de ButtonHandler. Het idee is dat in hun constructor er de
knoppen aan toevoegen die ze in hun eigendom hebben. Ze hoeven ButtonHandler dus alleen te
kennen binnen de functiebody van hun constructor. Het meegeven van een refrenence van de
ButtonHandler aan de constructor van InstelControl en TrilControl volstaat dus. Het is daarom niet
nodig dat InstelControl en TrilControl zelf een reference member hebben naar de buttonhandler.
Voor dit ontwerp hebben we eerder gezien dat de afhankelijkheid van het noodknop object met een
weak dependency gemodelleerd had kunnen worden. Ik heb er echter bewust voor gekozen (zie eind
van het hoofdstuk over Listeners) om in plaats daarvan een member variabele noodKnop:Button&
aan TrilControl en InstelControl toe te voegen. Daarmee werd het een “gewone” associatie.
Stap 10: Multiplicity
Zorg dat aan het uiteinde van de de associatiepijlen en de compositie‐relaties de juiste multipliciteit
in het klassediagram is aangegeven.
Tel eenvoudigweg hoeveel members en reference members een klasse heeft.
 InstelControl heeft 2 Buttons (plusKnop en minKnop). Aan het eind van zijn compositierelatie
naar de klasse Button moet dus een 2 komen te staan.
 TrilControl heeft 1 Button (trilKnop). Aan het eind van zijn compositierelatie naar de klasse
Button moet dus een 1 komen te staan.. of worden weggelaten (dat betekent ook 1). Ik
noteer overal netjes een 1. Dan is voor mezelf duidelijk dat ik geen tak ben vergeten te
beschouwen.
 InstelControl en TrilControl hebben beide een reference naar een Button (noodKnop). Naast
de “gewone” associatiepijl naar Button vanuit die klassen noteer ik daarom een 1.
 De klasse ButtonHandler heeft een array (misschien wel een vector) van niet nader
genoemde grootte. Je kunt er via zijn addButton functie een willekeurig aantal Buttons aan
toevoegen. Naast zijn associatiepijl naar Button noteren we daarom een *.
NB: dat er run‐time in ons design 4 buttons aan worden toegekend, doet er niet toe.
 Iets soortgelijks geldt voor de Button klasse. Die heeft een array met ButtonListeners
(misschien wel een vector) van niet nader genoemde grootte. Je kunt er via zijn
addButtonListener functie een willekeurig aantal ButtonListeners aan toevoegen. Naast zijn
associatiepijl naar ButtonListener noteren we daarom een *.
Met de multipliciteiten verwerkt krijgen we dus:
Synchronisatiemechanismen
Het is goed gebruik om taken alleen te laten communiceren en data te laten uitwisselen via
synchronisatiemechanismen.
De voordelen van het gebruik van synchronisatiemechanismen zijn:
1. Taken kunnen dingen aan elkaar doorgeven en vervolgens zelf doorgaan met hun eigen taak
(= asynchroniteit).
1. Data wordt veilig doorgegeven tussen de taken. Het RTOS voorkomt bijvoorbeeld door
middel van het gebruik van mutexen waar nodig dat data nooit gelijktijdig door meerdere
taken wordt bepoteld (anders zou het bijvoorbeeld kunnen voorkomen dat terwijl een struct
nog wordt gelezen door de ene taak, dat de andere taak al een deel ervan aan het
overschrijven is, waardoor de data niet meer consistent is.
De synchronisatiemechanismen die we binnen rtos gebruiken zijn:
 Waitables
Waitables zijn events waar je middels de rtos functie wait() op kunt wachten. Een waitable
hoort altijd bij een enkele taak. Alleen die ene taak kan op de waitable wachten. Zodra een
waitable/event waarop gewacht werd “is opgetreden”, wordt hij automatisch weer gereset.
Dit zijn de rtos waitables die tot je beschikking staan:
o Flag
De ene taak set een flag. De andere taak kan er op wachten. Het “afgaan” van een
flag betekent “let op”. Niet meer, niet minder. Een flag is dus niet hetzelfde als een
bool. Als iemand tegen je zegt “let op”, weet je niet of hij “true” of “false” bedoelt.
o Channel
Een channel is een FIFO (first in, first out) queue waar je op kunt wachten.
Zodra er iets in de channel wordt geschreven is zal de er aan gelieerde
waitable/event optreden.
int newTemperature = tempChannel.read();
Uiteraard moet er een andere taak zijn die iets in de channel schrijft:
tempChannel.write(30);
o Timer
Je kunt een timer object gebruiken als een soort kookwekker. Na het aanroepen van
zijn start() functie ga je normaal gesproken gelijktijdig ook op andere waitables
wachten. Als je alleen op de timer zelf zou wachten, had je in het algemeen ook
uitgekund met een eenvoudige hwlib::waitus() aanroep.
 Pool
Een pool is een variabele die gewrapped is in het pool<> template.
Neem bijvoorbeeld het object:
pool<int> temperatuurPool
Dat is een int, gewrapped in het pool<> template. Je kunt de int veilig lezen en schrijven door
de read() en write() member functies van de pool<> template te gebruiken.
Een pool is geen waitable. Elke taak kan er naar believen uit lezen of naartoe schrijven.
 Mutexen
Als je voor RTOS designt, heb je veelal genoeg aan de bovengenoemde
synchronisatiemechanismen. In een uitzonderlijk geval wil je misschien dat een reeks
activiteiten altijd gegroepeerd moet worden uitgevoerd, dus dat het klaar moet zijn voordat
een andere taak dezelfde reeks start. In dat geval kun je die reeks activiteiten beschermen
met een mutex. Daar ga ik in dit document niet verder op in.
STDs ontwerpen
Objecten die code uitvoeren binnen een taak volgen meestal een toestandsdiagram (een STD).
In het algemeen zijn dat de <<control>> objecten. Maar ook veel boundary objecten die periodieke
taken verrichten doorlopen ook een STD.
Hoe kom je vanuit een gegeven klassediagram tot de STDs?
Dat gaat in de volgende stappen:
 Maak de interface sectie van het STD
 Schrijf voor jezelf in woorden de reeks van acties en beslissingen op die horen bij de
uitvoering van de taak van het betreffende object.
 Zet je beschrijving om in een STD:
o Als je ergens op wacht, dan maak je daar een event van langs de uitgaande pijl van
een toestand. Bedenk ook een passende naam voor de toestand. Op de timer events
na zijn events altijd afkomstig uit de STD interface (zie verderop).
o Bijvoorbeeld als je wacht tot de “aan‐knop” is ingedrukt, maak dan een toestand met
de naam “uit”, en verlaat die via een uitgaande pijl met de event “flagAanButton”.
o Bedenk je of er actions zijn die altijd moeten gebeuren bij het binnengaan van de
toestand (entry events), bij het verlaten van de toestand (exit events) of tijdens een
event langs een uitgaande pijl.
De acties kunnen voor een deel bestaan uit aanroepen van publieke
memberfuncties van andere objecten. In het klassediagram kun je zien welke andere
objecten je klasse kent en heeft, en dus welke publieke functies er aangeroepen
kunnen worden.
o Verwerk je logische beslissingen met behulp van guards en eventueel decision nodes.
o Voorkom duplicate actions en guards eventueel met het gebruik van merge nodes.
o Gebruik eventueel een samengestelde toestand (composite state) als het gedrag uit
meerdere lagen bestaat.
Timers
Net als bij de overige typen waitables (flags, channels) – zie onderstaand – zouden er nu in het STD
ook timer objecten kunnen worden gebruikt. Timers zijn een vreemde eend in de bijt. Wanneer
gebruik je daar nu wel of niet een apart object voor in je STD? De vuistregel is: Benoem in je STD
geen apart timer object als:
 Je timer altijd wordt gestart in het entry‐event van een enkele, specifieke toestand, en de
toestand altijd verlaten wordt bij het vuren van zijn timer‐event
In zo’n geval kun je bijvoorbeeld after(1000ms) naast de uitgaande pijl zetten (dat impliceert dat de
betreffende timer is gestart tijdens het entry‐event).
In de overige gevallen geef je de timer een naam, en start je hem expliciet, met bijvoorbeeld
myTimer.start(1000), en kan de timer‐event eventueel afgehandeld worden door een event‐handler
in de body‐sectie (het deel tussen entry en exit event) van de betreffende toestand. Voorbeeld:
myTimer/doAction().
Ontwerp van de STD interface
 Het ontwerpen van STDs begint met het ontwerp van zijn interface sectie.
Het STD communiceert met andere taken via de interface functies in zijn interface sectie.
 Die interface functies worden uitgevoerd in de thread van de aanroepende taak.
Je kunt de STD interface ontwerpen met de volgende vuistregels:
1. Voeg elke publieke functie van de klasse waarvoor je een STD maakt, en die wordt
aangeroepen door een andere taak, toe aan de STD interface.
1. Je kunt de publieke functies in twee soorten verdelen:
o Functies die “even snel” een waarde opvragen:
Bijvoorbeeld getTemperature() en isTemperatureTooHigh().
Die functies implementeer je door een pool waarde te retourneren.
Voorbeeld van zo’n functie:
float getTemperature() {return temperaturePool.read();}
De betreffende pool maak je een member van de klasse van het STD.
De notatie van zo’n functie in de interface sectie is zoiets:
getTemperature/return temperaturePool.read()
De types van parameters en return values noteer je daar dus niet.
o Overige functies – in het algemeen functies die een bericht doorgeven of expliciet
opdracht geven om iets te gaan doen. Die functies kun je ook weer in twee
categorien verdelen:
 Functies zonder argument
Functies zonder argument, zoals bijvoorbeeld zetAan() implementeer je door
een flag te zetten:
zetAan/flagAan.set()
 Functies met argument
 Als alleen de laatst binnengekomen waarde ertoe doet
Als alleen de laatst binnengekomen waarde ertoe doet,
implementeer je zo’n functie met een pool en een flag. De waarde
wordt in de pool geschreven en de flag wordt gezet om te signaleren
dat er een nieuwe, nog niet verwerkte waarde is. Voorbeeld:
buttonPressed(buttonID)/buttonIdPool.write(buttonID);buttonFlag.s
et()
 Als het belangrijk is dat je geen voorgaande waarde misloopt
Als het belangrijk is dat je geen voorgaande waarde misloopt, kun je
in plaats van een flag+pool combinatie zoals hierboven beter kiezen
voor een channel:
buttonPressed(buttonID)/buttonChannel.write(buttonID)
Ontwerp van het STD van InstelControl
We beginnen met het ontwerp van de STD interface
Ontwerp van de STD interface
We beginnen met een blik op onze klasse in het klassediagram:
Er zijn welgeteld twee publieke functies. Dat worden dus de functies van de STD interface.
In beide gevallen wordt er een parameter meegegeven. Nu moet er een knoop worden doorgehakt
over of we voor een flag met pool of voor een channel kiezen om de nieuw binnengekomen waarde
mee te bufferen.
Als de noodKnop wordt ingedrukt, willen we dat absoluut niet missen. Je zou dat kunnen borgen
door aan de Button een IsButtonPressed functie toe te voegen die altijd gepollt kan worden. Je kunt
het ook borgen door alle binnenkomende buttonPresses te bufferen in een channel.
Verder is er ook weer niet veel risico dat er uberhaupt iets wordt gemist: InstelControl heeft behalve
het updaten van de frequentie na zo’n buttonpress toch niets te doen.
Werken met events heeft in het algemeen de voorkeur boven pollen, dus ik kies ervoor om ook de
noodKnop via events af te handelen. Om dat veilig te kunnen doen, kies ik voor het gebruik van een
channel.
De STD interface van InstelControl komt er dus zo uit te zien:
NB: de horizontale lijn (in andere dictaten soms weggelaten) verduidelijkt dat deze STD werkt met
meerdere threads tegelijk: het gedeelte boven de lijn wordt uitgevoerd in de aanroepende thread.
Het gedeelte onder de lijn (de eigenlijke STD, hier nog niet ingevuld) wordt uitgevoerd door de
thread van de taak waar de STD toe behoort.
Actiereeks van InstelControl in woorden
Wat InstelControl moet doen, staat beschreven in de beschrijving van de use case Instellen.
Er blijkt een uitzonderingssituatie te zijn:
Na indrukken van de noodknop moet “Emergency” op het scherm getoond worden. Na intrekken van
de noodknop mag de normale use case weer hervat worden.
De normale use case wacht op het indrukken van een button. Dat wordt gedaan vanuit een toestand
die ik maar “Normaal” noem.
Is het de plusKnop, dan moet de frequentie verhoogd worden, tenzij 100 is bereikt.
Is het de minKnop, dan moet de frequentie verlaagd worden, tenzijn 1 is bereikt.
Is het de noodKnop, dan moet naar de NoodToestand gegaan worden.
Een minuut nadat de laatste frequentie update plaatsvond, moet dat worden gelogd.
Hetzelfde verhaal, maar nu met toestanden, events en acties er aan toegevoegd.
Er blijkt een uitzonderingssituatie te zijn:
Na indrukken van de noodknop moet “Emergency” op het scherm getoond worden. Zoals de STD
interface laat zien, kom je daar achter door te wachten op en lezen uit buttonPressChannel. Het
tonen van “Emergency” op het scherm kan doormiddel van de aanroep van display.showMessage.
De betreffende toestand waar we dan in gekomen zijn noem ik “Noodtoestand”. Na intrekken van
de noodknop mag de use case weer hervat worden. Dus vanuit de Noodtoestand moet weer op
buttonReleaseChannel gewacht, en vervolgens gelezen worden.
De normale (zonder uitzonderingen) use case wacht ook op het indrukken van een button. Dat wordt
gedaan vanuit een toestand die ik maar “Normaal” noem.
Is het de plusKnop, dan moet de frequentie verhoogd worden, tenzij 100 is bereikt.
Is het de minKnop, dan moet de frequentie verlaagd worden, tenzijn 1 is bereikt.
Is het de noodKnop, dan moet naar de NoodToestand gegaan worden.
We zijn hier alleen geinteresseerd zijn in de inhoud van bnPressChannel. Toch moet ook
bnReleaseChannel gelezen worden, zodat die niet vol met oude rommel staat wanneer we weer naar
de toestand NoodToestand gaan.
In de noodtoestand zijn we dus alleen geinteresseerd in de inhoud van de bnReleaseChannel.
Toch moet daar ook de bnPressChannel gelezen worden, zodat die niet vol met oude rommel staat
wanneer we weer naar de toestand Normaal gaan.
Een minuut nadat de laatste frequentie update plaatsvond, moet dat worden gelogd. Dus bij de
frequentie update moeten we als actie een timer start uitvoeren. Voor wat betreft het loggen: laten
we zeggen dat het niet uitmaakt of het systeem zich ten tijde van dat loggen in de Normaal toestand
of in de Noodtoestand bevindt. Vanuit beide toestanden moet dus worden geluisterd naar het
aflopen van de timer, en in dat geval de actie remoteDataBase.log(trilFrequentie.getTrilFrequentie())
uitvoeren. In het STD gebruiken we geen after() voor deze timer, maar benoemen we hem expliciet,
omdat hij in meerdere toestanden wordt gebruikt.
Het STD van InstelControl
Na verwerking van het bovenstaande ontstaat dus het volgende STD van InstelControl
Van STD naar Code
Het omzetten van een STD naar Code gaat vrij rechttoe rechtaan:
1. Creeer een klasse die is afgeleid van rtos::task
2. Creeer een enum waarmee de toestanden geduid kunnen worden.
3. Voeg de member variabelen en references toe zoals aangegeven in het klassediagram.
(normaliter zijn die private).
1. Voeg een constructor toe die:
a. De reference members initialiseert.
b. Als de klasse een listener is, laat het eigen object zich als listener toevoegen aan de
objecten waar het naar luistert.
c. Voeg de members die een Handler nodig hebben toe aan de betreffende Handler.
1. Maak voor elke STD interface een gelijknamige publieke functie aan. De code kun je 1 op 1
overnemen.
1. Implementeer de main() functie:
a. Creeer een switch statement dat springt naar de code voor de huidige toestand.
b. Voer daar als eerste de entry event code uit.
c. Vervolgens eventuele “do” code.
d. Wacht op het optreden van events:
auto evt = wait( een of meer waitables hier )
e. Interpreteer de event, en laat de bijbehorende guard, actie en/of transitie uitvoeren:
if(evt=flagButton){state = Idle;}
Timers
Net als bij de overige waitables (flags, channels) zouden er nu in de code timer objecten kunnen
worden aangemaakt. Timers zijn een vreemde eend in de bijt. Wanneer maak je daar nu wel of niet
een object voor aan in je code? De vuistregel is: als je alleen op de timer gaat wachten en
ondertussen niets anders doet, hoef je geen apart timer object aan te maken. Je gebruikt dan in de
code bijvoorbeeld een hwlib::waitus(1000) call. De code gaat pas verder na het verstrijken van die
tijd.
Je maakt wel expliciet een timer object aan bij “time‐out” situaties. Het aparte timer object is dan als
een kookwekker die na enige tijd een event kan genereren. In de code kan dan worden gewacht op
zowel die timer als op andere events. Daardoor kan het object tot de timer afgaat door blijven gaan
met andere dingen.
Van STD naar code van InstelControl
De eerste 5 stappen zijn vrij rechttoe rechtaan en leiden tot de volgende code:
#include "hwlib.hpp"
#include "rtos.hpp"
// Onderstaande enum wordt zowel door TrilControl en InstelControl
// Gebruikt. Hij moet dus in een aparte header file staan die door
// beide wordt geinclude. Voor het overzicht zet ik het toch even
// erbij, hier.
enum eButtonID = {MinKnopID,PlusKnopID,TrilKnopID,NoodKnopID};
class InstelControl : public rtos::task<>{
enum state_t = {NORMAAL, NOODTOESTAND};
private:
state_t state = NORMAAL;
rtos::channel bnPressChannel;
rtos::channel bnReleaseChannel;
Trilfrequentie& trilFrequentie;
Button& noodKnop;
Button plusKnop;
Button minKnop;
Display display;
RemoteDatabase remoteDatabase;
rtos::timer logTimer;
InstelControl(Trilfrequentie& trilFrequentie, Button& noodKnop,
ButtonHandler& buttonHandler):
trilFrequentie(trilFrequentie),noodKnop(noodKnop)
{
// Meld objecten die door een handler aangezwengeld worden
// aan bij de betreffende handler.
buttonHandler.addButton(&plusKnop);
buttonHandler.addButton(&minKnop);
buttonHandler.addButton(&noodKnop);
// Aanname hierbij: de handler negeert
// herhaaldelijk aanmelden van dezelfde knop.
// Meld mezelf als ButtonListener aan bij de buttons waar ik
// naar luister.
plusKnop.addButtonListener(this);
minKnop.addButtonListener(this);
noodKnop.addButtonListener(this);
}
public:
void buttonPressed(eButtonID buttonID)
{bnPressChannel.write(buttonID);}
void buttonReleased(eButtonID buttonID)
{bnReleaseChannel.write(buttonID);}
Zoals eerder besproken, wordt het paradigma gehanteerd dat de eigenaar van een Button die button
ook aanmeldt bij de ButtonHandler.
Ook de vervolgstap, de uitwerking van de STD in code is ook rechttoe, rechtaan. Dit is de
implementatie van de toestand Normaal:
private:
void main(){
eButtonID bnID;
eButtonID bnReleaseID;
eButtonID dummID;
for(;;){
switch(state)
{
case NORMAAL:
// entry event
display.showMessage(trilFrequentie.getTrilFrequentie());
// overige events
auto evt = wait(bnPressChannel,
bnReleaseChannel,logTimer);
if(evt==logTimer)
{
remoteDatabase.log
(trilFrequentie.getTrilFrequentie());
}
else if(evt==bnPressChannel)
{
bnID=bnPressChannel.read();
if(bnID==NoodKnopID)
{
state = NOODTOESTAND;
}
else if((bnID==MinKnopID)&&
(trilFrequentie.getTrilFrequentie()>1)
{
trilFrequentie.setTrilFrequentie
(trilFrequentie.getTrilFrequentie()-1);
logTimer.start(60000000);
}
else if((bnID=PlusKnopID)&&
(trilFrequentie.getTrilFrequentie()<100))
{
trilFrequentie.setTrilFrequentie
(trilFrequentie.getTrilFrequentie()+1);
logTimer.start(60000000);
}
else
{
state = NORMAAL;
}
}
else // evt == bnReleaseChannel
{
// remove the content from the channel.
dummID=bnReleaseChannel.read();
}
break;
Zoals vrijwel altijd bij rtos taken implementeer je die door middel van een oneindige loop binnen de
functie main(). Aan het begin van die functie zijn enkele variabelen gedeclareerd die dienen om
tijdelijk de uit de channel gelezen waarde in op te slaan.
Dit is nog de implementatie van de toestand Noodtoestand:
case NOODTOESTAND:
// entry event
display.showMessage("Emergency");
// overige events
auto evt = wait(bnPressChannel,bnReleaseChannel,logTimer);
if(evt==logTimer)
{
remoteDatabase.log(trilFrequentie.getTrilFrequentie());
}
else if(evt==bnReleaseChannelChannel)
{
bnReleaseID=bnReleaseChannel.read();
if(bnReleaseID==NoodKnopID)
{
state=NORMAAL;
}
else
{
state=NOODTOESTAND;
}
}
else // evt == bnPressChannel
{
// remove the content from the channel.
dummID=bnPressChannelChannel.read();
}
default: break;
Ontwerp van het STD van TrilControl
We beginnen met het ontwerp van de STD interface
Ontwerp van de STD interface
We beginnen met een blik op onze klasse in het klassediagram:
Er zijn welgeteld twee publieke functies: buttonPressed en buttonReleased. Dat worden dus de
functies van de STD interface. In beide gevallen wordt er een parameter meegegeven. Nu moet er
een knoop worden doorgehakt over of we voor een flag met pool of voor een channel kiezen om de
nieuw binnengekomen waarde mee te bufferen. De overweging is hier hetzelfde als bij InstelControl:
Als de noodKnop wordt ingedrukt, willen we dat absoluut niet missen doordat bijvoorbeeld de
trilknop net erna is ingedrukt. Je zou dat kunnen borgen door aan de Button een IsButtonPressed
functie toe te voegen die altijd gepollt kan worden. Je kunt het ook borgen door alle binnenkomende
buttonPresses te bufferen in een channel.
Werken met events heeft in het algemeen de voorkeur boven pollen, dus ik kies ervoor om ook de
noodKnop via events af te handelen. Om dat veilig te kunnen doen, kies ik voor het gebruik van een
channel.
De STD interface van TrilControl komt er dus hetzelfde uit te zien als die van InstelControl:
Actiereeks van TrilControl in woorden
Wat TrilControl moet doen, staat beschreven in de beschrijving van de use case Trillen.
Het trillen bestaat uit het wachten tot een halve trilperiode voorbij is. De duur van een trilperiode is
1 gedeeld door de trilfrequentie. Voorbeeld: als de trilfrequentie 100Hz (Hertz) is, dat wil zeggen: 100
trillingen per seconde, dan duurt een complete trilling 1/100 seconde. Binnen die tijd is de
electromagneet aan en weer uit gezet. Tussen het aan en uit zetten zit dan dus de helft van 1/100
seconde.
Met het indrukken van de trilknop kan dat trillen getoggeld worden.
Er blijkt een uitzonderingssituatie te zijn:
Na indrukken van de noodknop moet het trillen stoppen, en wordt er niet meer naar de trilknop
geluisterd. Na intrekken van de noodknop mag de normale use case weer hervat worden.
Hetzelfde verhaal, maar nu met toestanden, events en acties er aan toegevoegd.
Wat TrilControl moet doen, staat beschreven in de beschrijving van de use case Trillen.
Het trillen bestaat uit het wachten tot een halve trilperiode voorbij is. De duur van een trilperiode is
1 gedeeld door de trilfrequentie. Voorbeeld: als de trilfrequentie 100Hz (Hertz) is, dat wil zeggen: 100
trillingen per seconde, dan duurt een complete trilling 1/100 seconde. Binnen die tijd is de
electromagneet aan en weer uit gezet. Tussen het aan en uit zetten zit dan dus de helft van 1/100
seconde.
Met het indrukken van de trilknop kan dat trillen getoggeld worden.
Er blijkt een uitzonderingssituatie te zijn:
Na indrukken van de noodknop moet het trillen stoppen, en wordt er niet meer naar de trilknop
geluisterd. Na intrekken van de noodknop mag de normale use case weer hervat worden.
De normale use case wacht dus op het indrukken van een button. Dat wordt gedaan vanuit een
toestand die ik maar “Normaal” noem.
Is het de noodKnop, dan moet naar de NoodToestand gegaan worden.
Is het de trilKnop, dan moet het trillen getoggeld worden. De toestand Normaal heeft dus twee
subtoestanden, die ik maar Trillen en NietTrillen noem.
De toestand Trillen zou je ook weer twee subtoestanden kunnen geven: ElectromagneetAan en
ElectromagneetUit. In totaal kom je dan om 3 toestand‐nestings‐levels. Dat is misschien weer wat
overkill in onze effort om het gedrag duidelijk te modelleren.
In plaats daarvan kies ik ervoor om de toestand trillen geen subtoestanden te geven. Na het
verstrijken van de periodetijd wordt als actie een boolean bMagneetAan getoggeld, en wordt
overeenkomstig electromagneet.zetAan() of electromagneet.zetUit() aangeroepen.
De extra laag van toestanden is dan dus gerealiseerd door middel van een boolean.
In de noodtoestand zijn we alleen geinteresseerd in de inhoud van de bnReleaseChannel.
Toch moet daar ook de bnPressChannel gelezen worden, zodat die niet vol met oude rommel staat
wanneer we weer naar de toestand Normaal gaan.
Omgekeerd geldt dat wel in toestand Normaal alleen geinteresseerd zijn in de inhoud van
bnPressChannel. Toch moet daar ook de bnReleaseChannel gelezen worden, zodat die niet vol met
oude rommel staat wanneer we weer naar de toestand NoodToestand gaan.
Het STD van TrilControl
Na verwerking van het bovenstaande ontstaat dus het volgende STD van TrilControl
NB:
 Het “after”/timer event waarmee de toestand Trillen kan worden verlaten impliceert een
entry event bij Trillen waarbij zijn wachttijd wordt gezet.
 De toestand Trillen wacht op drie events: dat timer event en twee channel read events.
Omdat er op meerdere dingen tegelijk gewacht wordt, moet er voor “after” een apart timer
object worden aangemaakt, waar dus ook binnen een wait(..+..+..) gewacht kan worden.
Van STD naar Code
Het omzetten van een STD naar Code gaat vrij rechttoe rechtaan:
1. Creeer een klasse die is afgeleid van rtos::task
2. Creeer een enum waarmee de toestanden geduid kunnen worden.
3. Voeg de member variabelen en references toe zoals aangegeven in het klassediagram.
(normaliter zijn die private).
1. Voeg een constructor toe die:
a. De reference members initialiseert.
b. Als de klasse een listener is, laat het eigen object zich als listenere toevoegen aan de
objecten waar het naar luistert.
c. Voeg de members die een Handler nodig hebben toe aan de betreffende Handler.
1. Maak voor elke STD interface een gelijknamige publieke functie aan. De code kun je 1 op 1
overnemen.
1. Implementeer de main() functie:
a. Creeer een switch statement dat springt naar de code voor de huidige toestand.
b. Voer daar als eerste de entry event code uit.
c. Vervolgens eventuele “do” code.
d. Wacht op het optreden van events:
auto evt = wait( een of meer waitables hier )
e. Interpreteer de event, en laat de bijbehorende guard, actie en/of transitie uitvoeren:
if(evt=flagButton){state = Idle;}
Van STD naar code van TrilControl
De eerste 5 stappen zijn vrij rechttoe rechtaan en leiden tot de volgende code:
#include "hwlib.hpp"
#include "rtos.hpp"
// Onderstaande enum wordt zowel door TrilControl en InstelControl
// Gebruikt. Hij moet dus in een aparte header file staan die door
// beide wordt geinclude. Voor het overzicht zet ik het toch even
// erbij, hier.
enum eButtonID = {MinKnopID,PlusKnopID,TrilKnopID,NoodKnopID};
class TrilControl : public rtos::task<>{
enum state_t = {NORMAAL, NOODTOESTAND};
enum substateNormaal_t = {NIET_TRILLEN,TRILLEN};
private:
state_t state = NORMAAL;
substateNormaal_t substateNormaal = NIET_TRILLEN;
rtos::channel bnPressChannel;
rtos::channel bnReleaseChannel;
Trilfrequentie& trilFrequentie;
Button& noodKnop;
Button trilKnop;
Electromagneet electromagneet;
rtos::timer trilTimer;
bool bMagneetEnabled = false;
InstelControl(Trilfrequentie& trilFrequentie, Button& noodKnop,
ButtonHandler& buttonHandler):
trilFrequentie(trilFrequentie),noodKnop(noodKnop)
{
// Meld objecten die door een handler aangezwengeld worden
// aan bij de betreffende handler.
buttonHandler.addButton(&trilKnop);
buttonHandler.addButton(&noodKnop);
// Aanname hierbij: de handler negeert
// herhaaldelijk aanmelden van dezelfde knop.
// Meld mezelf als ButtonListener aan bij de buttons waar ik
// naar luister.
trilKnop.addButtonListener(this);
noodKnop.addButtonListener(this);
}
public:
void buttonPressed(eButtonID buttonID)
{bnPressChannel.write(buttonID);}
void buttonReleased(eButtonID buttonID)
{bnReleaseChannel.write(buttonID);}
Ook de vervolgstap, de uitwerking van de STD in code is ook rechttoe, rechtaan. Dit is de
implementatie van de toestand Normaal, NietTrillen:
private:
void main(){
eButtonID bnID;
eButtonID bnReleaseID;
eButtonID dummID;
for(;;){
switch(state)
{
case NORMAAL:
switch(substateNormaal)
{
case NIET_TRILLEN:
auto evt = wait(bnReleaseChannel,
bnPressChannel);
if(evt==bnPressChannel)
{
bnID = bnPressChannel.read();
if(nbID==NoodKnopID)
{
state = NOODTOESTAND;
}
else // bnID moet TrilKnopID zijn
{
substateNormaal = TRILLEN;
}
}
else // empty the releasechannel
{
dummID = bnReleaseChannel.read();
}
break;
Dan Normaal, Trillen:
case TRILLEN:
// Er is een "after" event. Dat impliceert dat
// deze toestand een entry event heeft waarbij de
// timer wordt gestart.
// De ingestelde tijd gaat maal een miljoen, om
// seconden om te zetten naar microseconden.
trilTimer.start
(1/trilFrequentie.getTrilfrequentie/2*1000000);
auto evt = wait(bnReleaseChannel,bnPressChannel,trilTimer);
if(evt==bnPressChannel)
{
bnID = bnPressChannel.read();
if(nbID==NoodKnopID)
{
state = NOODTOESTAND;
}
else // bnID moet TrilKnopID zijn
{
substateNormaal = TRILLEN;
}
}
else if(evt==bnReleaseChannel)
{
// maak bnReleaseChannel leeg.
dummID = bnReleaseChannel.read();
}
else // De timer heeft gevuurd.
{
bMagneetEnabled = !bMagneetEnabled;
if(bMagneetEnabled)
{
electromagneet.zetAan();
}
else
{
electromagneet.zetUit();
}
}
break;
default: break;
En tot slot, de NoodToestand:
case NOODTOESTAND:
auto evt = wait(bnReleaseChannel,bnPressChannel);
if(evt==bnReleaseChannel)
{
bnReleaseID = bnReleaseChannel.read();
if(bnReleaseID==NoodKnopID)
{
state = NORMAAL;
substateNormaal = NIET_TRILLEN;
}
else // bnID moet TrilKnopID zijn
{
state = NOODTOESTAND;
}
}
else // het is bnPressChannel.
{
// maak bnPressChannelChannel.
dummID = bnPressChannel.read();
}
default: break;
Enum prefixes
Omwille van overzicht is het in het bovenstaande niet gedaan, maar omwille van het voorkomen van
nameclashes is het een betere gewoonte om enum variabelenamen te prefixen met de enum type
naam.
STD naar Code bij meer geavanceerde varianten
Je hebt nu voorbeelden gezien voor het omzetten van STD naar code bij het Trilapparaat.
Er zijn echter situaties die extra aandacht vergen:
 Een entry event in een state die nested substates heeft.
 Een action bij de uitgaande pijl van een state die nested substates heeft.
 Een exit event in een state die nested substates heeft.
 Een event bij de uitgaande pijl van een state die nested substates heeft.
Een entry event in een state die nested substates heeft
Kijk bijvoorbeeld nog eens naar de huidige code van TrilControl:
for(;;)
{
switch(state)
{
case NORMAAL:
switch(substateNormaal)
{
case NIET_TRILLEN:
auto evt = wait(bnReleaseChannel,bnPressChannel);
if(evt==bnPressChannel)
{
bnID = bnPressChannel.read();
if(nbID==NoodKnopID)
{
state = NOODTOESTAND;
}
else // bnID moet TrilKnopID zijn
{
substateNormaal = TRILLEN;
}
Stel nu dat de onderste else case wordt uitgevoerd: substateNormaal wordt gezet op TRILLEN.
Dan is de case afgehandeld, en komen we weer terug bij het begin van de for(;;) loop, bij het
bovenste switch statement. Aangezien de hoofdtoestand nog steeds NORMAAL is, gaat het
programma vervolgens CASE NORMAAL in.
So far, geen probleem. Maar wat als NORMAAL entry event code zou hebben gehad, waar zetten we
dat dan neer? Als we de entry event code simpelweg onder CASE NORMAAL: neerzetten, wordt die
code steeds opnieuw uitgevoerd als er een substate verandert (zoals in bovenstaand voorbeeld).
Maar entry event code van de state NORMAAL mag natuurlijk alleen uitgevoerd worden bij het
binnengaan van NORMAAL vanuit een andere (main‐) state.
Je zou in het algemeen dit op de volgende manier kunnen oplossen:
for(;;)
{
switch(state)
{
case NORMAAL:
if (prevState != NORMAAL)
{
// begin entry event stuff
// …
// end of entry event stuff
prevState = NORMAAL;
}
switch(substateNormaal)
{
case NIET_TRILLEN:
Een action bij de uitgaande pijl van een state die nested substates heeft, of een
exit‐event van een state die nested substates heeft
In het STD van TrilControl kun je zien dat er naast de uitgaande pijl van de toestand NORMAAL geen
event staat, en ook geen actions. Stel nu dat er een action zou hebben gestaan, dan zou die action
uitgevoerd moeten worden door elk van de substates op het event dat van hen naar de exit node
leidt. Hetzelfde geldt voor het geval dat de toestand NORMAAL exit event code had gehad. Ook die
zou moeten worden uitgevoerd door elk van de substates op het event dat van hen naar de exit
node leidt.
Een event bij de uitgaande pijl van een state die nested substates heeft.
In het STD van TrilControl is ervoor gekozen om de toestand NORMAAL te verlaten via een exit‐node,
in combinatie met een uitgaande pijl zonder event.
Alternatief had ervoor gekozen kunnen worden om de toestand NORMAAL te verlaten via een pijl
naar Noodtoestand met naast die pijl een event “noodButtonPressedFlag” waarop wordt gewacht.
Je kunt niet wait(noodButtonPressedFlag) onder case NORMAAL: zetten, omdat dan alle substates
eronder worden geblokkeerd. De oplossing is elk van de substates (ook) op noodButtonPressedFlag
te laten wachten.
Concurrency Diagram (dit hoofstuk/onderwerp vervalt/mag je skippen vanaf 2021)
Het concurrency diagram geeft weer via welke synchronisatiemechanismen te taken met elkaar
communiceren.
Ik heb er in dit document voor gekozen om de keuze van de synchronisatiemechanismen te bepalen
op het moment dat de interface voor de std moet worden ontworpen. In dit geval kan het
concurrencydiagram dus helemaal achteraf worden getekend en is het niet nodig geweest tijdens het
design proces.
Taken en synchronisatiemechanismen
Zo maak je een concurrency diagram:
1. Noteer de namen van de taken die uit de taakstructurering+taaksamenvoeging kwamen in
parallellogram‐vormen.
1. Kijk in het klassediagram welke functies van een taak door een andere taak worden
aangeroepen. Bedenk voor die functies welke syncronisatiemechanismen het best gekozen
kunnen worden.
In het voorgaande hadden we al gezien hoe je dat doet:
o Functies die “even snel” een waarde opvragen:
Bijvoorbeeld getTemperature() en isTemperatureTooHigh().
Die functies implementeer je door een pool waarde te retourneren.
o Overige functies – in het algemeen functies die een bericht doorgeven of expliciet
opdracht geven om iets te gaan doen. Die functies kun je ook weer in twee
categorien verdelen:
 Functies zonder argument
Functies zonder argument, zoals bijvoorbeeld zetAan() implementeer je door
een flag te zetten.
 Functies met argument
 Als alleen de binnengekomen waarde ertoe doet
Als alleen de laatst binnengekomen waarde ertoe doet,
implementeer je zo’n functie met een pool en een flag. De waarde
wordt in de pool geschreven en de flag wordt gezet om te signaleren
dat er een nieuwe, nog niet verwerkte waarde is.
 Als het belangrijk is dat je geen voorgaande waarde misloopt
Als het belangrijk is dat je geen voorgaande waarde misloopt, kun je
in plaats van een flag+pool combinatie zoals hierboven beter kiezen
voor een channel.
1. Ga na welke klassen op een timer wachten, en voeg dat toe aan het diagram.
2. Ga na of er entity klassen zijn die vanuit verschillende taken gelezen en geschreven kunnen
worden.
Ga na wie de setters en getters van de betreffende entity aanroepen. De betreffende data
moet geencapsuleerd zijn in in pools.
That’s all. Alleen even opletten op de volgende valkuil:
 Op een waitable (flag, timer, channel) mag alleen gewacht worden door die ene taak die hem
bezit.
 Alle pijlen wijzen naar de synchronisatie‐elementen toe (dus niet met de informatiestroom
mee, wat je intuitief misschien zou doen).
Concurrency Diagram voor het Trilapparaat
Stap 1: parallellogrammen tekenen
Dit was het resultaat van de taaksamenvoeging:
Taak Objecten Taaksoort Periode Deadline Prioriteit
InstelTaak InstelControl Intern, Demand
Driven
30ms 1
TrilTaak TrilControl Intern, Demand
Driven
30ms 1
Trilfequentie Geen
DisplayTaak Display IO, Demand Driven 200ms 3
ButtonTaak ButtonHandler,
PlusKnop, MinKnop,
NoodKnop,
TrilKnop
IO, Periodical 60ms 60ms 2
DatabaseTaak RemoteDatabase IO, Demand Driven 3 minuten 4
De taken beelden we af in parallellogrammen:
Stap 2: Aangeven via welke synchronisatie elementen de taken met elkaar praten
Kijk in het klassediagram welke functies van een taak door een andere taak worden aangeroepen.
We gaan dus de functies langs welke behoren tot klassen met het <<isActive>> stereotype.
Bedenk voor die functies welke syncronisatiemechanismen het best gekozen kunnen worden.
Voor het gemak is het klassediagram onderstaand nog eens weergegeven:
We bekijken het klasse voor klasse.
Voor InstelControl en TrilControl hadden we al STD‐interfaces gemaakt. Daar kunnen we de
synchronisatie‐elementen dus uit overnemen:
InstelControl
 InstelControl heeft twee publieke interface functies.
Wacht op twee channels: bnPressedChannel en bnReleasedChannel.
 Die channels worden geschreven door de aanroeper van de publieke interface functies. Dat
is in dit geval de Button. De Button is samengevoegd met de taak van de ButtonHandler (de
ButtonHandler roept de update() van Button aan, en die roept eventueel weer
buttonPressed of buttonReleased aan).
Kortom, de channels worden vanuit de ButtonTaak geschreven.
Verwerken we dit, dan krijgen we dus:
TrilControl
 TrilControl heeft dezelfde twee publieke interface functies als InstelControl.
Het wacht daar in ook op twee channels: bnPressedChannel en bnReleasedChannel.
 Die channels worden dus weer vanuit de ButtonTaak geschreven.
Verwerken we dat, dan krijgen we dus:
RemoteDatabase
 RemoteDatabase heeft de publieke interface functie log(jsonData:str). Die wordt
aangeroepen door InstelControl.
Ik besluit nu even dat een string in json formaat handig is om naar een database te sturen.
Even opnieuw screenshots maken van al die klassediagrammen :‐).
 Het is een klassiek geval van een functie met een argument, waarbij je niet wil dat er data
van voorgaande aanroepen verloren kan gaan.
Kortom: ook hier gebruiken we een channel om de strings met json data in te bufferen. Die
channel noem ik even jsonDataChannel.
De DatabaseTaak luistert dus naar jsonDataChannel, welke wordt gevuld door de InstelTaak.
Verwerken we dit, dan wordt het:
Display
 Display heeft de publieke interface functie showMessage(str:string). Die wordt aangeroepen
door InstelControl.
 In dit geval zijn we alleen geinteresseerd in de laatste message. Het is dus een klassiek geval
van een flag met een pool. De flag noem ik messageFlag. De pool noem ik messagePool.
 De DisplayTaak luistert dus naar messageFlag, en leest uit messagePool. Die worden geset
respectievelijk geschreven door de InstelTaak.
Verwerken we dat, dan wordt het:
ButtonHandler – een vreemde eend!
 De ButtonHandler heeft de publieke interface functie addButton(bn:Button*).
Die wordt aangeroepen door de constructor InstelControl en de constructor van TrilControl.
In de constructie fase lopen de taken nog niet. De constructors worden aangeroepen door de
main thread van het programma. Er is dan ook geen sprake van inter‐taak communicatie.
Er vanuit gaande dat addButton niet on the fly, maar alleen in de constructie‐fase wordt
aangeroepen (voor embedded systems is dat een veilige aanname), is het dus niet nodig of
wenselijk om de functie addButton via synchronisatieelementen te laten werken.
De functie mag direct in de aanroepende main thread worden afgehandeld.
Bon, we hebben nu de functies van alle <<isActive>> klassen nagelopen.
Tijd voor de stap 3:
Stap 3: Ga na welke klassen op een timer wachten, en voeg dat toe aan het
diagram.
 Zie code van InstelControl: Er wordt een timer genaamd logTimer gebruikt.
 Zie code van TrilControl: Er wordt een timer genaamd trilTimer gebruikt.
 ButtonHandler: De buttonhandler is een periodieke taak. Intern gebruikt hij dus een timer
die periodiek afgaat. Buttonhandler wacht alleen op die periodieke timer. Het kan dus een
naamloze timer zijn, waarvoor geen apart object wordt aangemaakt.
Na het toevoegen van deze 3 timers wordt het:
Stap 4: Entity Klassen
Ga na of er entity klassen zijn die vanuit verschillende taken gelezen en geschreven kunnen worden.
Ga na wie de setters en getters van de betreffende entity aanroepen. De betreffende data moet
geencapsuleerd zijn in in pools.
In ons trilapparaat bevindt zich slechts een entity klasse, genaamd TrilFrequentie. De data die zich er
in bevindt wordt door de InstelTaak geschreven en gelezen. De Triltaak leest de data. Omdat de data
in de entity klasse door de ene taak kan worden geschreven, en door de andere kan worden gelezen,
moet die data beschermd worden dmv pools.
De enige data die zich in TrilFrequentie bevindt, is een integer getal, welke dus moet worden
geencapsuleerd door een pool. De pool noem ik trilFrequentiePool.
Na toevoegen van de pool is het concurrency diagram compleet:
Mooi! Je hebt nu een prachtig overzicht van hoe de taken met elkaar communiceren.
Zonder dit overzicht is die informatie alleen overal verspreid te vinden: in de interfaces, in de stds, in
het klassediagram.
Wrapup
Je hebt het eind van dit lijvige, maar hopelijk toch relatief licht lezende document gehaald!
Kudos for you!
Je hebt daarbij getuige geweest van alle stappen van een ontwerp van kop tot staart:
1. Object model met object beschrijvingen
2. Taakstructurering
3. Klassediagram
4. Stds
5. Code
6. Concurrency Diagram
Een belangrijke volgende stap is oefenen, oefenen en nog eens oefenen. Het zijn steeds dezelfde,
eigenlijk wel logische stappen.
Als je het een beetje in de vingers hebt, kun je een ontwerp als dit in een stief ochtendje van
requirements naar code + goede documentatie brengen.