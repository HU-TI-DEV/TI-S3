# constexpr <!-- omit in toc -->

* Bron: V2CPSE1 reader, TI, HU.nl
* Voorbeelden: [v2cpse1-examples](https://github.com/HU-TI-DEV/v2cpse1-examples)

> Info: Oorspronkelijk gemaakt voor lessen met de Arduino Due, BMPTK en HWLIB.

Behandelde begrippen:

* effect van floating point op (cortex) code size
* constexpr variabele
* constexpr functie
* een namespace is ‘open’
* lookup klasse met template parameters
* template constructor
* lambda (genoemd, geen stof)

## Sinus

Neem aan dat we een sinus functie willen tekenen, voor het gemakt verticaal op de hwlib::cout.
Dit kan met een simpel programma dat gebruik maakt van de sin() functie uit de standaard library.
Dit programma rekent (op de Due) uit wat de (afgeronde en geschaalde) waarden van de sinus is in
stappen van 10 graden, en tekent op die plek een `*`.
Ik vind het in dit geval makkelijker om voor de x-as in graden te denken,
en voor de y-as een sinus te krijgen tussen 0 en 60, dus ik gebruik twee
hulpfuncties.

```cpp
#include <math>

double radians_from_degrees( int degrees ){
  return 2 * 3.14 * ( degrees / 360.0 );
}

int scaled_sine_from_degrees( int degrees ){
  return 30 * ( 1.0 + sin( radians_from_degrees( degrees )));
}

int main( void ){
    . . .
    for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
        for( int i = 0; i < scaled_sine_from_degrees( angle_degrees ); ++i ){
            hwlib::cout << " ";
        }
        hwlib::cout << "*\n";
    }
}
```

**Teken een sinus 05-02**

Het sinus programma is 9316 bytes, zonder de afgebeelde code (maar wel met opstarten en gebruik
van hwlib::cout) is het maar 1536 bytes.

Hoe vaak de `sin()` wordt aangeroepen doet er niet zo veel toe, een programma dat 1 keer een `sin()` aanroept is al 9164 bytes.

Meer dan 7 kB voor een sinus is erg veel.

Dit wordt voor een deel veroorzaakt door een eigenschap van de compiler libraries.

Ze zijn niet in de kleinst mogelijke brokjes opgedeeld: zodra je een functie uit zo’n library gebruikt
wordt de hele library meegelinkt, ook de code die je niet gebruikt.

Dit wordt gedaan om het linken van grote programma’s die veel libraries gebruiken te versnellen.

Er zijn compiler/linker opties die er voor zorgen dat het compileren/linken wel fijnmaziger werkt (bmptk
gebruikt automatisch die opties `-fdata-sections -ffunction-sections`),
maar de met de compiler installatie meegeleverde libraries zijn niet met die opties gecompileerd.

Om dit te ondervangen kunnen we de `sin()` functie uit de library vervangen door een zelf geschreven
functie. Met google kan je uitvinden dat een sinus benaderd kan worden met een Taylor reeks.

> Er zijn vaak betere (snellere) benaderingen dan een Taylor reeks, maar dat is wel de meest bekende.
> Let er als je zo’n reeks gebruikt goed op voor welke waarden de reeks goed werkt,
> de Taylor reeks voor sinus met 3 elementen werkt prima tussen -180 en +180 graden, maar heel slecht daarbuiten.

Met hulpfuncties voor machten en faculteit kunnen we dit eenvoudig naar C++ vertalen:

```cpp
double pow( double g, int n ){
    double result = 1;
    while( n > 0 ){
        result *= g;
        --n;
    }
    return result;
}

double fac( int n ){
    double result = 1;
    while( n > 0 ){
        result *= n;
        --n;
    }
    return result;
}

double sin( double a ){
    return
    a
    - pow( a, 3 ) / fac( 3 )
    + pow( a, 5 ) / fac( 5 )
    - pow( a, 7 ) / fac( 7 )
    + pow( a, 9 ) / fac( 9 )
    - pow( a, 11 ) / fac( 11 )
    + pow( a, 13 ) / fac( 13 );
}
```

**Een zelfgeschreven sinus functie 05-04**

Met deze zelfgeschreven `sin()` is de executable nog ‘maar’ 4168 bytes. Dat is veel minder dan met de
sinus uit de library, maar toch nog best veel. Dit komt omdat de Cortex-M3 processor van de Due
geen floating point hardware heeft, dus die floating point berekeningen worden gedaan door library
code die automatisch door de compiler wordt meegenomen. De omvang hiervan is niet triviaal, en
de floating point berekeningen zijn ook veel langzamer dan integer berekeningen.

> Op een PC is de situatie heel anders: daar heeft de processor floating point hardware, zodat er geen extra
> code nodig is, en floating point berekeningen zijn doorgaans net zo snel als integer berekeningen
> (en soms zelfs sneller).

Als de snelheid van berekeningen een probleem is kan het handig zijn om die berekeningen te
verplaatsen naar het begin van de main, in de initialisatie van de applicatie. Dit maakt het printen
veel sneller. Maar het heeft geen (gunstige) invloed op de omvang van de executabel, die is nu 4488
bytes.

```cpp
int main( void ){
    . . .
    const int table[ 36 ] = {
        scaled_sine_from_degrees( 0 ),
        . . .
        scaled_sine_from_degrees( 350 )
    };

    for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
        for( int i = 0; i < table[ angle_degrees / 10 ]; ++i ){
            hwlib::cout << " ";
        }
        hwlib::cout << "*\n";
    }
}
```

**Een ‘pre-calculated’ table met sinus waarden 05-05**

Als we floating-point berekeningen helemaal willen vermijden kunnen we in plaats van de lijst
aanroepen van scaled_sine_from_degrees() het array initialiseren met de juiste waarden.

In dat soort gevallen (er moeten waarden uitgerekend worden, en dat mag niet tijdens het runnen
gebeuren) werd vaak gebruik gemaakt van een excel sheet of een andere externe tool, waaruit dan
een kolom met waarden wordt gekopieerd naar de C++ source code.

Dit is natuurlijk omslachtig en foutgevoelig als er iets veranderd moet worden aan de berekening.

Een andere (al wat betere) oplossing is om een applicatie te schrijven die een file met de waarden genereert die wordt
meegenomen met het compileren. En dit kan je automatiseren in het Makescript!

Maar al die moeite wordt wel beloond met een veel kleinere executable: 2044 bytes.

```cpp
const int table[ 36 ] = {
    30, // 0
    35, // 10
    40, // 20
    ...
    36 // 350
};
```

**Initialiseer de tabel met (extern berekende) waarden voor 0 .. 350 graden 05-07**

## constexpr

In modern C++ is er een manier om berekeningen (zoals het uitrekenen van een reeks sinussen)
tijdens het compileren te doen dmv. het keyword `constexpr`. Dit keyword wordt op twee manieren
gebruikt. Ten eerste kan je `constexpr` aan de initialisatie van een (constante) variabele hangen om
aan te geven dat de waarde tijdens het compileren al berekend *moet* worden. Dit heeft als
praktische consequentie dat de betreffende non-const variabele in het DATA segment terecht komt
(en zijn initiële waarde in ROM), en een const variabele in het code of read-only segment (ROM).

Zonder de constexpr is de compiler vrij om de waarde tijdens het compileren of tijdens het runnen
te berekenen.

```cpp
const     int x = 15 + 27;   // dit mag een run-time berekening zijn
constexpr int y = 50 – 18;   // dit *moet* een compile-time berekening zijn
```

> In C++11 moest dit geschreven worden als “constexpr const”.
> In C++14 impliceert constexpr (in deze context) const, dus hoef je dat er niet bij te schrijven.

Voor het berekenen van een waarde tijdens het compileren mocht je (voor C++ 0x11) gebruik maken
van literal waarden, constanten, en ingebouwde operatoren. Met C++ 0x11 zijn daar `constexpr functies`
bijgekomen. Een functie die is gedeclareerd als constexpr moet aan een paar eisen voldoen
waardoor de compiler in staat is die functie (mits de waarden van de argumenten bekend zijn)
tijdens het compileren te berekenen. Vanaf C++ 0x14 zijn die eisen redelijk relaxed en intuïtief
(voornamelijk: geen globale dingen gebruiken).

> In C++ 0x11 gold de veel strengere eis dat zo’n functie slechts een enkel return statement mocht
> bevatten. Ingewikkelde berekeningen moesten met recursie gedaan worden.

De meeste library functies waarvan je zou denken dat ze constexpr zouden moeten zijn (bv. sinus)
zijn dat in de praktijk helaas niet, omdat
* volgens de (antieke) definitie veel library functies een fout aangeven door de globale
  variable errno een waarde te geven, en een constexpr functie mag geen globale dingen
  gebruiken
* constexpr relatief nieuw is (2014 voor de makkelijke versie) en veel libraries gewoon nog
  niet zijn aangepast, mede omdat daar op grotere system (Pc’s etc.) niet zo veel behoefte aan is.

Om onze sinus tabel tijdens het compileren te laten berekenen moeten we dus het array constexpr
maken.

```cpp
int main( void ){
    . . .
    constexpr int table[ 36 ] = {
        scaled_sine_from_degrees( 0 ),
        . . .
        scaled_sine_from_degrees( 350 )
    };
    . . .
}
```

**Initialiseer de tabel tijdens het compileren 05-08**

De initiële waarden worden uitgerekend door de functie `scaled_sine_from_degrees()`, dus die moet
constexpr zijn, en alle functies die hij aanroept dus ook. Gelukkig voldeden die functies al aan de
eisen, dus dat is alleen een kwestie van constexpr er voor zetten.

```cpp
constexpr double pow( double g, int n ) . . .

constexpr double fac( int n ) . . .

constexpr double sin( double a ) . . .

constexpr double radians_from_degrees( int degrees ) . . .

constexpr int scaled_sine_from_degrees( int degrees ) . . .
```

Met deze maatregelen is de omvang van de executable hetzelfde als bij de ‘met de hand’ ingevulde
tabel: 2044 bytes. Sterker: de gecompileerde applicatie code is precies hetzelfde.

Deze aanpak heeft dus de voordelen van een van-te-voren uitgerekende tabel (kleine applicatie),
maar niet de nadelen (gebruik van een externe tool, knippen-en-plakken).

De constexpr qualifier kan ook toegepast worden op functies van klassen, inclusief constructors. Een
voorbeeld is de hwlib::location klasse.

```cpp
class location final {
    public:
        int x, y;
        constexpr location( int x, int y ): x( x ), y( y ){}
        constexpr location operator+( const location rhs ) const {
            return location( x + rhs.x, y + rhs.y );
        }
        constexpr location operator-( const location rhs ) const {
            return location( x - rhs.x, y - rhs.y );
        }
};
```

**Klasse functies (inclusief constructors) kunnen ook constexpr zijn (zie Hwlib-graphics.hpp)**

De constructor en beide operatoren van deze klasse zijn constexpr, dus berekeningen op waarden
van deze klasse kunnen al tijdens het compileren gebeuren.

```cpp
#include "hwlib.hpp"

namespace hwlib {
    constexpr location operator/( const location & lhs, int rhs ){
        return location( lhs.x / rhs, lhs.y / rhs );
    }
}

constexpr auto origin    = hwlib::location( 0, 0 );
constexpr auto oled_size = hwlib::location( 128, 64 );
constexpr auto centre    = origin + oled_size / 2;
```

**constexpr berekeningen met met locations**

Merk op dat er nog geen `operator/` bestond voor location. Die is hier *binnen de hwlib namespace*
toegevoegd. Anders dan een klasse is een namespace niet afgesloten, je kan er altijd dingen aan
toevoegen.

## Een constexpr lookup klasse

De lookup table die we hebben gebruikt om sinussen op te zoeken werd geinitialiseerd met een
reeks waarden die we helemaal uit moesten schrijven. Dat wordt natuurlijk ondoenlijk bij grotere
aantallen waarden. We kunnen een sine_lookup klasse maken, die in zijn constructor een for loop
bevat die alle waarden uitrekent en in een tabel stopt.

```cpp
class sine_lookup {
    private:
        std::array< int, 360 > values;
    public:
        constexpr sine_lookup():
        values{}
        {
            for( int i = 0; i < 360; ++i ){
            values[ i ] = scaled_sine_from_degrees( i );
        }

        constexpr int get( int n ) const {
            return values[ n ];
        }
        }
};

int main( void ){
    . . .
    constexpr sine_lookup sinusses;

    for( int angle_degrees = 0; angle_degrees < 360; angle_degrees += 10 ){
        for( int i = 0; i < sinusses.get( angle_degrees ); ++i ){
            hwlib::cout << " ";
        }
        hwlib::cout << "*\n";
    }
}
```

**Een sine-lookup klasse 05-09**

Deze klasse doet wat hij moet doen, maar hij is erg specifiek voor dit geval: hij slaat

* 360 waarden op
* van het type int
* die uitgerekend zijn door de functie scaled_sine_from_degrees().

De eerste twee aspecten kunnen we algemener maken door er template parameters van te maken.

Het derde aspect is iets lastiger, omdat we geen functie kunnen meegeven als template parameter.

We kunnen echter wel een functie meegeven als parameter van de constructor. Om alle
mogelijkheden open te houden kunnen we zelfs vermijden dat we aangeven wat het type van die
parameter is, door van de constructor een template functie te maken. We kunnen nu bij het
initialiseren van de lookup aangeven welke functie er gebruikt moet worden.

```cpp
template< int N, typename T >
class lookup {
    private:
        std::array< T, N > values = {};
    public:
        template< typename F >
        constexpr lookup( F function ){
            for( int i = 0; i < N; ++i ){
            values[ i ] = function( i );
            }
        constexpr T get( int n ) const {
            return values[ n ];
        }
    }
};

auto sinusses = lookup< int, 360>( scaled_sine_from_degrees );
```

**Een algemene lookup klasse 05-10**

Omdat we het type van de ‘functie’ een template parameter hebben gemaakt, zijn we niet beperkt
tot een functie zoals `scaled_sine_from_degrees()`. Er zijn andere dingen in C++ die aangeroepen
kunnen worden alsof ze een functie zijn. Een interessant geval is de lambda (geïntroduceerd in C++
11). Dat is een soort functie die je kunt schrijven op de plek waar je hem als parameter meegeeft.

```cpp
auto sinusses = lookup< 360, int >(
    []( int x )-> int { return 30 * ( 1.0 + sin( radians_from_degrees( x ))); }
);
```

**Een lambda als parameter 05-11**

De applicaties met de lookup klassen zijn wat groter dan die met de opzoektabel: 3332 bytes.

De oorzaak is dat de klassen 360 waarden opslaan, terwijl de tabel er maar 60 had.\
Als we de klassen beperken tot 60 waarden is hun omvang weer gelijk aan de tabel versie.
