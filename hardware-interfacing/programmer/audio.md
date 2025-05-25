# Audio op een microcontroller (ATtiny24)

_Soms is software beter, soms hardware!!!!_

## Componenten

- $8 {\Omega}$ weerstand
- $47 {\mu}F$ condensator
- Speaker $8 {\Omega}$

## Stap-voor-stap instructie

1) Sluit de ene draad van de speaker aan de ground van de microcontroller (via je breadboard). 
2) Sluit de andere draad aan op (fysieke) pin 5 van de microcontroller.
3) Flash de software maar de microcontroller. 

Hoe gebruik je [PWM op een microcontroller](https://www.hackster.io/bearislive/enable-pwm-on-an-attiny-by-programming-its-registers-565948) zonder Arduino analogWrite().

```c++
#include <avr/io.h>
#include <util/delay.h>

void setupPWM() {
    // Set PB2 as output ATtiny physical pin 5
    DDRB |= (1 << PB2);

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

4) Wat valt je op? Hoe klinkt het muziekje? 

   > __Schrijf je antwoord op in je md document.__

5) Wat is er mis met bovenstaande code (hint: is de juiste timer gebruit?) pas de code aan het sluit de speaker aan op de juiste pin. Hoe klinkt het nu?
6) Maak de andere draad van de luidspreker weer los. 
7) Sluit de weerstand aan op pin ? van de microcontroller.
8) Aan de andere kant van de weerstand sluit je twee dingen aan: a) de andere draad van de speaker b) de plus kant van de condensator. 
9) de min kant van de condensator sluit je aan op de aarde van de microcontroller.
10) Als het goed is moet het geluid weliswaar zachter klinken, maar wel veel beter! Heb je een idee waarom? 

   > __Schrijf je idee op in je md document.__

11) Maak een foto van je opstelling en 

    > __Plak dit in je .md document__.

12) Neem je opstelling mee naar de oscilloscoop en vergelijk het signaal met en zonder de condensator. Klopte je idee van (9)?

    > __Schrijf je antwoord op in je .md document__

13) Berekening de cut off frequentie van het RC filter. Je mag hier ook een online website voor gebruiken. 

    > __Plak je berekening of een plaatje van de website in je .md document__.

14) Welk liedje kan je met de onderstaande code afspelen? We maken gebruik van een andere timer (Timer1) en de speaker sluit je ook aan op een andere pin. Deze muziek past beter bij kerst. Weet je niet nog een goede zomer hit?

```c++
/* Jingle Bells PWM demo

  2024-12-14 Fix code, Hagen Patzke
  The original code used Timer0, but:
  - This timer does not have a 'top' value register
    so its frequency can only be changed via the pre-scaler.
  - Only the duty cycle can be changed with Timer0.
  - Timer0 is also an 8-bit timer.

  -> we need to use Timer1 (16-bit-timer) instead
  -> instead of ATtiny24A pin5 (PB2) we need to use pin7 (PA6)
*/
#include <avr/io.h>
#include <util/delay.h>

/* from https://www.seventhstring.com/resources/notefrequencies.html
   frequencies for octave 8 (low bass)
   C C# D Eb E F F# G G# A Bb B - English scale names
   C C# D D# E F F# G G# A B  H - German  scale names
   const int note_freq[] = { 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902 };
*/

// Define the note names and their frequencies in Hz
#define NOTE_C4 261
#define NOTE_D4 294
#define NOTE_E4 329
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 493
#define NOTE_C5 523
#define PAUSE 0
// NB: we later multiply this with 2 (shift left one bit), one octave up sounds better with buzzers

//#define F_CPU 8000000UL  // -> set from Arduino core, usually 8MHz
// Standard Default Clock Source is
// CKSEL = “0010”, SUT = “10”, and CKDIV8 programmed -> 1.0MHz
// WARNING
// Looks like the Arduino IDE _does_ adapt all timing-related definitions to the selected frequency (e.g. internal 1MHz or 8MHz)
// but does not actually program the fuses correctly -> the device works in whatever is set (1MHz from the factory)
// but if you select 8MHz in  the IDE, the F_CPU value will be adapted, and also the timing for _delay_ms,
// resulting in very long notes.

// Because we can also use a prescaler for the timer
// (the original code used a prescaler of 8 for an 8MHz clock),
// we need to define the timer frequency
#define TIMER_FRQ 1000000UL

// We need the 16-bit Timer1 to set the PWM frequency:
// Define output pin, we use PA6, connected to OC1A
#define SPEAKER_PIN PA6 /* ATtiny24A pin 7 */

#define LEN_ARRAY(x) (sizeof(x) / sizeof(x[0]))

// Melody (excerpt) from https://www.pinterest.com/pin/free-lead-sheet-jingle-bells--778559854340300182/

// Melody and durations -  stored in FLASH (PROGMEM)
const uint16_t melody[] PROGMEM = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, PAUSE,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4,
  // second part
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, PAUSE,
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4, PAUSE,
  // extra pause at the end
  PAUSE
};

