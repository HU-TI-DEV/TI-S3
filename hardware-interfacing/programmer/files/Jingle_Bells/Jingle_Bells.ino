#include <avr/io.h>
#include <util/delay.h>

// Define the notes and their frequencies in Hz
#define NOTE_C4  261
#define NOTE_D4  294
#define NOTE_E4  329
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  493
#define NOTE_C5  523

#define F_CPU 8000000UL // Assume 8 MHz clock frequency

// Define output pin (e.g., PB2, connected to OC1A)
#define SPEAKER_PIN PB2

void wait(unsigned int ms)
{
  for(unsigned int i=0; i < ms; i++)
  {
    _delay_ms(1);
  }
}

// Melody and durations
uint16_t melody[] = {
    NOTE_E4, NOTE_E4, NOTE_E4,
    NOTE_E4, NOTE_E4, NOTE_E4,
    NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4
};

uint16_t noteDurations[] = {
    250, 250, 500,
    250, 250, 500,
    250, 250, 250, 250, 1000
};

// Function to set up Timer1 for PWM on OC1A (PB2)
void setupPWM() {
    // Set PB2 (OC0A) as output
    DDRB |= (1 << SPEAKER_PIN);

    // Configure Timer0 for Fast PWM mode
    TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // Fast PWM, non-inverting
    TCCR0B = (1 << CS01); // Prescaler = 8
}

// Function to play a note with the specified frequency and duration
void playNote(uint16_t frequency, uint16_t duration) {
    if (frequency == 0) {
        // Silence
        TCCR0A &= ~(1 << COM0A1); // Disable PWM
    } else {
        TCCR0A |= (1 << COM0A1);  // Enable PWM
        ICR1 = F_CPU / frequency; // Set the TOP value for the desired frequency
        OCR0A = ICR1 / 2;         // Set duty cycle to 50%
    }

    wait(duration / 8); // Wait for the note duration
    TCCR0A &= ~(1 << COM0A1); // Disable PWM after the note
    wait(duration / 32); // Short pause between notes
}

// Main function
int main() {
    // Initialize PWM
    setupPWM();

    while (1) {
      // Play the melody
      for (uint8_t i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
          playNote(melody[i], noteDurations[i]);
      }
      // slight pause between the song
      _delay_ms(2000);
    }

}
