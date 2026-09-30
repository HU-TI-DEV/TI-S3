# C++ Templates <!-- omit in toc -->

* Bron: V2CPSE1 reader, TI, HU.nl
* Voorbeelden: [v2cpse1-examples](https://github.com/HU-TI-DEV/v2cpse1-examples)

Behandelde begrippen:

- functie template
- ? (ternary operator)
- impliciete instantiering van functie templates
- template parameters
- template staat in header file
- class template
- operator[ ], operator[ ] const
- proxy pattern
- conversie operator

## Maximum

Het is niet moeilijk het maximum van twee integers te bepalen, hieronder staan twee versies.

De eerste komt wellicht wat leesbaarder over, maar de tweede versie is wat een ervaren C++
programmeur waarschijnlijk zou schrijven. Het maakt gebruik van de `?` operator (de ‘ternary
operator’), die werkt als een if statement maar dan voor twee expressies: als de waarde voor de `?`
waar is dan is het resultaat de eerste expressie, zo niet dan is het resultaat de tweede expressie.

```cpp
int max( int a, int b ){
    if( a > b ){
        return a;
    } else {
        return b;
    }
}

int max_versie2( int a, int b ){
    return ( a > b ) ? a : b;
}
```

**max functies voor int parameters 04-01**

Deze functie berekent dus het maximum van twee integers, maar we willen wellicht ook het
maximum van twee floats kunnen bepalen, en van twee doubles.

Een waarom ook niet van twee kleuren, even aangenomen dat er voor kleuren een `>` operator bestaat?

De source code van die andere `max()` functies is het zelfde als de integer `max()`,
alleen het type van de parameters en de return waarde is anders.

## Functie template

Een `template` in C++ is een functie of klasse die extra parameters heeft, die tijdens het compileren
worden meegegeven. Deze extra parameters kunnen typen (klassen) zijn of constante (integer) waarden.

> In C++ 2020 wordt het waarschijnlijk mogelijk om ook andere waarden als template parameters te gebruiken

We kunnen van de `max()` functie een functie template maken door het type dat we vergelijken uit de
functie te lichten en te vervangen door `T`, en dan aan te geven dat `T` een template parameter van
de functie is. Omdat het type `T` wellicht een ingewikkeld object is waarvan het kopiëren tijd kost (of
misschien niet eens mogelijk is) is de overdracht van de parameters veranderd van ‘by value’ naar
‘by const reference’.

> Het lijkt de gewoonte te zijn om voor template parameters losse hoofdletters te gebruiken.
> (Misschien gaat dit met toenemend gebruik van templates veranderen naar betekenisvollere namen.)

```cpp
template< typename T >
T max( const T & a, const T & b ){
    return ( a > b ) ? a : b;
}
```

**max() functie template 04-02**

Hiermee hebben we de compiler geïnstrueerd hoe hij, gegeven een type T, van twee waarden van
dat type het maximum kan bepalen en teruggeven.

Het enige wat daarbij wordt vereist is dat het
betreffende type een `operator>` en een `copy constructor` heeft. Nu kunnen we in onze code naar
hartenlust het maximum van dingen bepalen. Het leuke van een functie template is daarbij dat de
compiler automatisch de functies (instanties van de template) aanmaakt zodra ze nodig zijn.

> De copy constructor is nodig om de return waarde by value te kunnen teruggeven.

```cpp
std::cout << max( 11, 12 ) << "\n";
std::cout << max( 2.718, 3.14 ) << "\n";
std::cout << max( "ab", "cd" ) << "\n";
```

**Gebruik van de max() functie template 04-02**

De derde regel geeft een probleem: voor het type `char[3]` is geen `operator>` beschikbaar, dus als de
compiler de `max()` functie voor dat type probeert aan te maken geeft hij een foutmelding:

```text
main.cpp:14:31: error: no matching function for call to 'max(const char [3], const char [3])'
std::cout << max( "ab", "cd" ) << "\n";
```

De locatie van deze foutmelding is in dit geval de regel waar we de `max()` functie gebruiken, maar
het had ook de regel in de functie template kunnen zijn waar de `>` gebruikt wordt. Het gebruik van
ingewikkeldere templates kan soms zeer mysterieuze foutmeldingen geven.

Overigens is het niet nodig de `max()` template zelf te schrijven: de header <algorithm> bevat al een
`std::max()`, die standaard gebruik maakt van `operator<`, maar je ook de mogelijkheid biedt zelf een
operator mee te geven die als ‘smaller than’ gebruikt moet worden. Daarnaast kan je met `std::max()`
ook het maximum van een reeks van waarden opvragen. En uiteraard is er ook een `std::min()`.

In sommige gevallen is het nodig om expliciet op te geven voor welke parameters je een functie
template wilt instantiëren. Dit doe je door die parameters op te geven tussen `<>` haakjes. In het
volgende voorbeeld wordt dus de `max<float>` gebruikt in plaats van de `max<int>` die geselecteerd
zou worden op grond van de parameters.

```cpp
#include <iostream>
#include <algorithm>

int main( void ){
    std::cout << std::max< float >( 11, 12 ) << "\n";
}
```

**std::max() met expliciete template parameter 04-03**

## C-stijl array

Er zijn in C++ twee manieren om een array te maken. De ‘C-style’ array is overgenomen uit de taal C.

```cpp
int main(){
    double a[ 9 ];
    a[ 5 ] = 17.3;
    std:: cout << a[ 5 ] << "\n";
}
```

**C-style array 04-10**

Een nadeel van dit soort array is dat alle arrays die hetzelfde type bevatten (dus bv. alle `double`
arrays) voor de compiler het zelfde type zijn: het aantal elementen is geen onderdeel van het type.

Dit kan makkelijk zijn als je arrays van verschillende lengte wil kunnen doorgeven aan de zelfde
functie, maar je moet dan wel zelf zorgen dat die functie weet hoeveel elementen er in het array
zitten.

```cpp
void print( int a[ 2 ] ){
    // for( auto x : a ) won't work because the size of a is not known
    for( unsigned int i = 0; i < 2; ++i ){
        std::cout << a[ i ] << "\n";
    }
}
int main(){
    int a2[ 2 ] = { 1, 2 };
    int a4[ 4 ] = { 5, 6, 7, 8 };
    print( a2 );
    print( a4 );
}
```

**C-style arrays als functie parameter 04-11**

De `print()` functie vermeldt wel dat hij een array van 2 integers verwacht, maar de compiler negeert
die 2 volkomen, en je kan die 2 ook weglaten.

Dat is misschien duidelijker, want anders zou je kunnen denken dat alleen arrays van 2 integers toegestaan zijn als parameter.
Dat is niet zo, de compiler accepteert natuurlijk een array van 2 integers, maar een array van 4 integers is ook acceptabel.

Dat is nog niet zo erg, want een array van 4 integers bevat in ieder geval de 2 integers
die geprint worden.

Maar een array van 1 integer wordt ook geaccepteerd. Het is aan de
programmeur om dit te voorkomen, want wat er dan gebeurt is undefined behaviour.

```cpp
int main(){
    int a1[ 1 ] = { 42 };
    print( a1 );
}
```

**C-style arrays als functie parameter – undefined behaviour! 04-03**

## std::array

De moderne manier om in C++ een array te maken is `std::array`. Dit is geen onderdeel van de taal,
het is een feature in de library <array> die we dus moeten #includen.

```cpp
#include <iostream>
#include <array>

int main(){
    std::array<double,9> a;
    a[ 1 ] = 17.3;
    std:: cout << a[ 1 ] << "\n";
}
```

**std::array 04-20**

Anders dan bij een C-stijl array zijn twee std::array<>’s alleen van het zelfde type als zowel het
basistype als het aantal hetzelfde zijn. Als je zo’n array als functie parameter doorgeeft dan moet die
dus precies overeen komen met wat de functie verwacht. Dat is veilig, maar het betekent wel dat je
voor iedere aantal array elementen een aparte functie zou moeten schrijven.

```cpp
#include <iostream>
#include <array>

void print( const std::array< int, 2 > & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}

void print( const std::array< int, 4 > & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}

int main(){
    std::array< int, 2 > a2 = { 1, 2 };
    std::array< int, 4 > a4 = { 5, 6, 7, 8 };
    print( a2 );
    print( a4 );
}
```

**std::array<>’s als functie parameter 04-21**

Je kan die twee functies in één keer schrijven door van het aantal array elementen een template
parameter te maken. Er zijn dan (in je gecompileerde programma) nog steeds twee functies, maar je
hoeft maar 1 keer een functie template te schrijven.

```cpp
#include <iostream>
#include <array>

template< unsigned int N >
void print( const std::array< int, N > & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}

int main(){
    std::array< int, 2 > a2 = { 1, 2 };
    std::array< int, 4 > a4 = { 5, 6, 7, 8 };
    print( a2 );
    print( a4 );
}
```

**De array size als template parameter 04-22**

Je kan nog een stapje verder gaan: er zijn nog andere dingen dan een array<> die je met een `for( : )`
loop kan doorlopen. Je kan je print functie heel algemeen maken door ieder type te accepteren als
parameter, en dan maar te hopen dat je die kan doorlopen.

```cpp
#include <iostream>
#include <array>

template< typename T >
    void print( const T & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}

int main(){
    std::array< int, 2 > a2 = { 1, 2 };
    std::array< int, 4 > a4 = { 5, 6, 7, 8 };
    print( a2 );
    print( a4 );
}
```

**Het ‘array’ type als template parameter 04-23**

Voor het geval dat het type van een functie parameter een typename template is bestaat er een
verkorte notatie: je kan het type van die functie parameter als auto opgeven.

```cpp
void print( const auto & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}
```

**Een ‘auto’ functie parameter 04-24**

In beide gevallen (`template< typename T >` en `auto`) krijg je een foutmelding in de print functie als
je `print()` aanroept met iets dat niet geschikt is voor een `for( : )` loop. In dit geval meldt de compiler
dat hij, om een `for( : )` loop te kunnen maken, iets moet hebben dat een `begin()` functie heeft (een
`std::array<>` heeft dat). De `a` heeft die niet, vandaar de foutmelding. Om uit te zoeken waarom die `a`
geen `begin()` heeft moet je terugzoeken wat die a eigenlijk is. Daartoe kan je kijken naar de plek waar
de template werd geïnstantieerd (de `print( 5 )` aanroep), of naar de template parameter [with auto:1
= int]. Zoals al gezegd, templates zijn krachtige dingen, maar als er iets mis gaat is het vaak lastig om
uit te vinden wat precies de oorzaak is.

> In C++ 2020 komt naar alle waarschijnlijkheid een nieuwe feature (concepts) waarmee je kan aangeven
> wat je als template vereist van een template parameter. Daarmee kan de compiler een betere foutmelding geven,
> op de plek waar het template wordt aangeroepen (i.p.v. binnen de template, op de plek waar het wordt
> gebruikt). In GCC kan je deze feature al (beperkt) gebruiken, maar dit valt buiten de scope van deze cursus.

```cpp
void print( const auto & a ){
    for( const auto & x : a ){
        std::cout << x << "\n";
    }
}

int main(){
    print( 5 );
}

main.cpp: In instantiation of 'void print(const auto:1&) [with auto:1 = int]':
main.cpp:11:13: required from here
main.cpp:5:4: error: 'begin' was not declared in this scope
for( const auto & x : a ){
^~~
```

**Compiler error bij een template functie 04-25**

De `std::array<>` heeft behalve de beide `[]` operatoren ook twee `at()` functies, die de index checken
en een exception genereren als de index ongeldig is. In onderstaand voorbeeld gebeurt dit dus op de
laatste regel van main().

```cpp
#include <iostream>
#include <array>

int main(){
    std::array< double, 9 > a;
    a[ 1 ] = 17.3;
    std:: cout << a[ 1 ] << "\n";
    a[ -1 ] = 0.0;
    std:: cout << a[ -1 ] << "\n";
    std:: cout << a.at( -1 ) << "\n";
}
```

**std::array 04-03**

## Klasse template

Het zou handig zijn om een array te hebben dat iedere keer dat een element wordt gebruikt de
index checkt. In C++ kan je dit zelf maken door het gebruik van templates en de speciale operator `[]`.

De volgende klasse template heeft twee template parameters: een type en een aantal.

De klasse heeft als attribuut een array van dat aantal elementen van dat type.
De methoden zijn volledig in de klasse body opgenomen.
Dit is helaas verplicht bij templates, omdat de compiler om de template te
kunnen instantiëren de volledige uitwerking van alle methoden nodig heeft. 

Templates staan dus altijd helemaal in de .hpp file.

> In modern C++ zie je steeds vaker libraries die gebaseerd zijn op templates en (daarom) ‘header only’ zijn.

```cpp
template< typename T, int N >
class my_array {
    public:
        T operator[]( int i ) const {
        check( i );
            return a[ i ];
        }
        T & operator[]( int i ){
            check( i );
            return a[ i ];
        }
    private:
        std::array< T, N > a;
        void check( int i ){
            if (( i < 0 ) || ( i >= N )){
                std::cout << "HELP!\n";
                while( true ){}
            }
        }
};
```

**Een DIY array met range checks in de [] operators 04-40**

De `check()` methode controleert of de index binnen de grenzen valt. Daarbij kan gebruik gemaakt
worden van de template parameter `N`, want voor een gegeven instantiering van dit template ligt `N`
vast. Als de index niet binnen de grenzen valt schrijft `check()` een melding naar `std::cout` en hangt
het programma op door een eeuwige lus binnen te gaan.

> Een beter keuze zou zijn om hier een exception te genereren, maar dat wordt pas in V2CPSE2 behandeld.

Naast de door de compiler gegenereerde methoden (default constructor, copy constructor,
assignment, destructor) heeft de klasse twee `operator[]` methoden die sterk op elkaar lijken.

De `operator[]` is de methode die wordt aangeroepen als je het object als array gebruikt.
Een verschil tussen de twee methoden is het const keyword van de eerste net voor de `{`.

Het effect hiervan is dat deze methode kan werken op een constant object, en aangeroepen zal worden als de [] operator
wordt gebruikt op een const object. Deze methode geeft een `T` waarde ‘by value’ terug.

De tweede methode wordt gebruikt als de array notatie wordt gebruikt op een niet-const object.

Deze methode geeft een `T` object terug ‘by reference’. Een reference kan net als een waarde aan de
rechterkant van een assignment gebruikt worden, maar kan ook aan de linkerkant van een
assignment staat. Via deze methode kan een element van een (niet-const) array niet alleen worden
gelezen maar ook geschreven, want als er naar de reference die de `operator[]` teruggaf wordt
geschreven dan wordt er in feite naar het gerefereerde object, dus naar het array element,
geschreven.

```cpp
int main(){
    my_array< double , 9 > a;
    a[ 1 ] = 17.3;
    std:: cout << a[ 1 ] << "\n";
    a[ -1 ] = 0.0;
}
```

**Foutmelding als je buiten de array grenzen gaat 04-40**

## Specialisatie

Ons array template gebruikt als implementatie een `std::array<>` van de elementen.

```cpp
template< typename T, unsigned int N >
class my_array {
    public:
        T operator[]( int i ) const {
            return a[ i ];
        }
    private:
        std::array< T, N > a;
};
```

**Het std::array<> waar de waarden in worden opgeslagen 04-40**

Als het template argument bool is, resulteert dat in een array van bool. Iedere bool neemt 1 byte in
beslag (want een variabele of array element kan niet kleiner zijn dan 1 byte). Een array van bool is
dus nogal inefficiënt, want in een byte kunnen 8 bits opgeslagen worden, waarvan we er maar 1 gebruiken.

```cpp
std::array< int, 10 > int_10;
std::cout << "size of int_10 = " << sizeof( int_10 ) << "\n";
std::array< bool, 10 > bool_10;
std::cout << "size of bool_10 = " << sizeof( bool_10 ) << "\n";
```

**Omvang van arrays 04-10**

Om dit aan te pakken kunnen we een specialisatie van ons algemene array template maken, speciaal
voor bool. Deze versie is zelf een template, maar met maar 1 template parameter

```cpp
// hiervoor staat de generieke array template
// array template speciaal voor bool arrays
template< unsigned int N >
class my_array< bool, N > {
    public:
        bool operator[]( int i ) const {
        return ( a[ i / 8 ] >> ( i % 8 ) ) & 0x01;
        }
        private:
        std::array< uint8_t, ( N + 7 ) / 8 > a;
};

. . .

array< int, 10 > int_10;
std::cout << "size of int_10 = " << sizeof( int_10 ) << "\n";
array< bool, 10 > bool_10;
std::cout << "size of bool_10 = " << sizeof( bool_10 ) << "\n";
```

**Template specializatie voor bool 04-51**

Deze versie wordt nu alleen gebruikt als er als type bool wordt opgegeven. Voor andere typen wordt
‘teruggevallen’ op het algemene template.

## Proxy pattern

Overigens zit bij deze implementatie van een bool array nog een adder onder het gras: hoe
implementeer je de `operator[]` die je links van de assignment kan gebruiken?

De losse bitjes in het `unsigned char` array hebben geen individueel adres,
dus je kan er geen pointer naar creëren en (dus) ook geen reference.

De `std::array` heeft om deze reden geen ruimte-efficiënte specialisatie voor `bool`.\
In de standaard library zit echter een `std::vector<bool>`, die die wel ruimte-efficiënt is.

Het probleem van de `operator[]` wordt hier opgelost doordat die operator geen `bool &` teruggeeft, maar
en object van het speciale type `vector<bool>::reference`. Dit type implementeert een `operator=`, die
er voor zorgt dat de toegekende waarde wordt opgeslagen in de juiste bit van de `std::vector<bool>`.

Voor onze `my_array<bool>` zouden we dit als volgt kunnen realiseren. Eerst schrijven we `get()` en
`set()` functies die de array elementen (de individuele bitjes) benaderen. De `operator[] const` is
triviaal: die roept gewoon get() aan.

```cpp
template< unsigned int N >
class array< bool, N > {
    public:
        bool get( int i ) const {
            return (( a[ i / 8 ] >> ( i % 8 ) ) & 0x01 ) != 0;
        }
        void set( int i, bool b ){
            if( b ){
                a[ i / 8 ] |= ( 0x01 << ( i % 8 ));
            } else {
                a[ i / 8 ] &= ~ ( 0x01 << ( i % 8 ));
            }
        }
    private:
    bool operator[]( int i ) const {
        return get( i );
    }
    // hier komt de reference klasse

    unsigned char a[ ( N + 7 ) / 8 ];
};
```

**Get en set functies 04-61**

De `operator[]` (zonder const) moet een object (een zgn. proxy) teruggeven waaraan een bool
geassigned kan worden, dus die klasse moet een assignment operator hebben die een bool
accepteert en zorgt dat die bool op de juiste plek in de array terecht komt.

Dit kan via de `set()` operator, maar dan moet het object dus wel de beschikking hebben over het array object,
en de index. Die beide dingen moeten we dus aan de constructor van de reference klasse meegeven en in
het proxy object opslaan.

```cpp
class reference {
    private:
        array & subject;
        int n;
    public:
        reference( array & subject, int n ): subject( subject ), n( n ){}

        reference & operator=( bool b ){
            subject.set( n, b );
            return *this;
            operator bool(){
                return subject.get(n );
            }
        }

        reference operator[]( int i ){
            return reference( *this, i );
        };
}
```

**Een proxy voor het benaderen van een enkel bitje 04-61**

Tot slot moeten we zo’n `reference` object ook aan de rechterkant van een statement kunnen
gebruiken, als `bool` waarde. Om dit mogelijk te maken is er de operator `bool()`. 

Omdat de naam van deze operator een type is, is dit is een conversie operator voor conversie naar dat type.

Als een proxy object wordt gebruikt op een plek waar een bool vereist is, dan wordt automatisch deze
conversie aangeroepen.

Proxy objecten worden in allerlei situaties gebruikt om de illusie te scheppen dat een object
‘gewoon’ beschikbaar is, terwijl er in werkelijkheid dingen gedaan moeten worden om het object te
gebruiken. Een proxy verbergt dit voor zijn gebruiker.

Er is hier alleen het allereenvoudigste gebruik van templates beschreven.

Templates vormen een programmeertaal op zich, die in complexiteit kan wedijveren met de rest van C++.

Dit heeft geleid tot een (erg moeilijk leesbare) stijl van C++ programmeren die ‘template metaprogramming’
wordt genoemd: het gebruik van templates om tijdens het compileren dingen te berekenen.
