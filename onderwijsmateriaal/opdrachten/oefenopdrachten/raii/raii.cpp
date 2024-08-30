#include <iostream>
#include <fstream>
#include <cstdio> // Voor std::remove
#include <string>

class TempFile {
private:
    std::string filename; // Naam van het tijdelijke bestand

public:
    // Constructor die een tijdelijk bestand aanmaakt
    TempFile(const std::string& prefix) {
        // ** vul deze body zelf in **
    }

    // Destructor die het tijdelijke bestand verwijdert
    ~TempFile() {
        // ** vul deze body zelf in **
    }

    // Verwijder copy constructor en copy assignment operator
    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;

    // Functie om naar het bestand te schrijven
    void writeData(const std::string& data) {
        // ** vul deze body zelf in **
    }

    // Functie om de naam van het bestand te krijgen
    const std::string& getFilename() const {
        return filename;
    }
};

// Hoofdprogramma om de RAII-klasse te testen
int main() {
    try {
        TempFile tempFile("example"); // Maak een tijdelijk bestand aan met prefix "example"

        tempFile.writeData("Hello, RAII!"); // Schrijf data naar het bestand
        std::cout << "Temporary file is: " << tempFile.getFilename() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Het tijdelijke bestand wordt hier automatisch verwijderd door de destructor van TempFile

    return 0;
}
