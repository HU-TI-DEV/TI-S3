// by Marius Versteegen, 2023

#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Button.h>

// This file contains the code of multiple tasks that run concurrently and notify eachother using flags.

namespace crt
{
	template <int WIDTH, int HEIGHT>
	class CharMatrix {
	public:
		// Constructor: Initialiseer de matrix met een standaardteken
		CharMatrix(char initChar = ' ') {
			for (int i = 0; i < HEIGHT; ++i) {
				for (int j = 0; j < WIDTH; ++j) {
					matrix[i][j] = initChar;
				}
			}
		}

		// Functie om een element in de matrix in te stellen
		void setChar(int x, int y, char value) {
			if (y < HEIGHT && x < WIDTH) {
				matrix[HEIGHT-1-y][x] = value;	// oorsprong is linksonder.
			}
		}

		// Functie om een element uit de matrix op te halen
		char getChar(int x, int y) const {
			if (y < HEIGHT && x < WIDTH) {
				return matrix[HEIGHT-1-y][x];
			}
			return '\0';  // Onbekende waarde als de index ongeldig is
		}

		void clearMatrix()
		{
			for (int i = 0; i < HEIGHT; ++i) {
				for (int j = 0; j < WIDTH; ++j) {
					matrix[i][j] = ' ';
				}
			}
		}

		// Functie om de matrix af te drukken
 		void printMatrix() const {
			// Buffer voor elke rij, een extra plek voor de null-terminator
			char buffer[WIDTH + 1];

			for (int i = 0; i < HEIGHT; ++i) {
				// Kopieer de karakters van de huidige rij naar de buffer
				for (int j = 0; j < WIDTH; ++j) {
					buffer[j] = matrix[i][j];
				}
				// Voeg de null-terminator toe om de buffer als string af te sluiten
				buffer[WIDTH] = '\0';

				// Gebruik de buffer als string
				ESP_LOGI("", "%s", buffer);
        }
    }

	private:
		char matrix[HEIGHT][WIDTH];  // 2D-array van karakters
	};

};// end namespace crt
