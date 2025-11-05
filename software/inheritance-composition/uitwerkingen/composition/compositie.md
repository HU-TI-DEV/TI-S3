## Compositie en Aggregatie in C++ </br>

> Datum : 05/11/2025 </br>
> Kort : Taak verdeling document </br>
> [Opdracht Bron](https://github.com/HU-TI-DEV/TI-S3/blob/main/software/inheritance-composition/README.md)
---
| Onderzoekers | Schrijvers | Presentatoren | Github |
|--------------|------------|---------------|--------|
| Vigo         | Emma       |               | Tess   |
| Luuk         | Erin       |               | Sarah  |
| Alea         | Jente      |               | Ryan   |
| Jorn         | Amira      |               | Joni   |
| Nathaniel    | Maud       |               | Ruben  |
| Laurens      |            |               |        |
| Ying         |            |               |        |

### Inhoudsopgave
---
1. Object Composition in c++, de grote lijnen.
2. Types Object Composition.
3. Voor en nadelen.
4. Implementatie voorbeelden.
5. Waar gaat het vaak fout?
6. Bronnen vermelding.
---

### Object Composition in C++, de grote lijnen
---
**Compositie:**<br>
*Compositie in C++ is wanneer een klasse is opgebouwd uit één of meer objecten van andere klassen.<br>*

Het vertegenwoordigt een *“has a”* relatie, waarbij de bijbehorende klasse de eigenaar is van die objecten.<br>
Dit betekent dat wanneer de behorende klasse buiten scope gaat (of wordt vernietigd), de bijbehorende lid objecten ook automatisch worden vernietigd.

**Bijvoorbeeld:**<br> Stel dat je een `Deur-klasse` en een `Raam-klasse` hebt, en beide zijn member variables van een `Huis Klasse`. Wanneer een instantie van de `Huis klasse` wordt aangemaakt, worden ook de `Deur-` en `Raam-objecten` aangemaakt. <br>
Wat voor het aanmaken van de instantie geldt, geldt ook voor het vernietigen. Dus als het `Huis-object` wordt vernietigd (bijvoorbeeld wanneer het buiten scope gaat), worden ook de `Deur-` en `Raam-objecten` vernietigd.

*Voorbeeld code:*
```cpp
class Engine {
  // Class members and methods
};

class Car {
  Engine engine;
  // Class members and methods
};
```


**Object composition** wordt voornamelijk gebruikt voor grotere projecten, waar men te maken heeft met veel verschillende objecten, die ook weer gebruikt moeten worden elders. Er zijn meerdere manieren om dit aan te pakken, dus dan spreken we over **compositie types**. 

<br>

**Aggregatie:**<br>
*Aggregatie in C++ is wanneer een klasse is samengesteld uit objecten van andere klassen, maar de hoofdklasse is niet de eigenaar van de member variables.*<br>

De member variable kunnen **onafhankelijk** bestaan van de hoofdklasse.
Dit wordt meestal bereikt door pointers of referenties naar de member variable te gebruiken.
Daarom kunnen de member variable blijven bestaan wanneer de hoofdklasse wordt vernietigd of buiten scope gaat. Dit is dus een verschil tussen compositie en aggregatie.

*Voorbeeld code:*
```cpp
class Employee {
  // Class members and methods
};

class Department {
  std::vector<Employee*> employees;
  // Class members and methods
};
```

### Types Object Composition
---

### Voor- en nadelen van aggregratie en compositie
---
#### Voordelen van compositie:
- **Flexibiliteit** </br>
    Compositie is een stuk flexibeler dan overerving. Dit is omdat je het gedrag van een object kunt veranderen, zelfs tijdens runtime. Dit doe je door de samenstellende objecten te vervangen. 

- **Complexiteit verbergen** </br>
    Je kan met gebruik van compositie complexiteit verbergen achter het simpele vaandel van objecten, wat onderhoud simpel houdt.

- **Losser verband** </br>
    Waar overerving klassen heel sterk koppelt, biedt compositie een losser verband. Hierdoor is het veiliger om de onderliggende klassen individueel aan te passen zonder de hoofdklasse negatief te beïnvloeden.


#### Nadelen van compositie:
- **Verkeerd gebruik** </br>
    Als compositie verkeerd gebruikt word, dan kan het juist meer problemen veroorzaken dan wat het oplost. Het kan leiden tot een ingewikkelde structuur die moeilijk te begrijpen en uit te leggen is. Je moet wel weten wat je doet als je compositie in je code wilt gaan gebruiken.

- **Levenscyclus en relaties** </br>
    Het beheren van de verschillende levenscyclussen en relaties tussen meerdere samengestelde objecten kan soms uitdagend zijn. Hierdoor is overerving soms toch een betere keuze, als je hier zelf beter in bent.

#### Voordelen van aggregratie:
- **Hergebruik**
    Het zorgt ervoor dat klassen makkelijk te hergebruiken zijn, omdat je ze definiëert als elementen in andere klassen. Dit maakt de code meer herbruikbaar.

- **Relatie tussen klassen**
    Het creëert een relatie tussen klassen die ervoor zorgt dat objecten van verschillende klassen kunnen samen werken, zonder rekening te hoeven houden met een strikte hiërarchie. Dit zorgt voor flexibiliteit.

- **Modelleren van complexere systemen**
    Aggregratie helpt met het modelleren van complexere systemen, omdat het duidelijke relaties tussen objecten definiëert. Dit maakt het makkelijker te modelleren omdat je een goed overzicht behoudt.

- **Flexibiliteit**
    Aggregratie is ook flexibel omdat objecten kunnen bestaan, ook als het aggregerende object niet bestaat. De levensduur van het geaggregeerde object is onafhankelijk van de levensduur van het aggregerende object. 

#### Nadelen van aggregratie:
- **Complexiteit**
    Als er veel geaggregeerde componenten zijn, die zelf ook nog eens complex zijn, kan het erg complex en moeilijk te begrijpen worden.

- **Niet hiërarchisch**
    Aggregatie bouwt geen hiërarchisch verband op, terwijl dit voor sommige mensen fijn kan zijn met modelleren.

- **Onnodige koppelingen**
    Het kan ervoor zorgen dat er onnodige koppelingen komen tussen klassen, waardoor een aanpassing aan één klas ook de andere klassen ongewenst kan beïnvloeden.

### Implementatie voorbeelden
---
### Implementatie voorbeelden
**Voorbeeld 1: Basis klasse compositie**

``` cpp
#include <iostream>

class Engine {
public:
    void start() {
        std::cout << "Engine started";
    }
};

class Car {
private:
    Engine engine;  // Car has an Engine
public:
    void start() {
        engine.start();               // Start the engine first
        std::cout << " Car started";
    }
};

int main() {
    Car myCar;
    myCar.start();  // Outputs: Engine started Car started
    return 0;
}
```
[*Bron voorbeeld 1*](https://codesignal.com/learn/courses/diving-into-cpp-classes/lessons/classes-composition-in-cpp) <br><br>
In dit voorbeeld heeft de klasse ```Car``` het object ```Engine```. 

**Voorbeeld 2: Geavanceerde klasse compositie**
```cpp
class Car {
private:
    Engine engine;
    Wheel wheels[4];  // Composition with multiple instances of a component
public:
    // Constructor initializes Engine and Wheel objects
    Car(int hp, int ws) : engine(hp), wheels{Wheel(ws), Wheel(ws), Wheel(ws), Wheel(ws)} {}

    void displaySpecifications() const {
        std::cout << "Engine: " << engine.getHorsepower() << " HP\n";
        std::cout << "Wheel size: " << wheels[0].getSize() << " inches\n";
    }
};

int main() {
    Car myCar(300, 18);
    myCar.displaySpecifications();  // Outputs: Engine: 300 HP \n Wheel size: 18 inches
    return 0;
}
```
[*Bron voorbeeld 2*](https://codesignal.com/learn/courses/diving-into-cpp-classes/lessons/classes-composition-in-cpp) <br><br>
In dit voorbeeld heeft de klasse ```Car``` het object ```Engine``` en een array van vier ```Wheel``` objecten. In de contructor van ```Car``` worden ```Engine``` en ```Wheel``` geÃ¯nitialiseerd.

**Voorbeeld 3: Aggregatie**
```cpp
#include <iostream>
#include<string.h>
using namespace std;

class Tech{
    public:
        int house;
        string city, state;
        Tech(int house_no, string city, string state)
        { this->house = house_no;
        this->city = city;
        this->state = state;}
};


class Person{
    private:
        Tech* address;
    public:
        string name;
        Person(string name, Tech* address){
            this->name = name;
            this->address = address;}

    void display(){
        cout<< name<< " "<< " "<< address->house<<" "<<address->city<< " "<<address->state<<endl;}
    };


int main(void) {
    Tech add1= Tech(112 ,"Bandra","Mumbai");
    Tech add2 = Tech(222, "Jahanpanah","New Delhi");
    Person p1 = Person("Raj",&add1);
    Person p2 = Person("John",&add2);
    cout << "Name of the Person" << " and " << "Address"<< endl<<endl;

    p1.display();
    p2.display();

    return 0;
}

```
[*Bron voorbeeld 3*](https://techvidvan.com/tutorials/cpp-aggregation/)
<br><br>
In het bovenstaande voorbeeld bevat de object klasse ```Tech``` variabele zoals ```House```, ```City```en ```State```. De ```Person``` klasse heeft een instantie variabele die de naam van de persoon verteld. Het heeft ook een pointer variabele naar```Tech* address```.

### Waar gaat het vaak fout?
---
#### Compositie
Waar het vaak fout gaat met compositie is dat de volgorde waarin je definities in je klasse defined de manier is hoe het programma uitgevoerd wordt. Wanneer je een andere volgorde aanhoudt in je constructor (initializer list), dan wordt het overschreven. Dit zorgt voor errors in je compiler en onverwacht gedrag in je code.

Een ander probleem ontstaat wanneer een samengestelde objecten gebruikt die dynamisch geheugen gebruiken. Als je namelijk pointers of referenties gebruikt dat worden deze gekopieerd zonder dat de locatie waarnaar gewezen gekopieerd wordt. Wanneer je dat het object originele object verwijderd worden beide pointers of referenties verwijderd wat kan zorgen voor errors, crashes of memory leaks.

#### Aggregatie
Aggregatie wordt vaak gebruikt door middel van pointers of referenties, wanneer je het object verwijderd, maar de pointers laat staan dan krijg je pointers of referenties die nergens meer naar verwijzen.

Aggregatie heeft ook geen eigenaarschap op een object, dit zorgt ervoor dat een object meerdere keren verwijderd of op dezelfde manier aangepast kan worden. Omdat er geen eigenaarschap bestaat is er ook een kans dat een object nooit wordt opgeruimd, dit zorgt uiteindelijk (als dit vaak genoeg voorkomt) voor een memory leak. 

### Bronnen vermelding
---
### Bronvermelding

- [Composition and Aggregation](https://www.youtube.com/watch?v=pDlEvmawN9g)

- [Composition vs inheritance](https://www.adservio.fr/post/composition-vs-inheritance#:~:text=The%20difference%20between%20inheritance%20and,class%2C%20thus%20breaking%20your%20code.)

- [Composition | Evolved](https://evolved-cpp.netlify.app/d-object-oriented-programming/04-composition/#association-composition-and-aggregation)

- [Composition voorbeelden](https://codesignal.com/learn/courses/diving-into-cpp-classes/lessons/classes-composition-in-cpp)

- [Aggregatie voorbeeld](https://techvidvan.com/tutorials/cpp-aggregation/)

- [Aggregatie vs Inheritance (voordelen/nadelen)](https://gyansanchay.csjmu.ac.in/wp-content/uploads/2023/02/Aggregation.pdf)

- [Waarschuwingen over het gebruik van aggregatie](https://techvidvan.com/tutorials/cpp-aggregation/)

- [Foutmelding met compositie](https://stackoverflow.com/questions/12222417/why-should-i-initialize-member-variables-in-the-order-theyre-declared-in)

- [Shallow copy (compositie)](https://www.geeksforgeeks.org/cpp/shallow-copy-and-deep-copy-in-c/)

- [Six different Kinds of Composition](https://www.conradbock.org/compkind.html)

- [What is aggregation and composition](https://www.conradbock.org/compkind.html)

- [Stack difference between aggregation and composition](https://stackoverflow.com/questions/885937/what-is-the-difference-between-association-aggregation-and-composition)