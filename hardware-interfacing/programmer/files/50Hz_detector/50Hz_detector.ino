/*

  Ik heb in een andere code gemeten hoe lang hij over het samplen doet, daar komt uit dat de sample tijd gelijk is 1.25 ms.


  De delay is 1.130 ms, de rest van de tijd wordt ingenomen door de analogRead.

  Dit houdt in dat de sample frequentie gelijk is aan 800 Hz. De hoogste frequentie die je kan detecteren is 400Hz.


  De kleinste freqeuentie (k=1) is dan 25Hz (400/16, omdat je een buffer hebt van 32 => 32/2 =16). De tweede frequentie is dan 50 Hz!!!!

  De interessante waarde is dus: sqrt(pow(X_real[2],2)+pow(X_imag[2],2))

*/

// Define the number of samples (32)

#define N 32

// Input buffer with 32 samples (real values)

int x[N] ;


// Arrays to store the real and imaginary parts of the DFT output

void setup() {

  // Initialize serial communication for output

  //Serial.begin(9600);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(PA3, OUTPUT);
  pinMode(PA4, OUTPUT);
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

    //imag_part -= (float)x[n] * cos(angle+0.5*PI);  // Imaginary part (note the negative sign)

  }

  // Store the results in the corresponding arrays

  return (real_part* real_part);
}


void loop() {
  for (int i = 0; i < 32; i++)
  {
    delayMicroseconds(1130);
    x[i] = analogRead(PA0);
  }

  // Perform DFT

  // Print the results (real and imaginary parts of the DFT)

  float result =  calculateDFT();
  //Serial.println();
  digitalWrite(PA1, LOW);
  digitalWrite(PA2, LOW);
  digitalWrite(PA3, LOW);
  digitalWrite(PA4, LOW);
  if (result > 64000000)
  {
    digitalWrite(PA1, HIGH);
    digitalWrite(PA2, HIGH);
    digitalWrite(PA3, HIGH);
    digitalWrite(PA4, HIGH);
  }
  if (result > 36000000 && result < 64000000)
  {
    digitalWrite(PA1, HIGH);
    digitalWrite(PA2, HIGH);
    digitalWrite(PA3, HIGH);
  }
  if (result > 8000000 && result < 16000000)
  {
    digitalWrite(PA1, HIGH);
    digitalWrite(PA2, HIGH);
  }
  if (result > 400000 && result < 8000000)
  {
    digitalWrite(PA1, HIGH);
  }

  // Nothing needed here for now
}
