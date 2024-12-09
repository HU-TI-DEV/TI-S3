# 50Hz detector
In dit practicum gaan we aan de slag om een 50Hz detector te bouwen. 
Maak eerst op je breadboard het volgende schema:
1) verbind 4 ledjes naar PA1, PA2, PA3 en PA4 en naar aarde (via een 1 KOhm weerstand, elke led zijn eigen voorschakelweerstand).
2) verbind op PA0 een draadje naar een spoeltje van 220 microHenry.

Wat we gaan doen is de analoge spanning op PA0 bemonsteren. Op die pin zal de spanning als een gek op en neer gaan (in feite hebben we een radio antenne op de analoge ingang aangesloten).  


```c++
/*
Ik heb in een andere code gemeten hoe lang hij over het samplen doet, daar komt uit dat de sample tijd gelijk is 1.25 ms. 
De delay is 1.130 ms, de rest van de tijd wordt ingenomen door de analogRead.
Dit houdt in dat de sample frequentie gelijk is aan 800 Hz. De hoogste frequentie die je kan detecteren is 400Hz. 
De kleinste freqeuentie (k=1) is dan 25Hz. De tweede frequentie is dan 50 Hz!!!!
De interessante waarde is dus: sqrt(pow(X_real[2],2)+pow(X_imag[2],2)) 
*/
// Define the number of samples (32)
#define N 32

// Input buffer with 32 samples (real values)
int x[N];

// Arrays to store the real and imaginary parts of the DFT output

void setup() {
  pinMode(PA0, INPUT);

  DDRA |= (1 << PA1);  //replaces pinMode(PA1, OUTPUT);
  DDRA |= (1 << PA2);  //replaces pinMode(PA2, OUTPUT);
  DDRA |= (1 << PA3);  //replaces pinMode(PA2, OUTPUT);
  DDRA |= (1 << PA4);  //replaces pinMode(PA2, OUTPUT);
}

// Function to calculate the DFT of the input buffer
float calculateDFT() {
  int k = 2;
  float real_part = 0.0;
  float imag_part = 0.0;

  for (int n = 0; n < N; n++) {
    // Calculate the angle for the current sample and frequency bin
    float angle = 2 * PI * k * n / N;
    // Accumulate the real and imaginary parts
    real_part += (float)x[n] * cos(angle);  // Real part
    imag_part -= (float)x[n] * sin(angle);  // Imaginary part (note the negative sign)
  }

  return (sqrt(pow(real_part, 2) + pow(imag_part, 2)));
  // Store the results in the corresponding arrays
}

void loop() {

  for (int i = 0; i < 32; i++) {
    delayMicroseconds(1130);
    x[i] = analogRead(PA0);
  }
  // Perform DFT
  float result = calculateDFT();
  if (result > 1600) {
    PORTA |= (1 << PA1);  //replaces digitalWrite(PA1, HIGH);
    PORTA |= (1 << PA2);  //replaces digitalWrite(PA2, HIGH);
    PORTA |= (1 << PA3);  //replaces digitalWrite(PA3, HIGH);
    PORTA |= (1 << PA4);  //replaces digitalWrite(PA4, HIGH);
  } else if (result > 800) {
    PORTA |= (1 << PA1);   //replaces digitalWrite(PA1, HIGH);
    PORTA |= (1 << PA2);   //replaces digitalWrite(PA2, HIGH);
    PORTA |= (1 << PA3);   //replaces digitalWrite(PA3, HIGH);
    PORTA &= ~(1 << PA4);  //replaces digitalWrite(PA4, LOW);
  } else if (result > 400) {
    PORTA |= (1 << PA1);   //replaces digitalWrite(PA1, HIGH);
    PORTA |= (1 << PA2);   //replaces digitalWrite(PA2, HIGH);
    PORTA &= ~(1 << PA3);  //replaces digitalWrite(PA3, LOW);
    PORTA &= ~(1 << PA4);  //replaces digitalWrite(PA4, LOW);
  } else if (result > 200) {
    PORTA |= (1 << PA1);   //replaces digitalWrite(PA1, HIGH);
    PORTA &= ~(1 << PA2);  //replaces digitalWrite(PA2, LOW);
    PORTA &= ~(1 << PA3);  //replaces digitalWrite(PA3, LOW);
    PORTA &= ~(1 << PA4);  //replaces digitalWrite(PA4, LOW);
  } else {
    PORTA &= ~(1 << PA1);  //replaces digitalWrite(PA3, LOW);
    PORTA &= ~(1 << PA2);  //replaces digitalWrite(PA3, LOW);
    PORTA &= ~(1 << PA3);  //replaces digitalWrite(PA3, LOW);
    PORTA &= ~(1 << PA4);  //replaces digitalWrite(PA4, LOW);
  }
}
~~~
