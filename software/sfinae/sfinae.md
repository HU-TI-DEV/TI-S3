# SFINAE
## Inleiding
SFINAE is een geavanceerd concept dat je kunt gebruiken met c++ template programmering. Het staat letterlijk voor "Substitution Failure Is Not An Error". Dit mechanisme stelt programmeurs in staat om overloading en conditionele sjablonen te gebruiken op basis van compile-tijd logica.

Stel bijvoorbeeld dat je het volgende wilt bereiken:

```c++
class WithFoo {
public:
    void foo() {
        std::cout << "WithFoo::foo()" << std::endl;
    }
};

class WithoutFoo {
    // No foo() function in this class
};

int main() {
    WithFoo a;
    WithoutFoo b;

    callFooIfExists(a); // Dit zou "WithFoo::foo()" moeten afdrukken
    callFooIfExists(b); // Dit zou "No foo() method available." moeten afdrukken
```

Je kunt dergelijk gedrag run-time realiseren door gebruik van overerving (zie de opdracht).
Maar als je naar de code kijkt, zie je zo dat callFooIfExists(a) altijd wel foo() moet aanroepen en callFooIfExists(b) nooit. Als jij dat kunt zien, is dat een teken dat de compiler dat ook compile-time ook zelf zou moeten kunnen doen. Met wat ingewikkelde trucs, samen SFINAE genoemd, kan dat ook.

Bestudeer [deze van commentaar voorziene code](./sfinae.cpp) om een idee te krijgen van hoe het werkt.

## Voordeel van SFINAE
- Het compile-tijd nemen van beslissingen leidt tot snellere code.
## Nadeel van SFINAE
- SFINEA leidt tot moeilijk leesbare code. Pas het dus alleen toe indien echt nodig, in het meest tijdkritische deel van de code.