# Memory Management

Bron: Eigen materiaal, CPSE2 reader v1.8 (2023-2024-V2CPSE2-reader_v1.8.pdf, p.39-47)

## Overzicht

### Inleiding

Memory Management is nodig voor alle data waar tijdens de programmering niet bekend is hoe groot de nodige ruimte ervoor is.

Denk bijvoorbeeld aan een tekenprogramma dat een bestand inleest om vervolgens grafische elementen te tonen.

Normaliter is het RAM de resource waar we Memory Management willen gebruiken, maar bijvoorbeeld bij SmartCards is dit ook voor EEEPROM/Flash nodig.

### Programmeertaal en platform

Er zijn programmeertalen die het geheugenmanagement voor jij doen, bijvoorbeeld:

- Python
- Java
- Smalltalk
- JavaScript

Programmeertalen die geen geheugenmanagement ingebouwd hebben zijn bijvoorbeeld:

- C/C++
- Assembly Language

Of een taal met 'ingebouwd' geheugenmanagement kan worden gebruikt of niet hangt ook af van de ontwikkelplatform die je gebruikt.

Voorbeelden:

- op een Arduino Uno met zijn ATmega 328 ca. 2 kB RAM ter beschikking
- op een ATtiny24 heb je 512 bytes RAM (en 2K FLASH)
- op een Raspberry Pi Pico of een STM32 "Blue Pill" heb je veel meer ruimte (512kB
- op een Raspberry Pi heb je meerdere gigabytes beschikbaar

Verder zijn er industriestandards voor de ontwikkeling, bijvoorbeeld:

- [NASA C coding guidelines (prohibit memory allocation)](http://spinroot.com/gerard/pdf/P10.pdf)
- [MISRA C standard, commonly used in automotive](https://en.wikipedia.org/wiki/MISRA_C)

### Hardware

Sommige platformen / processorchips / SoCs hebben hardware-ondersteuning voor het bijhouden van gebruikte RAM en ter bescherming van ongewenste verandering of toegang. Meestal zijn dit 'grotere' platformen met (potentieel) veel RAM.

Voorbeelden:

- Intel/AMD x64 architectuur
- Motorola 68K architectuur
- Power ISA (instruction set architecture)

### Software

Voor programmeertalen die zelf geen geheugenmanagement hebben zijn meestal libraries (bibliotheken) beschikbaar om het werk voor de ontwikkelaar makkelijker te maken. Voor C++ heeft de `Standard Template Library (STL)` bijvoorbeeld ondersteuning in vorm van 'smart pointers'. Daarop gaan we in het gevolg dieper in.

## De Heap

Behandelde begrippen en technieken:

- Heap
- malloc(), free()
- new, new[], delete, delete[]
- Garbage collection
- Regel van drie
- Eigenaarschap
- Smart pointers: unique_ptr<>, shared_ptr<>

### Levensduur van objecten

Ieder object in een C++ applicatie heeft een levensduur:

- Parameters ontstaan net voordat de functie wordt uitgevoerd, en worden opgeruimd nadat de functie is uitgevoerd (de destructor wordt aangeroepen en de ruimte wordt vrijgeven).
- Lokale (niet-statisch) variabelen ontstaan op de plek van hun definitie, en worden opgeruimd als het blok eindigt.
- Een tijdelijk object (het resultaat van een functie aanroep) ontstaat op het moment dat het nodig is en wordt opgeruimd bij het eerstvolgende ‘sequence point’, dat is meestal het einde van het statement waarin het tijdelijke object ontstond.
- Een globale variabele ontstaat voordat de main() begint, en wordt opgeruimd nadat de main() eindigt.
- Een lokale statische variabele ontstaat op het moment dat zijn functie voor het eerst uitgevoerd wordt, en wordt eveneens opgeruimd nadat de main() eindigt.

Parameters, lokale variabelen en tijdelijke objecten worden in het geheugen opgeslagen op de stack.

Waar ze precies terechtkomen in het geheugen dat is toebedeeld aan de stack hangt af van de reeks functieaanroepen die op dat moment actief is.

Globale variabelen en lokale statische variabelen worden opgeslagen op een door de linker bepaalde plaats, in het BSS, DATA, of TEXT segment.

In al deze gevallen heeft de programmeur geen omkijken naar de levensduur van de objecten, en er ook geen invloed op.

Wel moet de programmeur opletten om geen objecten te gebruiken nadat ze opgeruimd zijn (dat is undefined behaviour).

### Flexibel gegevensgebruik

Op het moment dat een object wordt aangemaakt moet worden aangegeven wat het exacte type is, en dat betekent voor bijvoorbeeld een array<> ook hoe groot die kan zijn. Dit is vervelend als je een object wil aanmaken dat een hoeveelheid gegevens moet opbergen die op dat moment nog niet bekend is, bijvoorbeeld omdat het van externe dingen afhangt (invoer van de gebruiker, inhoud van een bestand, etc.).

Een oplossing hiervoor is om de gegevens niet in je object zelf op te slaan maar in een ander object, dat je op de heap alloceert.

Dit is wat std::vector en std::string doen. In je oorspronkelijke object kun je dan een pointer naar dit heap object opslaan. Om de hoeveelheid gegevens die je op deze wijze kan opslaan flexibel te houden kun je twee technieken gebruiken:

- Pointer naar array: je kunt op de heap in plaats van een enkel object een array van objecten
toewijzen, met een tijdens het runnen bepaald aantal elementen. Mocht dit aantal niet
genoeg zijn, dan kun je een nieuw array op de heap alloceren dat groter is, en alle oude
elementen daarheen kopiëren. Dit lijkt erg tijdrovend, maar als je zodra het oude array niet
groot genoeg is het nieuwe array bijvoorbeeld 2x zo groot maakt, dan komt dit over
kopiëren gemiddeld niet vaak voor.

- Recursieve datastructuur: je kunt in ieder object een of meer pointers zetten die naar
volgende objecten wijzen (of nullptr zijn als er geen volgende objecten zijn). Zo kun je net zo
veel objecten alloceren en met pointers aan elkaar verbinden als je nodig hebt.

### Voor- en nadelen

De recursieve datastructuur vermijdt het kopiëren dat bij de array versie nodig is, maar alloceert wel
veel meer (kleinere) objecten, die in de meeste gevallen willekeurig over het geheugen verspreid
zijn. Dit vergt meer CPU-tijd voor het ‘managen’ van de heap, en is ongunstig voor de ‘lokaliteit’ van
je data en dus voor de performance van je cache.

### Kiezen: geheugen en cache

Daardoor is het op een systeem met genoeg geheugen en een hiërarchie van caches in de meeste
gevallen beter om een array-gebaseerde opslag te gebruiken dan een die gebaseerd is op een
recursieve datastructuur.

Voor een systeem met weinig geheugen en geen caches geldt eerder het omgekeerde.

### Programmeertal C: `malloc()` en `free()`

In C is er voor het alloceren van heap geheugen de functie malloc(). Die geef je het aantal bytes mee
dat je wilt hebben, en je krijgt een void pointer (een pointer waarvan niet bekend is naar wat voor
type hij wijst) terug naar een stuk geheugen (of NULL als er op de heap geen ruimte meer is). Als je
het geheugen niet meer nodig hebt roep je free() aan met de pointer.

```c
struct person {
   /* ... */
};

/* ... */

person *p = malloc(sizeof(person));
/*
 *  gebruik *p
 */
free(p);
```

*Geheugen toewijzen en vrijgeven in C*

### Undefined behaviour bij object allocatie

Het geheugen gebruiken nadat je het hebt vrijgegeven, of meer gebruiken dan je gealloceerd hebt,
of het twee keer vrijgeven, vallen allemaal onder ‘undefined behaviour’. In C ben je er zelf voor
verantwoordelijk dat je het juiste aantal bytes reserveert, de compiler zal je daar niet bij helpen,
maar je kunt wel sizeof() gebruiken om de kans op fouten te verminderen. De malloc functie geeft
een void* terug, en die kun je (in C) toewijzen aan ieder type pointer dus helaas ook aan een
verkeerd type.

### Programmeertal C++: `new` en `delete`

In C++ is er het keyword `new` voor het alloceren van een enkel object en `new[]` voor het alloceren
van een array van objecten.

**Allocatie van een enkel object**

- Als je een **enkel object** alloceert geef je meteen ook aan
  - Wat het type is en
  - wat de constructor parameters voor dat object zijn.

De compiler bepaalt voor je hoeveel geheugen er nodig is (dat kun je dus niet fout doen), en
zorgt ervoor dat de constructor wordt aangeroepen.

Je krijgt een pointer terug naar de juiste klasse, die hoef je dus niet te casten en je kunt
alleen toewijzen aan het juiste soort pointer.

Als er niet genoeg heap geheugen meer beschikbaar is krijg je de speciale waarde nullptr terug.

> In C heet deze speciale waarde NULL, en deze waarde is in C++ ook beschikbaar. Het gebruik van nullptr
heeft echter de voorkeur.

**Allocatie array**

- Bij het alloceren van een **array** geef je aan
  - Hoeveel array elementen je wilt hebben en
  - van wat voor type.

Dee compiler zorgt ervoor dat die elementen ieder geinitialiseerd worden door aanroepen
van de default constructor.

Als je het geheugen niet meer nodig hebt dan roep je delete
(voor een enkel object) of delete[] (voor en array van objecten) aan om het geheugen weer
vrij te geven. De compiler zorgt ervoor dat, voordat het geheugen weer aan de heap wordt
toegevoegd, de destructor(s) worden aangeroepen.

```cpp
person *p2 = new person();
// gebruik *p2
delete p2;

person *p3 = new person[ 20 ];
// gebruik *p3
delete[] p3;
```

*Allocate and free memory in C++*

### Undefined behaviour bij array allocatie

Net als bij C is het undefined behaviour om meer array elementen te gebruiken dan je gealloceerd
hebt, of het te gebruiken nadat je het hebt vrijgegeven.

Daarnaast is het ook undefined behaviour als je alloceert met `new` en vrijgeeft met `delete[]` of andersom en als je alloceert met malloc en vrijgeeft met `delete` (of `delete[]`) of andersom.

Maar op veel systemen maakt het in de praktijk helaas niet uit omdat zowel new als new[] gewoon malloc aanroepen.

> 'Helaas' omdat het over het algemeen beter is als een fout zo snel mogelijk aan het licht komt.
> De meest vervelende vorm van undefined behaviour is als de code doet wat de programmeur (ten onrechte) verwacht.
>
> Waarom is dit vervelend ("maar he werkt toch gewoon goed?")?\
> Omdat je geen garantie hebt dat het ook nog werkt na een update van je ontwikkelsysteem (toolchain, compiler/linker),
> of als je dezelfde code ater gebruikt op een andere platform (met eigen toolchain).\
> In het Engels noemen we dit soms "It's a ticking time-bomb!".

### Libraries

Goed gebruik van de heap is lastig. Daarom wordt dit in de meest gevallen afgehandeld in libraries.

Voorbeelden hiervan zijn std::vector en std::string, die zonder dat je er omkijken naar hebt
geheugen op de heap alloceren en weer vrijgeven.

Als je toch zelf met de heap gaat werken, gebruik dan de smart pointers zoals verderop beschreven.

### Garbage collection

Als je het geheugen niet meer nodig hebt maar ook niet vrijgeeft dan zal het systeem op den duur
door z’n geheugen heen raken: het heeft dan een **'memory leak’**.

Hoe erg dit is hangt af van hoe je de applicatie gebruikt: bij een applicatie die runt en snel klaar is zoals een compiler hoeft dit geen probleem te zijn, maar voor bijvoorbeeld een Operating System of een webserver betekent het dat het systeem op den duur vastloopt en opnieuw opgestart moet worden.

Dit heeft ertoe geleid dat talen als Java en Python het managen van geheugen helemaal op zich nemen: het run-time systeem dat bij de taal hoort bevat een “garbage collector” die geheugen dat niet meer wordt gebruikt automatisch vrijgeeft voor hergebruik.

Het voordeel hiervan is dat de programmeur er geen omkijken naar heeft en er ook geen fouten mee kan maken.

Nadelen zijn:

- Garbage Collection kost tijd, en maakt daardoor de run-time performance van het systeem
op korte termijn minder voorspelbaar;22

- Het moment waarop een object wordt vrijgegeven wordt bepaald door de garbage collector,
niet door de programmeur. In dergelijke talen heeft een object doorgaans geen destructor,
wat het lastiger maakt om andere resources dan geheugen effectief te managen.

De eenvoudigste vormen van garbage collection gaan aan het werk als er tekort aan geheugen is en doen
dan een ‘sweep’ (veeg) over het geheugen om alle ongebruikte stukken te verzamelen. Dit leidt tot een korte
piek in CPU gebruik, wat voor real-time systemen onwenselijk is. Er zijn ook ‘concurrent’ garbage collectors die
de CPU last meer over de tijd verspreiden.

**Desktop versus real-time applicaties**

- Voor een gemiddelde desktopapplicatie wegen de voordelen meestal zwaarder dan de nadelen.
- Voor een real-time applicatie wegen de nadelen meestal zwaarder.

In sommige gevallen worden de sterke punten van beide benaderingen gecombineerd:
het is niet ongewoon om voor een spel de performance-kritische delen in C of C++ (soms zelfs in assembler) te schrijven,
en het (veel grotere) deel dat niet tijd-kritisch is in een gemanagede taal (bijvoorbeeld Java of Python).

### Geheugenadministratie Heap

Bij het alloceren en/of vrijgeven van een stuk geheugen moet de library code die de heap beheert de
administratie van het vrije geheugen bijwerken.

Als er al vrije blokken zijn (die gescheiden worden door blokken die wel in gebruik zijn)
en er wordt een blok vrijgegeven, dan wordt (meestal tijdens het vrijgeven) de lijst langsgelopen
om te kijken of het nieuwe blok met oudere blokken gecombineerd kan worden tot een groter blok.

Hoeveel tijd dit kost is lastig te voorspellen omdat het afhangt van de toestand van de administratie,
met andere woorden: van het verleden.

Om deze reden wordt het gebruik van de heap in real-time systemen vaak vermeden, in ieder geval tijdens
het uitvoeren: soms wordt nog wel heap geheugen gealloceerd tijdens het opstarten.

### De regel van drie

**De klasse zorgt zelf voor allocatie en deallocatie**

Een manier om met geheugen allocatie om te gaan is dat een klasse expliciet zorgt dat alle dingen
die hij alloceert ook door hem worden vrijgegeven.

Neem als voorbeeld een klasse die de naam van
een persoon opslaat in een gealloceerd char array (zie volgend code fragment).

De array wordt in de constructor gealloceerd, en in de destructor weer vrijgegeven. Het `name` object is de eigenaar van
het gealloceerde geheugen, en is dus verantwoordelijk voor het alloceren en dealloceren.

Als je voor alle gealloceerde dingen op deze wijze een eigenaar kan aanwijzen is het geheugen
managementprobleem (geheugen lekken, gebruik van al vrijgegeven geheugen) in principe opgelost.

```cpp
class name {

private:
   char * p;

public:
   name( const char * s ){
      p = new char[ std::strlen( s ) + 1 ];
      std::strcpy_s( p, std::strlen( s ) + 1, s );
   }

   ~name(){
      delete[] p;
   }
};
```

*Een klasse die de heap alloceert (in de constructor) en vrijgeeft (in de destructor)*

**Copy constructor**

Er zijn nog wel wat losse eindjes. De name klasse heeft geen **copy constructor**.

In dat geval zal de compiler een copy constructor aanmaken.

Die kopieert alle attributen (gebruikmakend van hun copy constructors).

Voor een pointer houdt dit in dat er een kopie wordt gemaakt van de pointer.

In de volgende code is die copy constructor voor de duidelijkheid expliciet uitgeschreven.

Als we deze copy constructor gebruiken dan krijgen we twee variabelen, wiens pointers naar hetzelfde op de
heap gealloceerde namen wijzen. Dat wordt interessant als we de naam van de ene veranderen: de
andere verandert dan mee! En het wordt helemaal chaos als de destructors van de beide variabelen
worden aangeroepen: hetzelfde heap object wordt dan twee keer vrijgegeven, wat resulteert in het
gevreesde Undefined Behaviour. Uit het onderstaande geval krijg je gelukkig een foutmelding, maar
dat is niet gegarandeerd.

```cpp
class name {
   public:
      char * p;

      name( const char * s ){
         p = new char[std::strlen( s ) + 1];
         std::strcpy( p, s );
      }

      // this copy constructor would be generated by the compiler
      name( const name & rhs ):p{ rhs.p }{
        // geen code, alleen de initialisatielijst
      } 

      ~name(){
          delete[] p;
      }
}; // end class name

int main() {
   name w("Wouter");
   name q(w);

   std::cout << w.p << " " << q.p << "\n"; // Wouter Wouter

   w.p[0] = 'J';

   std::cout << w.p << " " << q.p << "\n"; // Jouter Jouter (laatste is onverwacht!)

   return 0;
}
```

*De impliciete copy constructor levert een probleem op*

Een correcte copy constructor moet in zijn eigen object ruimte reserveren voor de naam, en dan de
letters van de naam van de parameter daarheen kopiëren.

```cpp
      // copy constructor allocating its own memory
      name(const name & rhs){
         p = new char[std::strlen(rhs.p) + 1 ]; // +1 for the ‘\0’ at the end of a string
         std::strcpy( p, rhs.p );
      }
```

*Een copy constructor die wel eigen geheugen alloceert*

Dat is eigenlijk hetzelfde werk dat de gewone constructor al doet!

Om in een constructor een andere constructor (een deel van) het werk te laten doen
kun je gebruik maken van **constructor ‘delegation’**:
je roept dan in de initialisatie een lijst van een constructor aan een andere constructor aan.

Daarmee is de copy constructor teruggebracht tot een minimum:

```cpp
      // copy constructor using constructor delegation
      name(const name & rhs):name(rhs.p){}
```

**Assignment operator**

Behalve de copy constructor maakt de compiler, als je die zelf niet schrijft, ook automatisch een
assignment operator aan.

Deze assignment operator assignt (kopieert) de attributen, gebruikmakend van hun assignment operatoren.

Voor een pointer betekent dit (net als bij de constructors) dat de pointer wordt gekopieerd,
zoals in de volgende code expliciet is uitgeschreven.

Dit levert voor de name klasse een dubbel probleem op: na een assignment zijn er, net als na een
copy, twee variabelen wiens pointers naar dezelfde naam wijzen (met alle problemen die bij de copy
constructor zijn genoemd), en het object dat door de bestemming van de assignment was
gealloceerd is voorgoed verloren.

```cpp
      // this implicit assignment operator would be generated by the compiler
      name & operator=( const name & rhs ){
         p = rhs.p;
         return *this;
      }
```

Een naïeve oplossing is dat we in de assignment operator eerst ons eigen gealloceerde geheugen
vrijgeven, en daarna (net als in de constructors) voldoende geheugen alloceren voor de nieuwe
naam, en die kopiëren.

```cpp
      // naïve assignment operator
      name & operator=(const name & rhs) {
         delete[] p;
         p = new char[std::strlen(rhs.p) + 1];
         std::strcpy(p, rhs.p);
         return *this;
      }
```

Dit gaat perfect, behalve in het geval wanneer een dergelijke variabele aan zichzelf wordt
toegekend: dan zijn p en rhs.p hetzelfde, dus na de ”delete[] p” regel kun je ook rhs.p niet meer
gebruiken.

Dit kun je op twee manieren oplossen:

- Bewaar een kopie van de p pointer, en geef het geheugen waar die naar wijst pas op het einde vrij;
- Check of de rhs en het object dezelfde zijn. Als dat zo is dan hoeft er niets te gebeuren.

Beide methoden voldoen.

```cpp
      // 'save-old-pointer' assignment operator
      name & operator=(const name & rhs) {
         auto old_p = p;
         auto rhs_p = rhs.p;
         p = new char[std::strlen(rhs_p) + 1];
         std::strcpy(p, rhs_p);
         delete[] old_p;
         return *this;
      }
```

```cpp
      // 'do-nothing assignment in case of self-assignment' assignment operator
      name & operator=(const name & rhs) {
         if (&rhs != this) {
            delete[] p;
            p = new char[std::strlen(rhs.p) + 1];
            std::strcpy(p, rhs.p);
         }
         return *this;
      }
```

*Twee manieren om self-assignment correct af te handelen*

Deze manier om met het alloceren van heap geheugen om te gaan (door het te verbergen in een
klasse, en die klasse het werk te laten doen) wordt wel **de regel van 3** genoemd:

Als je een klasse schrijft met een pointer er in die moet wijzen naar heap geheugen,
dan moet je vrijwel altijd 3 functies schrijven:

- Een of meer **constructors** waarin het geheugen wordt gealloceerd (denk eraan dat de
compiler een default constructor maakt als er helemaal geen constructors zijn, en een copy
constructor als er geen copy constructor is);
- Een **assignment operator** waarin het oude geheugen wordt vrijgegeven en het nieuwe
geheugen wordt gealloceerd (denk eraan dat de compiler een assignment operator maakt
als er geen geschreven is);
- Een **destructor** waarin het geheugen wordt vrijgegeven.

### Eigenaarschap

Het werken met pointers en heap objecten lijkt misschien niet zo moeilijk: als je datgene wat je
alloceert zelf weer vrijgeeft komt alles goed.

Dat is zo, maar het venijn zit in de situaties waar degene die het object heeft gealloceerd
niet degene is die het ook weer vrijgeeft.

Bijvoorbeeld als je een functie hebt die een object aanmaakt naar aanleiding van een invoerbestand.

Die functie levert (een pointer naar) het aangemaakte object op. Het is aan zijn aanroeper om dat
object ooit weer vrij te geven. Als het object wordt opgeslagen in een datastructuur die door
meerdere delen van de applicatie wordt gebruikt dan wordt het lastig helder te houden wie er
verantwoordelijk is voor het vrijgeven.

De kern van het probleem is eigenaarschap: Wie is de eigenaar van het gealloceerde geheugen, en
dus verantwoordelijk voor het vrijgeven?

Bij code die op deze manier werkt (bijvoorbeeld een functie die een pointer naar gealloceerd geheugen teruggeeft)
moet heel duidelijk in de documentatie staan dat het eigenaarschap van dat geheugen wordt overgedragen
naar de aanroeper van de functie.

Nog beter is het een ‘smart pointer’ te gebruiken, zie de volgende paragraaf.

### Smart pointers

Een variabele wordt aan het einde van zijn levensduur opgeruimd (het object wordt gedestruct, en
de ruimte wordt vrijgegeven). Maar dit geldt alleen voor de variabele zelf, als het een pointer is geldt
dit niet voor hetgeen waar de pointer naar wijst. In de volgende code (over het toekennen van vogel
namen) wordt aan het einde van de functie test() calimero wel opgeruimd, want dat is een variabele,
maar flappy niet, want die is op de heap aangemaakt, en er staat nergens een ‘delete p;’ statement.

```cpp
class bird{
   private:
      std::string name;

   public:
      bird(const char *name):name(name){
         std::cout << "bird " << name << " created\n";
      }
      ~bird(){
         std::cout << "bird " << name << " destructed\n";
      }
      void fly(){
         std::cout << "bird " << name << " flies\n";
      }
};

void test(){
   bird c("calimero");
   bird * p = new bird("flappy");

   c.fly();
   p->fly();
}
```

*Flappy wordt niet opgeruimd*

In het terminal venster zien we dan ook:

```text
bird calimero created
bird flappy created
bird calimero flies
bird flappy flies
bird calimero destructed
```

Als wij de enige ‘eigenaar’ zijn van het object waar de pointer naar wijst zou het heel handig zijn als
het geregeld kon worden dat dit wel automatisch gebeurt. Dat kan door in plaats van een pointer
een ‘pointer-achtig ding’ te maken: een object dat zich gedraagt als een pointer, maar in zijn
destructor ook dat waar hij naar wijst verwijdert.

**Benodigde operaties**

Wat voor operaties hebben we nodig van zo’n ‘smart pointer’?

- Het moet een `template` zijn, want we willen zulke pointers voor ieder basistype kunnen maken.
- We moeten er één kunnen aanmaken, dus `construeren`, op grond van een gewone pointer.
- In zijn `destructor` moet hij die pointer verwijderen.
- Verder is de belangrijkste operatie van een pointer het dereferencen, en dat levert het object op
waarnaar wordt gewezen. Dat moet de `operator*` dus ook doen.
- In C++ is de `operator->` (de combinatie van *dereference* en het benaderen van een onderdeel) een aparte operator, die gek genoeg niet het object maar een pointer naar het object moet teruggegeven. Die operator moeten we dus ook hebben.

```cpp
template<typename T> 
class remover {
    private: 
       T *p;
    
    public: 
       remover(T* p):  
          p( p ){} 
     
       ~remover(){  
          delete p;  
       } 
     
       T & operator*() const {  
          return *p;  
       } 
     
       T * operator->() const {  
          return p;  
       } 
}; 
```

*Een pointer wrapper die (in zijn destructor) het onderliggende object vrijgeeft*

Hiermee hebben we een werkende ‘smart pointer’ die het object waar hij naar wijst verwijdert op het moment dat hij zelf wordt weggegooid.

```cpp
void test(){ 
    bird c("calimero"); 
    remover<bird> p(new bird("flappy")); 
 
    c.fly(); 
    (*p).fly(); 
    p->fly(); 
} 
```

*Nu wordt flappy ook opgeruimd*

In het terminal venster zien we dan ook:

```text
bird calimero created
bird flappy created
bird calimero flies
bird flappy flies
bird flappy flies
bird flappy destructed
bird calimero destructed
```

Er zijn nog wel wat losse eindjes: bijvoorbeeld de assignment en de copy constructor moeten zorgen dat er maar één exemplaar van de pointer bestaat.

Een dergelijke smart pointer is beschikbaar in de Standard Template Library (STL) library als std::unique_ptr<>.

**std::unique_ptr<>**

De naam verwijst ernaar dat er altijd maar zo’n 1 pointer naar het heap object zal zijn.
Als die pointer gewist wordt dan wordt dus ook het heap object gewist.

> Een unique_ptr heeft wel een assignment operator en een copy constructor,
> maar die maken de ‘source’ pointer leeg (zetten deze op nullptr).

```cpp
#include<memory> 
void test(){ 
    bird c("calimero"); 
    std::unique_ptr<bird> p(new bird( "flappy" )); 

    c.fly(); 
    (*p).fly(); 
    p->fly(); 
} 
```

*Gebruik van een std::unique_ptr<>*

**std::make_unique**

In de vorige code wordt bij het alloceren het type (`bird`) twee keer genoemd.
Als dat een  ingewikkelde type expressie is, is het handiger om de (template) functie std::make_unique te
gebruiken. Een andere reden is dat je dan het expliciet gebruik van `new` in je code kan vermijden.
Dit  maakt het makkelijker om met tooling te verifiëren dat alle heap allocaties in smart pointers worden opgeborgen.

```cpp
#include<memory>

auto p = std::make_unique<bird>("flappy");
```

*`std::make_unique<>` verbergt ook een `new` aanroep*

**std::shared_ptr<>**

Een andere smart pointer die vaak handig is heet `std::shared_ptr<>`. Een `shared_ptr` kun je
toewijzen, en er kunnen meerdere van deze pointers naar hetzelfde object wijzen. De `shared_ptr`’s
die naar hetzelfde object wijzen houden bij met hoeveel ze zijn, en als de laatste ophoudt met naar
dat object te wijzen (omdat hij zelf gewist wordt, of omdat hij naar een ander object gaat wijzen, of
omdat hij gereset wordt en dus naar niets gaat wijzen), dan delete hij het object.  

```cpp
#include<memory> 
void test(){ 
    std::shared_ptr<bird> p1(new bird("flappy")); 
    std::shared_ptr<bird> p2; 
    p2 = p1; 
    p1.reset(); 
    p2.reset(); 
} 
```

*Een std::shared_ptr<> kun je delen met anderen*

```text
bird flappy created
bird flappy destructed
```

**De klasse `name` met een `unique_ptr`**

Met een `unique_ptr` kunnen we de `name` klasse iets eenvoudiger maken.

De destructor is overbodig, want de door de compiler-gegenereerde destructor roept de destructor van de unique pointer aan, en die zorgt ervoor dat het geheugen wordt vrijgegeven.

De gewone constructor, copy constructor en assignment operator zijn nog wel nodig, maar in de assignment hoef je het oude geheugen niet meer vrij te geen, want dit gebeurt automatisch als je de unique pointer naar een nieuw stuk geheugen laat wijzen.

```cpp
    class name { 
        private: 
            std::unique_ptr< char[] > p;

        public: 
            name(const char * s) { 
                p = std::make_unique<char[]>(std::strlen(s) + 1); 
                std::strcpy(p.get(), s); 
            }

            name(const name & rhs) : name(rhs.p.get()) {} 
            
            name & operator=(const name & rhs) { 
                auto temp = new char[std::strlen(rhs.p.get()) + 1]; 
                std::strcpy( temp, rhs.p.get() ); 
                p.reset(temp); 
                return *this; 
            } 
            
            // no destructor needed 
    }; 
```

*De `name` klasse met gebruik van een `std::unique_ptr<>`*

## Opdracht

- Schrijf een eigen programma
  - dat alle memory management technieken toont
  - en de constructie/destructie van de objecten zichtbaar maakt\
    (dat mag ook in een logfile als je bijvoorbeeld voor een spel
     geen afleidende uitvoer op het scherm wil hebben).
- Verwerk dit in jouw portfolio / verantwoordingsdocument.

Veel plezier en succes!

----
EOF
