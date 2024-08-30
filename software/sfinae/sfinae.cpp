// Primer
// Uitleg van decltype met voorbeeld:
    // int a = 5;
    // double b = 3.14;
    // // De comma-operator evalueert beide expressies, maar decltype geeft het type van de tweede expressie terug
    // decltype(a = 10, b) c; // c krijgt het type van b, wat een double is

#include <iostream>

// Struct om te controleren of een type een lidfunctie 'foo()' heeft
template <typename T>
class has_foo {
private:
    // Deze functie overload wordt gekozen als T een lidfunctie 'foo()' heeft
    // Dus als U een pointer is naar een object met een foo functie, dan 
    // compileert ptr->foo() en wordt std::true_type() teruggegeven.
    
    // Zo niet, dan crasht de compilatie niet (vanwege SFINAE regels in c++),
    // wordt deze overload niet gekozen, en zoekt de compiler naar een andere overload.

    // std::true_type() is een type dat bij meta-programming gebruikt om true te representeren.
    // Zijn static member genaamd "value" is een boolean met waarde true: 
    // static constexpr bool value = true.

    template <typename U>
    static auto test(U* ptr) -> decltype(ptr->foo(), std::true_type());

    // Deze functie overload wordt gekozen als de eerste overload niet werkt.
    // In dit geval retourneert de functie test een std::false_type() object, 
    // met ::value == false.
    template <typename U>
    static std::false_type test(...);

public:
    // Onderstaand krijgt compile-time een bool constante een waarde 
    // die aangeeft of de eerste overload is gekozen.
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

// Classes om te testen, waarbij een class foo() heeft en de andere niet
class WithFoo {
public:
    void foo() {
        std::cout << "WithFoo::foo()" << std::endl;
    }
};

class WithoutFoo {
    // No foo() function in this class
};

// Functie die wordt aangeroepen als het type een 'foo()' functie heeft
// NB: het return type van de functie is std::enable_if<has_foo<T>::value>::type
// in geval has_foo<T>::value == true, in dat geval is std::enable_if<has_foo<T>::value>::type
// gelijk aan void, een geldig return type voor de functie, waardoor de functie gecompileerd wordt.
// Zo niet, dan is std::enable_if<has_foo<T>::value>::type niet gedefinieerd, 
// zoekt de compiler naar een andere overload.
template <typename T>
typename std::enable_if<has_foo<T>::value>::type
callFooIfExists(T& obj) {
    obj.foo();
}

// Functie die wordt aangeroepen als het type GEEN 'foo()' functie heeft
template <typename T>
typename std::enable_if<!has_foo<T>::value>::type
callFooIfExists(T&) {
    std::cout << "No foo() method available." << std::endl;
}

int main() {
    WithFoo a;
    WithoutFoo b;

    callFooIfExists(a); // Dit zou "WithFoo::foo()" moeten afdrukken
    callFooIfExists(b); // Dit zou "No foo() method available." moeten afdrukken

    return 0;
}