#define sixteenth_note_len 64  // -> 1/16=64ms, 1/8=128ms, 1/4=256ms, 1/2=512ms, 1/1=1024ms
const uint8_t noteDurations[] PROGMEM = {
  4, 4, 8, 4, 4, 8,
  4, 4, 6, 2, 12, 4,
  4, 4, 6, 2, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 8, 8,
  // second part
  4, 4, 8, 4, 4, 8,
  4, 4, 6, 2, 12, 4,
  4, 4, 6, 2, 4, 4, 4, 2, 2,
  4, 4, 4, 4, 12, 4,
  // extra pause at the end
  4
};

void delay_ms(int duration) {
  for (int i = 0; i < (duration >> 2); i++) {
    _delay_ms(1);
  }
}

void disablePWM() {
  TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));  // Disable PWM
}

void enablePWM() {
  TCCR1A |= ((1 << COM1A1) | (0 << COM1A0));  // Enable PWM
}

// Function to play a note with the specified frequency and duration
void playNote(uint16_t frequency, uint8_t duration) {
  if (frequency == 0) {
    // Silence
    disablePWM();
    delay_ms(duration * sixteenth_note_len * 4);
  } else {
    enablePWM();
    unsigned int counter_value = TIMER_FRQ / (frequency << 1);  // -> one octave higher
    unsigned int duration_ms = duration * sixteenth_note_len;
    ICR1 = counter_value;          // Set the Timer1 TOP value for the desired frequency
                                   // with a 16-bit register this also makes sense
    OCR1A = (counter_value >> 1);  // Set duty cycle to 50%
    delay_ms(duration_ms * 3);     // Play for 3/4 of the note duration
    disablePWM();
    delay_ms(duration_ms);  // Short pause between notes (1/4 of duration)
  }
}

void setup() {
  // Set PA6 as output (ATtiny24A SOIC physical pin7) -> enable speaker pin on Port A
  // Also enable PA1/2/3/4 as output for LEDs from 50Hz_detector.
  DDRA = (1 << SPEAKER_PIN) | 0x1E;
  // Turn off the LEDs from the 50Hz_detector, to prevent the LEDs from flickering while playing.
  PORTA &= ~(0x1E);
  // Initialize PWM: Configure Timer1 A for Fast PWM (Mode 14)
  TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (0 << WGM10);            // Fast PWM, non-inverting
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);  // Count up, Prescaler = 1
}

void loop() {
  // Play the melody
  for (uint8_t i = 0; i < LEN_ARRAY(melody); i++) {
    // If we would store the melody/duration in RAM, we could use this:
    // playNote(melody[i], noteDurations[i]);
    // PROGMEM storage unfortunately needs a different syntax for variable access
    playNote(pgm_read_word(&melody[i]), pgm_read_byte(&noteDurations[i]));
  }
}

#ifndef main
// main routine (as used by the Arduino)
int main() {
  setup();
  while (1) { loop(); }
}
#endif
```
