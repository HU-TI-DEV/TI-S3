# Audio op een microcontroller

Componenten:
- 1.5 Ohm weerstand
- 470 microF condensator
- speakertje uit de kit van het 1e jaar

1) Sluit de zwarte draad van de speaker aan de ground van de microcontroller (via je breadboard). 
2) Sluit de rode draad aan op pin XX van de microcontroller.
3) Flash de software maar de microcontroller. 
4) Wat valt je op? Hoe klinkt het muziekje? 

__Schrijf je antwoord op in je md document.__

5) Maak de rode draad van de luidspreker weer los. 
6) Sluit de weerstand aan op pin XX van de microcontroller.
7) Aan de andere kant van de weerstand sluit je twee dingen aan: a) de rode draad van de speaker b) de plus kant van de condensator. 
8) de min kant van de condensator sluit je aan op de aarde van de microcontroller.
9)  Als het goed is moet het geluid weliswaar zachter klinken, maar wel veel beter! Heb je een idee waarom? 

__Schrijf je idee op in je md document.__

10) Maak een foto van je opstelling en 

__past hem in je md document__.

11) Neem je opstelling mee naar de oscilloscoop en vergelijk het signaal met en zonder de condensator. Klopte je idee van (9)?

 __Schrijf je antwoord op in je md document__

12) Berekening de cut off frequentie van het RC filter. Je mag hier ook een online website voor gebruiken. 

__Paste je berekening of een plaatje van de website in je md document__.

```c++
#include <avr/io.h>
#include <util/delay.h>

void setupPWM() {
    // Set PB0 as output
    DDRB |= (1 << PB0);

    // Configure Timer0 for Fast PWM mode
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, non-inverting
    TCCR0B = (1 << CS01); // Prescaler = 8

    OCR0A = 128; // 50% duty cycle (initial)
}

void playTone(uint8_t dutyCycle) {
    OCR0A = dutyCycle; // Adjust PWM duty cycle to change tone volume
}

int main() {
    setupPWM();

    while (1) {
        // Cycle through tones by varying duty cycle
        for (uint8_t i = 0; i < 255; i += 10) {
            playTone(i);
            _delay_ms(50);
        }
    }

    return 0;
}

```