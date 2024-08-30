#include <iostream>

// Basisstructuur met een virtuele foo() functie
class Base {
public:
    virtual void foo() {
        std::cout << "Base::foo() - should never be called" << std::endl;
    }
};

// Classes om te testen, waarbij een class foo() heeft en de andere niet
class WithFoo : public Base {
public:
    void foo() override {
        std::cout << "WithFoo::foo()" << std::endl;
    }
};

class WithoutFoo : public Base {
    // No foo() function in this class
};

// Functie die foo() aanroept als het object een foo() methode heeft
void callFooIfExists(Base* obj) {
    // Dynamisch casten naar een WithFoo pointer
    WithFoo* derived = dynamic_cast<WithFoo*>(obj);
    if (derived) {
        // Als de cast succesvol is, dan wijst obs naar een WithFoo object en heeft het object een foo() methode
        derived->foo();
    } else {
        // Anders heeft het object geen foo() methode
        std::cout << "No foo() method available." << std::endl;
    }
}

int main() {
    WithFoo a;
    WithoutFoo b;

    callFooIfExists(&a); // Dit zou "WithFoo::foo()" moeten afdrukken
    callFooIfExists(&b); // Dit zou "No foo() method available." moeten afdrukken

    return 0;
}
