# Programma Signalen in het Frequentiedomein, Fir filter, Median filter

## Voorbereiding

Fourier, bestudeer dit filmpje:
- https://www.youtube.com/watch?v=ku39-1nrLEY

Bestudeer dit Jupyter Notebook:
- https://colab.research.google.com/drive/1Ef9jMI7Xl5Bf_fc_84rMgdECp6YsRVsk?usp=sharing

Digitaal filteren, bestudeer de volgende filmpjes:
-  https://youtu.be/Ao4cgxQIQrw?si=_-uKQsK79rTFXIwS
-  https://youtu.be/IklFHadApFI?si=zVBgie5ILE9iiNdr
-  https://youtu.be/-M1EfbZ8xWs?si=l3oNQc-mpJcG5LrG
-  https://youtu.be/M79_tzuWiLQ
-  https://youtu.be/_vvIPFmNQD8?si=MvneLlWZjhwuV2Ux

En het nut van dit alles!:
- https://youtu.be/hG2-fehhcig
  
## Tijdens en na de les

1) Bart legt DFT uit.

2) Upload de volgende code naar je arduino uno.

```c++
// 50 Hz detector – 1024 samples, 8-bit storage
// Fits in Arduino Uno SRAM

#include <Arduino.h>
#include <math.h>

const uint16_t N = 512;     // number of samples
const uint16_t Fs = 500;    // sample rate [Hz]
const uint16_t FREQ = 50;   // frequency to detect
const int16_t SCALE = 256;  // scaling factor for sin/cos
const uint8_t ANALOG_PIN = A0;

uint8_t samples[N];  // 8-bit samples
const uint16_t Ts = 1000000UL / Fs;

void setup() {
  Serial.begin(115200);
  Serial.println(F("50 Hz detector – 1024 samples, 8-bit storage"));
}

void loop() {
  // ---- Sampling ----
  uint16_t n = 0;
  while (n < N) {
    uint32_t t0 = micros();
    uint16_t val = analogRead(ANALOG_PIN);  // 0–1023
    samples[n] = val >> 2;                  // scale to 0–255
    n++;
    while ((micros() - t0) < Ts) {}
  }

  // ---- Single-frequency DFT at 50 Hz ----
  int32_t cosSum = 0;
  int32_t sinSum = 0;

  for (uint16_t n = 0; n < N; n++) {
    float angle = 2.0 * PI * FREQ * n / Fs;
    int16_t c = (int16_t)(cos(angle) * SCALE);
    int16_t s = (int16_t)(sin(angle) * SCALE);
    int32_t x = samples[n];
    cosSum += x * c;
    sinSum += x * s;
  }

  // ---- Dump raw samples ----
  Serial.println(F("--- SAMPLE DUMP START, first 1/4 of the samples ---"));
  for (uint16_t n = 0; n < (N / 4); n++) {
    Serial.println(samples[n]);
  }
  Serial.println(F("--- SAMPLE DUMP END ---"));

  // ---- Compute relative "power" ----
  uint32_t power = (uint32_t)(((int64_t)cosSum * cosSum + (int64_t)sinSum * sinSum)
                              / ((int64_t)SCALE * N * SCALE * SCALE));

  Serial.print(F("50 Hz power: "));
  Serial.println(power);

  delay(250);
}
```
Sluit een jumpwire aan op A0 van je arduino.
Open je serial monitor (en je plotter). Zet de baudrate goed. Houd je jumpwire in de buurt van een wandcontact doos. 

3) Bestudeer & lever de Canvas opdracht `Signals, Fourier en Filters` in.
