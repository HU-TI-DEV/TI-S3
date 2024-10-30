# Log sGxWorks2

[mitsubishi electric]

Eerst inloggen met account op mijn mitsubishi electric, met:

XXX
(Die link blijkt niet meer te werken, maar ik heb onderstaand een link naar de zip op Teams Files gezet:
[GX Works3 1.101F EU.zip](https://hogeschoolutrecht.sharepoint.com/:u:/r/sites/int_Onderwijs_ti-s3-24h1/Gedeelde%20documenten/General/GX%20Works3%201.101F%20EU.zip?csf=1&web=1&e=8QSewI)
. NB: je hebt GxWorks 2 nodig, maar dat kun je installeren vanuit deze GxWorks3 installer)

Vervolgens geavanceerd zoeken. Checkbox engels.
In de lijst staat de volgende zip erbij:
(onderstaande link wijst naar de Canvas Teams Files van TI-S3-24H1 - het is ruim 3GB)

Ik download het. Kopieer het in een tmp folder op D:, extract all,
open command prompt als administrator, run de installer vanaf daar.

Bij User Information type ik:
Naam: Marius Versteegen
Company: Hogeschool Utrecht
Product ID: 752-357853260
(Dat is denk ik de id voor onbeperkt gebruik)

Bij de checkboxes heb ik voor de zekerheid alles aangevinkt om te installeren.

Tijdens het installeren:
![](img/2024-04-19-15-22-56-image.png)

Enfin, ik klikte maar op OK. Hopelijk is dat niet te erg..

De iQ-R Ethernet/IP Configuration Tool en FX5 Ethernet/IP Configuration Tool heb ik niet geinstalleerd, gezien het feit dat we FX-2N (clones) gebruiken.

Pc herstarten (volgens aanbeveling..)

## Onze PLC: FX2N - kloon : WS2N-6MT-S met 2 ADC inputs

Het is dus geen FX2N, maar een kloon. FX2N heeft volgens chatgpt geen pwm output en AD inputs. Wel een aparte module, genaamd FX2N-2AD.
Misschien gedraagt de WS2N-6MT-S zich als een combinatie van FX2N met die module?

## WS2N-6MT-S Van binnen

Even opengeschroefd. Er zijn twee vermogenstransistoren te zien. 
Ze zijn van het type MJD122. Dat is een op NPN gebaseerde darlington.
VCE max = 100VDC
Ic max, continuous = 8A DC (wow)
Thermal resistance, Junction to case = 6 graden per Watt
Uit de IB vs VCE grafiek leidt ik af dat de Ron weerstand 1.5 ohm is.
Maar bij een minimale schakelstroom zal VCE nog steeds minimaal 0.7V zijn, als gevolg van de manier waarop de darlington opgebouwd is.

Aangezien de originele FX2N niet meer gemaakt wordt, en het een kloon moet zijn, ben ik benieuwd naar welke chip gebruikt wordt. Misschien een of andere cheapo microcontroller? Even de kwaliteitssticker eraf pulken en de lijmresten verwijderen met stickerverwijderaar. Helaas (b)lijkt de naam van de chip eraf gefreesd te zijn.

## WS2N gebruiken

### Aansluiten

De WS2N kun je bevestigen met DIN-rail. Dat kun je o.a. bij de bouwmarkt kopen.

De versie die ik heb, heeft de volgende aansluitingen:
+24V, 0V, X3, X2, X1 en X0 aan de onderkant en
(voedingsspanning en 4 logische input pinnen)
Y1, CM1, Y0, CM0 aan de bovenkant.
(het contact tussen Y1 en CM1 kan worden "geschakeld".
 dat kan met relais of transistor. als Harm heeft besteld wat ik suggereerde, moet deze met transistor werken. Ik vermoed van P-type (om active hoog te kunnen zijn) CM0 en CM1 fungeren als de grounds voor Y0 en Y1. Ze zijn alleen typisch niet standaard met elkaar verbonden - je kunt elk als ground laten dienen voor een aparte uitgangsgroep)
Aan de zijkant zie ik twee "bussen" van 4 pinnen elk:
gnd, tx, rx, 5v  
(voor connectie met de FDTI USB naar serial interface)
en 
gnd, pwm, ad1, ad0
(dus pwm output resp adc inputs)

## Specs

Die zijn te vinden op:
```https://www.winsunzk.cn/en/product?mode=0&type=4```
en daarop:
```https://www.winsunzk.cn/en/pdetail/62aafcbfad6b0117cddfab99```

| Item                   | Spec                  |
| ---------------------- | --------------------- |
| voedingsspanning       | 12-24V DC             |
| Load                   | 24 V                  |
| aantal AD inputs       | 2                     |
| AD input range         | 0-10V                 |
| Aantal logische inputs | 4                     |
| Logic input levels     | 0-5V = 0, erboven = 1 |
| Uitgangsstroom         | 1A                    |
| High speed counting    | 2 kanalen 3KHZ        |
| Pulsuitgang            | 2 kanalen 3KHZ        |
| Instructiecapaciteit   | 4000 stappen          |
| Downloadsnelheid       | 9600 baud             |
| Download port          | TTL                   |
| Programming software   | GxWorks 2             |
| Stappenmotor           | Supported             |
| Servomotor             | Not supported         |

Helaas hebben wiring diagram en code uitleg broken links, en staat er bij de "related downloads" alleen een manual van een andere plc (een Siemens S7 kloon).
Er is ook een FX2N manual:

```
https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjxhtnY89CFAxVr7rsIHVkkCTEQFnoECBUQAQ&url=https%3A%2F%2Fdocs.rs-online.com%2Fc981%2F0900766b8046ac4c.pdf&usg=AOvVaw3Nsupqi8AifFp39mflD1pu&opi=89978449
```
NB (achteraf hier toegevoegd): verderop ontdekte ik dat er ook een Programmers Manual bestaat voor de FX2N serie. Die bleek het nuttigs te zijn. 
Beide manuals zijn ook te vinden in deze repo:
- [FX2N Programming Manual](./FX2N%20Programming%20Manual.pdf)
- [FX2N User Manual](./FX2N_user_manual.pdf)  
Verder is dit een aardige algemene introductie voor ladder e.d.: 
- [Link naar tutorial](https://iaprofessionals.nl/basiskennis/programmeren-van-een-plc/#LadderDiagram)   

Deze FX2N manual rept over een benodigde ingangsstroom van tenminste 7mA om een ingang (voldoende) omhoog te trekken. Kortom, kennelijk is er een vrij lage ingebouwde pulldown-weerstand aanwezig. Geen idee of dat voor de WS2N ook nodig is. Proberen maar straks. Update: nope: zonder een externe pulldown van 10k op X0 ging het bijbehorende ledje op de PLC niet branden.

Verder suggereert die manual dat soms de N type transistor als als emittervolger is geschakeld in dat geval heten de contacten "V0 Y0" en "V1 Y1", waarbij V0 en V1 met de voedingsspanning van de load verbonden worden. Bij onze PLC heten de contacten echter "Com0 Y0" en "Com1 Y1". In dat geval is de N type transistor een traditionele "Schakelaar op de ground". Onze kloon gebruikt ook de laatstgenoemde benamingen.

Ha, hier is nog een manual van de FX2N serie. Die laat mooi de beschikbare instructies als IL code en ladder zien:

```https://docs.rs-online.com/d13f/0900766b8002b6e2.pdf```

![](img/2024-04-21-14-21-19-image.png)

Verder lijkt dit een nuttige tutorial serie:
```https://www.youtube.com/watch?v=Zc1Cc3IbRew&list=PLAsa6d7WgobHwxCI1CDZBlgzNRL5INUhy&index=1```
Het is in onverstaanbaar filippino maar uitstekend ondertiteld.

### Gxworks2 Project Starten

Leuk, je kunt voor de FX2N/FX2NC kiezen tussen Simple en Structured mode. Verder uit de talen ladder, ST (structured Text), IL (Instruction List) en SFC (grafisch blokschema). Structured text lijkt eenvoudig en overzichtelijk in het gebruik.
IL doet meer denken aan assembly notatie. Minder overzichtelijk. Ladder ziet er ook overzichtelijk uit. SFC ziet er omslachtig en onduidelijk uit.

Ah, er zijn shortcut keys:
<img title="" src="img/2024-04-19-16-17-00-image.png" alt="" width="454">
ik kies yes

<img src="img/2024-04-19-16-20-15-image.png" title="" alt="" width="453">
ik kies no

Eerst maar eens ladder - want daar is ook een youtube demo van, dacht ik.

## Ladder - Hello world

Ik heb eerst maar eens de plc aangesloten op een schakelaar met 10k pulldown weerstand die X0 op 24V kan zetten.
Verder op Y0 een 10k weerstand, verbonden met de kathode van een led. De anode van de led verbonden met 24V.
De powerlines van de PLC ook op 24V ingesteld. De maximale stroom van de labvoeding even gelimiteerd op 4A.

GxWorks2 shortcut keys:

| Functie                | Key |
| ---------------------- | --- |
| write mode             | F2  |
| compileren             | F4  |
| open contact           | F5  |
| gesloten contact       | F6  |
| uitgang ()             | F7  |
| speciale instructie [] | F8  |

Okee, connectie ingesteld op de juiste comport, op 9600 baud, RS232.
Een ladder gemaakt die de input op de output overzet.

**Online Data Operation winodow geopend**

| Optie  | Beschrijving                               |
| ------ | ------------------------------------------ |
| Read   | leest data van PLC naar project            |
| Write  | schrijft data van project naar PLC         |
| Verify | vergelijkt data op PLC met data in project |

Middels checkboxen kun je aangeven wat je wilt lezen, schrijven of vergelijken.

In mijn geval is alleen het programma van belang.
In principe kun je bij het uploaden de volgende foutmelding krijgen:
<img src="img/2024-04-20-17-07-27-image.png" title="" alt="" width="343">

In dat geval moet je op de "stop knop" op de plc drukken.
Deze PLC heeft niet zo'n knop. Dus laten we hopen dat programmeren veilig is?
Voor onze PLC zou je denk ik het beste de power-line van de uitgangen (tbv motoren e.d.) kunnen losschakelen tijdens het programmeren.

Na het programmeren vraagt GxWorks2 of een "remote run" / starten van de cpu gedaan moet worden -> yes.
Het 'run' ledje op de PLC licht nu op. (Project: "TestLadder")

Het ladderprogramma lijkt echter niet te werken: Als ik op de input-schakelaar klik, zie ik weliswaar nog altijd op de PLC het bijbehorende input ledje uitgaan. De waarde van Y0 zie ik echter niet veranderen.

Wat blijkt: een 10k pulldown is weliswaar genoeg om het ledje van X0 aan te zetten. Het is niet genoeg om X0 laag genoeg te trekken voor de cpu. Die 7mA minimale input stroom is kennelijk echt een dingetje. Na vervangen van de 10k pulldown door een 2.2k pulldown werkte het. Het blijkt dat de plc ook een ledje per output heeft, en dus aangeeft welke output geactiveerd is. Bij deze PLC geldt dat als het ledje voor Y0 brandt, dat dan de darlington schakelaar aan de ground zijde geactiveerd wordt en de output laag wordt. 

### Remote RUN en STOP

Meestal vraagt hij niet de vraag of hij na het uploaden moet runnen.
In dat geval: dubbelklik op het remote operation icon linksonder in het Online Data Operation menu. Nu kun je handmatig starten of stoppen.

### TestLadder2

Nu maak ik een nieuw ladder testje. dit keer vink ik bij de project-creatie optie de checkbox "use label" aan.

Nu zie ik naast de tab met het laddernetwerk ook een tab voor local label settings. Kennelijk kan ik daar variabelen en constanten declareren, van de types Bit, Signed Word, Signed Double Word, FLOAT, Timer, Counter, Retentive Timer en Pointer.

Dat zijn denk ik locale variabelen, die steeds als je "functie" begint weer op 0 gezet worden.
Je kunt ook (links via de project tree) globale variabelen aanmaken.

Van al die typen behalve Pointer kun je ook een ARRAY declareren.

Retentive timers zijn timers die hun waarde onthouden als je de PLC uitschakelt.

Wat blijkt: doordat "use label" aanstaat, wordt elke keer dat je in de ladder een logische bouwsteen toevoegt gevraagd een label in te vullen. Als je dat niet doet, wordt geprompt om er een aan te maken (een variabele van het type Bit, by default). Het voordeel is dat elke waarde in het circuit zo een naam krijgt.

Onderstaande zie je een aantal ladder-operaties met functietoets erbij (gekopieerd uit de GxWorks2 Beginners manual):

![](img/2024-04-21-10-42-17-image.png)

Een device kan zijn: een ingang (X0), een uitgang (Y0), een timer (T0), of een variabele - dacht ik.

Normally open betekent dat je het met een "1" op bijvoorbeeld X0 kunt sluiten: de output wordt dan 1.

In Mnemonics: LD X0
Normally closed is de geinverteerde versie daarvan.
Je kunt ook een 1 genereren als een input van 0 naar 1 gaat.

Met de [insert] toets kun je toggelen tussen overwrite en insert mode.

Als je op een nieuwe regel Open Branch toevoegt, maakt hij daar een open contact aan die parallel komt te staan aan de eerste operatie van de regel erboven.

Door een vertical line ergens op een regel toe te voegen, maak je daar een aftakking naar een volgende regel.

Ik probeer de GxWorks2 Beginnners manual te volgen, maar het toevoegen van de application instruction "MOVP K20 VAR1"  lukt niet: MOVP staat niet als optie bij de instructies (ik gebruik een FX2N, itt de manual). Als het had gewerkt, had het de waarde 20 in de variabele VAR1 geschreven.

Met de instructie T0 K10 zet je de timer op een constante waarde (van 10 * 0.1sec=1seconde). De kortste tijd die je dus kunt instellen lijkt 0.1sec.

Ik bouwde onderstaande schema:
![](img/2024-04-21-16-27-58-image.png)

Knop X0 is met pull-down aangesloten.
De leds hangen aan een kant aan de 24V, met de andere kant via 10k weerstand aan de uitgang.
De rustsituatie is:

* De uitgangsspanningen zijn hoog, de led aan Y0 staat uit.
  De Y0-led op de PLC zelf staat ook uit.

* De X0-led op de PLC zelf staat aan.

Vervolgens: als ik de knop indruk gebeurt er niets, maar als ik hem weer loslaat brandt de led 10 seconden en gaat dan weer uit.

Mijn interpretatie: De ingangen zijn **active low**. De schakeling reageert immers op neergaande ipv opgaande flank van de ingang.

Met andere woorden: X0 in de ladder = logische 1 als de spanning op de bijbehorende pin laag is. Voor de uitgangen geldt hetzelfde:
Y0 = logische 1 betekent dat de darlington is ingeschakeld en de bijbehorende pin laag trekt.

Hoe timer T0 werkt, begrijp ik nog steeds niet. Zonder de feedback van Y000 naar zijn eigen ingang werkt het niet. Volgens chatgpt telt de timer tot het gespecificeerde K getal. Daarna zou het moeten activeren.

Deze ladder doet bijvoorbeeld helemaal niets (leds altijd uit):
![](img/2024-04-21-18-16-13-image.png)

Gelukkig kun je ook het gedrag real-time monitoren.

Bij deze variant bleek duidelijk hoe de timer werkt:
![](img/2024-04-21-20-12-35-image.png)
Wat het doet: zolang je X0 logisch een maakt en houdt, verhoogt het getal bij "Timer T0". Eigenlijk is het dus geen timer, maar meer een counter, welke elke functieloop telt of de input 1 is. Je ziet dan dat hij telt tot de teller in T0 100 is geworden. Vanaf dan wordt de logische uitgang van T0 gelijk aan 1 (en brandt de led). Zodra X0 weer logisch 0 wordt, wordt de uitgang van T0 ook 0, en wordt ook zijn interne teller terug op 0 gezet.

## Structured Text

De volgende Structured Text blijkt hetzelfde gedrag te hebben als de ladder met  feedback van Y0, een eindje hierboven;

```
Y0:=(LDP(TRUE,X0) OR Y0) AND NOT (TS0);
OUT_T(Y0,TC0,10);
(* dit is commentaar *)
MOVP(X1,10,VAR1);
MOVP(X2,10,VAR1);
```

Het blijkt dat je tijdens het runnen van deze ST ook "monitoring" aan kunt zetten.
Dan zie je dat VAR1 op 10 wordt gezet als je X1 logisch een maakt.
Verder zie je in blauw alles oplichten dat 1 wordt.
Uitzondering: TS0 zie ik  op de een of andere manier nooit in blauw oplichten. Misschien gaat dat sneller dan de monitor kan bijhouden.

Geen idee wat het verschil is tussen TS0 en TC0.

Gelukkig is er een programming manual:   
```https://dl.mitsubishielectric.com/dl/fa/document/manual/plc_fx/jy992d48301/jy992d48301j.pdf```

Vermoedelijk staat TC0 voor "Timer/Counter" .
Vermoedelijk had ik T0 voor Timer kunnen gebruiken.
Counters kunnen 16bit of 32bit zijn.

## Interne stacks

Om een goed beeld te krijgen van hoe een en ander werkt, kun je volgens mij het best denken aan interne stacks:

![](img/2024-04-22-09-37-22-image.png)

LD X0    // stack.**push**(X0)
OR X1   // stack.top()=stack.top() OR X1
LD X2    // stack.**push**(X2)
AND X3 // stack.top()=stack.top() AND X3
LDI X4    // stack.**push**(!X4)
AND X4  // stack.top()=stack.top() AND X4
ORB        // stack.top()=stack.**pop**() OR stack.top()
OR X6     // stack.top()=stack.top() OR X6
ANB        // stack.top()=stack.**pop**() AND stack.top()
OR X3     // stack.top()=stack.top() OR X3
OUT Y7   // Y7 = stack.**pop**()

### Aparte stack voor MPS, MRD en MPP

![](img/2024-04-22-09-47-55-image.png)

voorbeeld:

![](img/2024-04-22-09-50-01-image.png)

LD X0   // stack.push(X0)
MPS     // Mstack.push(stack.top())
LD X1   // stack.push(X1)
OR X2   // stack.top()=stack.top() OR X2
ANB      // stack.top()=stack.pop() AND stack.top()
OUT Y0 // Y0 = stack.pop()
MRD      // stack.push(Mstack.top())
LD X3    // stack.push(X3)
AND X4 // stack.top()=stack.top() AND X4
LD X5    // stack.push(X5)
AND X6 // stack.top()=stack.top() AND X6
ORB       // stack.top()=stack.pop() OR stack.top()
ANB       // stack.top()=stack.pop() AND stack.top()
OUT Y1  // Y1=stack.pop()
MPP       // stack.push(Mstack.pop())
AND X7 // stack.top()=stack.top() AND X7
OUT Y2  // Y2 = stack.pop()
LD X10   // stack.push(X10)
OR X11  // stack.top()=stack.top() OR X11
ANB        // stack.top()=stack.pop() AND stack.top()
OUT Y3   // Y3 = stack.pop()

## (geneste-) functies

Het onderstaande voorbeeld llaat een functie zien:
![](img/2024-04-22-10-12-29-image.png)

LD X0                 // stack.push(X0)
MC N0 M100    // M100 = stack.pop(), depth N=0   (M100 kun je zien als functienaam)
                           // if !M100, jump to after MCR N0
LD X1                 // stack.push(X1)
OUT Y0              // Y0=stack.pop()
LD X2                 // stack.push(X2)
OUT Y1              // Y1=stack.pop()
MCR N0             // Label die einde van deze depth 0 functie markeert.

Het onderstaande voorbeeld laat geneste functies zien:

![](img/2024-04-22-10-11-36-image.png)

## Set/Reset (Flipflop) functionaliteit

Spreekt voor zich:

![](img/2024-04-22-11-26-12-image.png)

## Timers en Counters

Timers T en Counters C kun je zetten met ee OUT mnemonic.
Je kunt ze resetten met de RST mnemonic. Bijvoorbeeld RST C200 resets de counter met de naam C200.

Timers en counters kunnen basic en retentive zijn (dwz: waarde bewaren na uitzetten van de plc)

Er zijn voor sommige plc's ook "High speed counters" beschikbaar. Daarvoor zijn aparte symbolen (en ik denk ook pinnen op de plc).

## PLS (pulse) en PLF (pulse falling)

Als je een opgaande flank voert naar PLS, genereert die gedurende 1 "loop-execution" een 1, en daarna weer 0. PLF doet hetzelfde, maar dan op negatieve flank.

## INV

INV inverteert de logische toestand op zijn positie.

## NOP

No operation. Na 'Program Clear' bestaan alle instructies uit NOP instructies.

## END

De end operatie breakt de loop. Het tussenvoegen van een END commando kan handig zijn tijdens het debuggen.

# STL (STepLadder programming) subprogrammas

<img src="img/2024-04-24-08-41-50-image.png" title="" alt="" width="370">

Bovenstaand zie je een voorbeeld. Zodra de STL instructie ziet er uit als een dik getekend normally open  contact, in dit geval met de naam (State) S005. Als die geactiveerd is - kom je de verticale bar er rechts van. Die gedraagt zich hetzelfde als de verticale bar helemaal links van het hoofdprogramma: met rongs die een voor een uitgevoerd worden. Dus geen OR branching oid. De STL functie moet met RET worden afgesloten, zodat de functiecall kan retourneren naar de vertical bar een niveau hoger.
Vergeet je dat, dan ziet de compiler alles wat erna komt ook nog als onderdeel van de subbranch.

Je kunt STL functies dus ook in standaard ladder programma's toevoegen:
<img src="img/2024-04-24-08-54-03-image.png" title="" alt="" width="385">

De states 
kunnen geactiveerd worden zoals "coils" met PLS, OUT, SET.
Het is normaal gesproken echter aanbevolen om daar SET voor te gebruiken.
Zodra de STL instructie wordt bereikt, slaat de program counter rechtsaf, en wordt de State coil (in bovenstaande voorbeelden S005, resp S009) **automatisch** gereset.
(Als je geen SET gebruikte, kun je met RST of ZRST handmatig een state resetten)

Vergelijk met deze standaard case, zonder STL instructie, maar met gewoon open contact:
<img src="img/2024-04-24-09-24-01-image.png" title="" alt="" width="388">

Als S020 op FALSE wordt gezet, wordt S030 ook op false gezet.
Als daarentegen S020 een STL instructie was geweest, en S020 FALS zou zijn geSET, dan zou de subfunctie niet zijn uitgevoerd, en ook niet S030 hebben aangepast.

### SFC representatie, gebruik van OUT ipv SET

Je kunt de flow van states ook met een SFC diagram weergeven:

<img src="img/2024-04-24-09-32-53-image.png" title="" alt="" width="362">

Nu is de conventie dat je voor sequentiele en geneste states SET gebruikt voor het activeren van de states, maar voor **sprongen** (zowel voorwaarts of terug / in een loop) het **OUT** statement gebruikt.
(volgens de docs kan het theoretisch ook met SET, maar is OUT nodig om het in SFC format te kunnen weergeven)

Ook bij minder mooie, niet geneste program flows kun je OUT gebruiken om over te steken:
<img title="" src="img/2024-04-24-09-36-49-image.png" alt="" width="371">

### Dual coils

In normaal programmeren is het not done om dezelfde coil op verschillende plekken aan te passen. Alleen de laatste is dan effectief.

Maar het volstrekt okee om binnen verschillende STL states dezelfde coil aan te passen. Je moet dan alleen opletten dat je binnen een program "scan" (iteratie, loop) niet twee states uitvoert die dezelfde coil aanpassen.

#### Dual coil timers

Het is aanbevolen om niet dezelfde timer binnen twee opeenvolgende Steps/States aan te passen. Dat leidt tot incorrect gedrag, schijnt.

### Steps/States

Ik ben niet 100% zeker, maar zoals het er staat, (op blz3-7 van de programming manual) interpreteer ik het dat per "program scan". Steeds twee opeenvolgende states gelijktijdig actief zijn. Dus als je wilt voorkomen dat twee outputs tegelijk geset worden, kun je die outputs van twee states "interlocken":
<img title="" src="img/2024-04-24-11-46-19-image.png" alt="" width="243">

Een andere manier om maar 1 Step per scan uit te voeren is:
<img src="img/2024-04-24-11-50-33-image.png" title="" alt="" width="267">

### Special Single Pulse Flags

Op pg 3-9 staat ook iets onduidelijks. Kennelijk als je pulse contacten (LDP, LDF, ANP, etc) gebruikt met M devices in range M2800-M3071, dan wordt tijdens een scan alleen de eerste die wordt tegengekomen actief.

<img src="img/2024-04-24-12-01-06-image.png" title="" alt="" width="327">

Dus stel dat bovenstaand S50 actief is (dus de state variable S50 is op TRUE gezet).
Zodra de laddercode dan STL S50 bereikt, wordt die code uitgevoerd.
Na afloop wordt in dit geval M2800 gepulsed gemeten. Die detecteert dat in de ladder eerder de M2800 coil is geset, en activeert op basis daarvan State/Step S51.
Vanwege de speciale M2800-M3071 reeks wordt die pulse detectie dus direct "geconsumeerd", wat voorkomt dat de huidige scan na step S51 meteen doorloopt.

#### Control flow

Wat me niet helemaal duidelijk is, is of je nu wel of niet een geneste serie STL Steps binnen een enklele scan kunt doorlopen, of dat elke STL step een eigen scan in beslag neemt.

#### Beperkingen STL MC

Eerder zagen we al dat je ook met MC constructies kunt nesten.
Kennelijk kun je daar ook FOR-NEXT mee maken.
Beperkingen:

- FOR-NEXT kunnen geen STL blocks bevatten.

- Subroutines en interrupts kunnen dat ook niet.

- STL program blocks kunnen niet na een FEND instructie komen.

- FOR-NEXT instructies binnen een STL programma mag wel, maar maximaal 4 niveaus diep.

### Branchen en joinen

![](img/2024-04-24-12-26-11-image.png)

![](img/2024-04-24-12-26-23-image.png)

Een beetje gek.. Enfin. De eerste tak die klaar is en door mag, set S50 als eerste.

In plaats van te kiezen tussen branches kun je er ook meerdere parallel starten:

![](img/2024-04-24-13-20-12-image.png)

Vervolgens kun je op twee manieren weer mergen:

- "First State Merge": het gaat verder zodra het eerste van de 3 parallelle threads klaar is.

- "Multiple State Merge": een echte join: het gaat pas verder als alle 3 de parallelle threads klaar zijn.

Voorbeeld van "Multiple State Merge":
![](img/2024-04-24-13-23-24-image.png)

## Recommended rewrites (onbegrepen waarom)

![](img/2024-04-24-13-38-45-image.png)

![](img/2024-04-24-13-39-06-image.png)

### ZRST Zone Reset

Met ZRST kun je een reeks resetten. Voorbeeld: ZRST S21 S25 doet hetzelfde als RST S21, RST S22, RST S23, RST S24, RST S25.

## Voorbeeld

![](img/2024-04-24-13-39-59-image.png)

Waarom heeft alleen de laatste STL step een RET?

#### Ander voorbeeld

![](img/2024-04-24-14-08-53-image.png)

# "Devices"

## Input Devices: X

Die representeren de fysieke input pinnen van de PLC.

## Output Devices: Y

Die representeren de outgangs-devices: bijvoorbeeld darlingtons of output-relais.

### Auxiliary Relays: M

Die representeren intern in te stellen "status vlaggen". Vroeger vermoedelijk daadwerkelijk als relais geimplementeerd.

Er zijn verschillende types van, die afhangen van de gebruikte nummerreeks.
Voor de FX2N serie geldt: algemeen: M0-M4999, battery backed/latched: M500-3071.

Laatstgenoemde slaan hun status op in EEPROM geheugen.

Voorbeeld:
<img src="img/2024-04-24-14-19-44-image.png" title="" alt="" width="383">

Bovenstaande laat een retained bit instellen met de knoppen X0 en X1.

Ook kan:

<img src="img/2024-04-24-14-21-18-image.png" title="" alt="" width="369">

#### Speciale commando's met auxiliary relays:

Voorbeelden:

- M8000 : RUN monitor (ON during run)

- M8002 : Initial pulse (ON momentarily when PLC starts)

- M8012 : 100msec clock pulses

- M8033 : all output statusses are retained when PLC is stopped running

- M034 : all outputs are disabled

- M8039 : de plc draait in "constant scan mode"

- M8047 : zet deze ON om dynamic active states te monitoren

#### Single operation "consumptive" pulse detectie

- M2800-M3072 kan gebruikt worden (zoals eerder aangegeven) om een flank erop te detecteren en te "consumeren", zodat alleen de eerste instructie die hem detecteert hem kan detecteren.

## State Relays: S

Zelfde als M-relays, maar representeren nu de "state".

- S0-S499 : algemeen

- S500-999 : battery backed / latched relays

##### Reserved States

Als de IST (Initial State function) gebruikt wordt, kunnen de volgende states niet meer door de gebruiker gebruikt worden (die zijn dan gereserveerd voor andere doeleinden):

- S0 : de manual operation initial state

- S1 : de zero return initial state

- S2 : de automatic operation initial state

- S10-S19: gealloceerd voor de zero return program sequence.

### Annunciator Flags

Er is nog een moeilijk verhaal over het gebruik van annunciator flags, wellke gebruikt kunnen worden om diagnostics te outputten.
