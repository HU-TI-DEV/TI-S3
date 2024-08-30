#include <iostream>
#include <array>
#include <cmath>

// Constante voor pi
constexpr double pi = 3.14159265358979323846;

// Functie om graden naar radialen om te zetten
constexpr double degreesToRadians(int degrees) {
    return degrees * (pi / 180.0);
}

// Eigen constexpr sinus functie met behulp van de Taylor-reeks
constexpr double constexprSin(double x) {
    double term = x;
    double result = x;
    constexpr int iterations = 10; // Aantal termen voor de Taylor-reeks
    
    // De Taylorreeks van een sinus is:
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...

    // NB: onderstaande code is een optimalisatie: elke 
    // term wordt berekend met behulp van de vorige term, waardoor
    // er minder vermenigvuldigingen nodig zijn.
    for (int i = 1; i < iterations; ++i) {
        term *= -x * x / ((2 * i) * (2 * i + 1));
        result += term;
    }

    return result;
}

// Constexpr functie om de sinuswaarden voor 0 tot 359 graden te berekenen
constexpr std::array<double, 360> generateSinTable() {
    std::array<double, 360> sinTable{};
    for (int i = 0; i < 360; ++i) {
        sinTable[i] = constexprSin(degreesToRadians(i));
    }
    return sinTable;
}

// Sinustabel gegenereerd tijdens compile-tijd
constexpr auto sinTable = generateSinTable();

// Functie om de sinuswaarde te krijgen voor een gegeven graad
double sinDegrees(int degrees) {
    return sinTable[degrees];
}

int main() {
    // Test de sinusfunctie met enkele voorbeelden
    for (int i = 0; i <= 360; i += 45) {
        std::cout << "sin(" << i << " degrees) = " << sinDegrees(i) << '\n';
    }
    return 0;
}
