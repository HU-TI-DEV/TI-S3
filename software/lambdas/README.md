# C++ Lambda's <!-- omit in toc -->

* Bron: V2CPSE2 reader, TI, HU.nl
* Voorbeelden: [v2cpse2-examples](https://github.com/HU-TI-DEV/v2cpse2-examples)

Behandelde begrippen en technieken:

- Data-driven programming
- Lambda’s
- Capture
- function-wraps-class truc
- std::function

## Data-driven programming

In een vorig programma bevatte de main() een reeks if-statements die reacties op verschillende toetsen afhandelden.

```cpp
int main(){
   . . . 
   while( window.isOpen() ){

      if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )){
         my_ball.move( sf::Vector2f{ -1, 0 } );
      }
      if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )){
         my_ball.move( sf::Vector2f{ +1, 0 } );
      }
      if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )){
         my_ball.move( sf::Vector2f{ 0, -1 } );
      }
      if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )){
         my_ball.move( sf::Vector2f{ 0, +1 } );
      }
      if( sf::Mouse::isButtonPressed( sf::Mouse::Left )){
         my_ball.jump( Vector2f_from_Vector2i( sf::Mouse::getPosition( window )));
      }

      . . .
}
```

**Een keten van if-statements voor het afhandelen van de cursor toetsen**

Een reeks van vier vrijwel gelijke if-statements is nog wel leesbaar, maar als het er bijvoorbeeld 10 zijn dan kun je beter gebruik maken van wat ‘data driven programming’ wordt genoemd: breng de variatie die er is onder in data en ‘interpreteer’ die in bijvoorbeeld een `for(:)` lus.

Als het aantal acties toeneemt, wordt deze versie snel leesbaarder dan de versie met losse if’s, ook al omdat de lijst met acties buiten de main loop geplaatst kan worden.

```cpp
const struct { 
   sf::Keyboard::Key key; 
   float x; float y; 
} actions[] = {
   { sf::Keyboard::Left,  -1.0,  0.0 },
   { sf::Keyboard::Right, +1.0,  0.0 },
   { sf::Keyboard::Up,     0.0, -1.0 },
   { sf::Keyboard::Down,   0.0, +1.0 }
};

. . .

for( auto& action : actions ){
   if( sf::Keyboard::isKeyPressed( action.key )){ 
      b.move( sf::Vector2f{ action.x, action.y } );
   }
}
```

**Aparte lijst met acties, buiten de main (zie `03-01 main.cpp`)**

Merk op dat we nergens hoeven aan te geven hoeveel acties er zijn, dus daar kunnen we ook geen fout in maken. De omvang van de array wordt bepaald door het aantal initialisatie elementen. Het aantal iteraties van het `for( : )` statement wordt weer bepaald door de omvang van de array.

Een nadeel van het gebruikte `actions` type is dat we beperkt zijn in wat we kunnen opgeven als trigger (een toets die is ingedrukt) en als actie (het verplaatsen van de bal met een bepaalde waarde voor de x en y richtingen). Daar kunnen we wat aan doen door lambda’s te gebruiken.

## Lambda’s

Voor wat meer flexibiliteit kunnen we gebruik maken van lambda’s. Een lambda in C++ is een functie die op de plaats van een expressie geschreven wordt, en als functie parameter kan worden doorgegeven, of in een variabele kan worden opgeslagen.

Een lambda begint met
- Een **capture clause** (de [ ] haakjes en wat daartussen staat),
- gevolgd door een (optionele!) **parameter lijst**,
- en als laatste de lambda **body**.

De parameter lijst en de body zijn hetzelfde als bij een functie.
Het is niet nodig het return type aan te geven.
De compiler bepaalt dit aan de hand van de return-statements in de body. 
Je kunt ook een expliciet return-type aangeven, maar dan moet dit met de ‘trailing return type’ syntax.  

De capture clause kun je niet weglaten, zelfs niet als die leeg is, want die [ ] haakjes geven aan dat wat volgt een lambda is.

Het type van een lambda object  is ‘verborgen’: iedere lambda heeft een ander type, zelfs als de parameter lijst, return type en body precies hetzelfde zijn. Als je een lambda wil opslaan in een variabele dan kan dit door `auto` te gebruiken, maar je kunt aan die variabele nooit een andere lambda toekennen, want iedere lambda is een ander type, ook al zien ze er precies hetzelfde uit.

```cpp
    // lambda's without parameters, returning void
    auto empty_void_lambda_1 = [](){};
    auto empty_void_lambda_2 = []()->void {};
    auto empty_void_lambda_3 = []{};

       // error: each lambda is a different type
       empty_void_lambda_1 = [](){};

       // lambda’s incrementing their parameter, returning int
    auto increment_1 = []( int & n )         { return ++n; };
    auto increment_2 = []( int & n )->int    { return ++n; };

       // idem, returning double
    auto increment_3 = []( int & n )->double { return ++n; };
    auto increment_4 = []( int & n )         { return 0.0 + ++n; };
```

**Lambda voorbeelden (zie `03-02`)**

Als je een lambda wil meegeven aan een functie dan kan dat door het type van de lambda als (impliciete) template parameter door te geven.
Je hoeft de lambda dan niet eerst op te slaan in een variabele (maar dat mag wel): lambda’s worden meestal aangemaakt in een functie aanroep (anders had je bijna net zo goed een losse functie kunnen schrijven). 
Je moet natuurlijk wel zorgen dat de echte lambda die je meegeeft past bij hoe de lambda parameter in de functie wordt aangeroepen.
Doe je dit fout, dan krijg je een foutmelding op de plaats waar de lambda in de template op een verkeerde manier wordt aangeroepen.

```cpp
template< typename T >
void pass_a_lambda( T lambda ){
   lambda();
}

// or: void pass_a_lambda( auto lambda ){ lambda(); }

empty_void_lambda_1();
pass_a_lambda( empty_void_lambda_1 );

pass_a_lambda( []{} );

// error at the lambda() call in the pass_a_lambda function
pass_a_lambda( []( int x ){} );
```

**Een lambda als een functie parameter (zie `03-02`)**

## Class template parameter deduction

Als je een lambda wil meegeven aan de constructor van een klasse om hem daarna in het object op te slaan, dan moet het type van de lambda een template parameter van de klasse zijn (dus niet van de constructor).
In oudere C++ versies (voor C++14) was dit lastig. Vanaf C++14 kan het type van een klasse template parameter gededuceerd worden uit het type van een constructor parameter.

```cpp
template< typename T >
class store_a_lambda_class {
private:
   T lambda;

public:

   store_a_lambda_class( T lambda ): 
      lambda( lambda ) 
   {}

   void run(){ 
      lambda(); 
   }
};

// the class template parameter is deduced from the constructor parameter
// requires in C++17
auto store1 = store_a_lambda_clas( []{} );
store1.run();

// this does not work because the two lambda's have a different type
auto store2 = store_a_lambda_class< decltype(empty) >( []{} );
```

**Klasse template parameter deductie (vanaf C++17, zie `03-03`)**

Voor C++14 moest je een truc toepassen: in plaats van de constructor direct aan te roepen, roep je een functie aan (functie template parameters konden altijd al gededuceerd worden), en binnen die functie roep je de constructor van de klasse aan.

```cpp
template< typename T >
store_a_lambda_class< T > store_a_lambda( T lambda ){
   return store_a_lambda_class< T >( lambda );
}

auto store3 = store_a_lambda( empty_void_lambda_1 );
store3.run();

auto store4 = store_a_lambda( []{} );
store4.run();
```

**Function – wraps – constructor (C++14 en ouder, zie `03-03`)**

## std::function

Iedere lambda is een uniek type, dus je kunt niet zomaar lambda’s opslaan in een variabele die je creëert met het type van een lambda.

Dit kan wel in `std::function`. Dit is een (template) class waarin je lambda’s van een specifieke signatuur  kunt opslaan.

Je moet als template parameter de signatuur opgeven.
Die ziet eruit als een functie header, maar zonder de functienaam en zonder parameternamen.
Aan zo’n variabele kun je dus een lambda (van die signatuur) toekennen.

```cpp
#include <functional>

std::function< int(int) > f;

f = []( int x ){ return x; };
std::cout << "identy " << f( 5 ) << "\n";

f = []( int x ){ return 1 + x; };
std::cout << "next " << f( 5 ) << "\n";

f = []( int x ){ return 2 * x; };
std::cout << "double " << f( 5 ) << "\n";
```

**std::function (zie `03-04`)**

De capture clause van een lambda bepaalt hoe de lambda omgaat met variabelen die gedefinieerd zijn in de functie waar de lambda is gecreëerd, maar binnen de lambda body worden gebruikt.
De keuze is, net als bij functie parameters: **by-value** of **by-reference**.
By-value betekent in dit geval automatisch by const value.
Als je niets aangeeft, dan kun je binnen de lambda geen variabelen van zijn ‘omringende’ functie gebruiken.

Je kunt per variabele specificeren of je die by-value of by-reference wilt gebruiken met respectievelijk de naam, of & gevolgd door de naam, met een komma tussen de verschillende specificaties.
Dat ziet er dus ongeveer uit als een parameter lijst, maar zonder de parameter typen (de compiler weet de naam, dus hij kan het type opzoeken).
Met een losse `&` als eerste kun je aangeven dat de default (voor namen die je niet expliciet noemt) by reference is. Met `=` kun je aangeven dat de default by (const) value is.

```cpp
// std::cout is global, so you can use it without capturing
auto here = [](){ std::cout << __FILE__ << ":" << __LINE__ << "\n"; };
here();

// line is in the enclosing function, so you must capture it, 
// either by copy or by reference, either individually or collectively
int line = __LINE__;
[ & ]()   { std::cout << __FILE__ << ":" << line << "\n"; }();
[ &line ] { std::cout << __FILE__ << ":" << line << "\n"; }();
[ = ]()   { std::cout << __FILE__ << ":" << line << "\n"; }();
[ line ]  { std::cout << __FILE__ << ":" << line << "\n"; }();

// error: line is not accessible in the lambda
[]{ std::cout << __FILE__ << ":" << line; }();
```

**Capture (zie `03-05`)**

Als je een lambda creëert in een klasse functie, dan wil je wellicht in de lambda gebruik maken van de eigenschappen van het object (de klasse functies en de klasse variabelen).
Dit kun je doen door de ‘this pointer’ (de impliciete pointer die naar het object wijst) op te vangen en expliciet in de lambda te gebruiken.

```cpp
class capture_this {
private:
   int n;

public:
   capture_this(): 
      n( __LINE__) 
   {
      auto lambda = [ this ](){ 
         this->print( this->n ); 
      };
      lambda();
   }

   void print( int x ){
      std::cout << x << "\n";
   }
};
```

**Het opvangen van de this pointer (zie `05-06`)**

Bij een capture by-reference moet je goed opletten dat je niet een variabele by-reference gebruikt die niet meer bestaat.
Met een lambda kan dit voorkomen als je de lambda opslaat in een variabele die langer leeft dan de gerefereerde variabele. Je hebt dan `Undefined Behaviour`.

```cpp
using void_void = std::function< void(void) >;

void assign_lambda( void_void & f ){
   int n = __LINE__;
   std::cout << __LINE__ << ":" << n << "\n";

   // n is captured by reference by a lambda that will live longer 
   // than n. trouble on the way!
   f = [ &n ](){ 
       std::cout << __LINE__ << ":" << n << "\n"; 
   };
}


void_void f;
assign_lambda( f );

// this function stores a lambda that uses the local variable n,
// which is no longer valid. Undefined behaviour!
f();
```

**Lambda undefined behaviour (zie `03-07`)**

## Lambda-driven programming

Met behulp van lambda’s die we opslaan in `std::function<>` objecten kunnen we de acties van het bewegende-bal programma vatten in objecten die we kunnen opslaan in een lijst.

In de main loop lopen we dan de items van die lijst door, zonder ons te bekommeren om wat daar precies in staat.

Dit kan bij een grotere applicatie heel handig zijn, want we kunnen dan (met een iets andere opzet) die acties definiëren bij de objecten waar ze betrekking op hebben, in plaats van in de main.

De main ziet er dan afgezien van de acties en het scherm object prettig kaal uit: er is eigenlijk niets meer over dat specifiek is voor de applicatie.

```cpp
int main( int argc, char *argv[] ){

    sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
    ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };

    action actions[] = { . . .  };

    while (window.isOpen()) {
       for( auto & action : actions ){
          action();
       }

       window.clear();
       my_ball.draw( window );
       window.display();

       sf::sleep( sf::milliseconds( 20 ));

          sf::Event event;  
       while( window.pollEvent(event) ){
          if( event.type == sf::Event::Closed ){
           window.close();
          }
       } 
    }

    std::cout << "Terminating application\n";
    return 0;
}
```

**Lambda-driven main (zie `03-08`)**

De acties bestaan telkens uit twee delen:
- Een conditie (bijvoorbeeld de cursor-links knop is ingedrukt)
- en wat er moet gebeuren als die conditie waar is.

Beiden kunnen we als lambda schrijven, en een action object kan die twee lambda’s opslaan als `std::function<>` objecten. De constructor krijgt de twee lambda’s mee, en slaat ze op. De `operator()` checkt of aan de conditie voldaan is. Zo ja dan wordt het werk uitgevoerd.

```cpp
class action {
private:
    std::function< bool() > condition;
    std::function< void() > work;

public:
    action(
       std::function< bool() > condition, 
       std::function< void() > work
    ) : 
          condition( condition ), 
       work( work ) 
    {}

    void operator()(){
       if( condition() ){
          work();
       }
    }
};
```

**Conditie & ‘work’ klasse (zie `03-08`)**

De constructor die we nu hebben vraagt als conditie een lambda die een bool teruggeeft. Dat is heel algemeen, maar het zou makkelijk zijn als we als conditie kunnen opgeven (‘deze knop is ingedrukt’), waarbij ‘knop’ dan een toetsenbordtoets kan zijn of een muisknop.

Dat is eenvoudig te realiseren door twee constructors toe te voegen, die als eerste parameter een toets van het betreffende type meekrijgen. Die constructor maakt dan zelf de lambda aan die de test uitvoert door de betreffende SFML-functie aan te roepen.

```cpp
// extra constructor for keyboard key presses
action(
    sf::Keyboard::Key key,
    std::function< void() > work
) :
    condition(
        [ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
    ),
    work(work)
{}

// extra constructor for mouse button presses
action(
    sf::Mouse::Button button,
    std::function< void() > work
) :
    condition(
        [ button ]()->bool { return sf::Mouse::isButtonPressed( button ); 
    ),
    work(work)
{}
```

**Extra constructors (zie `03-08`)**

Nu kunnen we de lijst met acties schrijven.

```cpp
action actions[] = {
  action( sf::Keyboard::Left,  [&]{ my_ball.move( sf::Vector2f( -1.0,  0.0 )); }),
  action( sf::Keyboard::Right, [&]{ my_ball.move( sf::Vector2f( +1.0,  0.0 )); }),
  action( sf::Keyboard::Up,    [&]{ my_ball.move( sf::Vector2f(  0.0, -1.0 )); }),
  action( sf::Keyboard::Down,  [&]{ my_ball.move( sf::Vector2f(  0.0, +1.0 )); }),
  action( sf::Mouse::Left,     [&]{ my_ball.jump( sf::Mouse::getPosition( window )); })
};
```

**Acties (zie `03-08`)**
