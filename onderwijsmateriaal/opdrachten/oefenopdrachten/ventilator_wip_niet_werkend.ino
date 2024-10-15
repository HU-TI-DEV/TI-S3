
void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(115200);
}

float distance = 0;
float setpoint = 0.300;
float error = 0;
float error_sum = 0;
float error_prev = 0;
float dt = 0.003;
float prop_setpoint = 0;
float time=0;

// HERE YOU CAN CHANGE YOUR VALUES!!!!
float Kp = 1000;
float Ki = 0;
float Kd = 0;
//  GOOD LUCK!!!

void loop() {
  delayMicroseconds(1000);  // apparantly the rest of the loop takes ~2000 microSeconds...
  if (millis()>30000) setpoint=0.40;
  time+=dt;
  distance = analogRead(A0)/1000.0;
  error = (setpoint - distance);
  error_sum += error * dt;
  

  prop_setpoint =Kp * (error)+ Ki * error_sum +  Kd*(error - error_prev) / dt;
  error_prev = error;
  if (prop_setpoint > 100) {
    prop_setpoint = 100;
  }
  if (prop_setpoint < 0) {
    prop_setpoint = 0;
  }
  Serial.print(distance,2);
  Serial.print(',');
  Serial.print(error,2);
  Serial.print(',');
  Serial.print(error_sum,2);
  Serial.print(',');
  Serial.print(Kp*error/100,2);
  Serial.print(',');
  Serial.print(Ki*error_sum/100,2);
  Serial.print(',');
  Serial.print(Kd*(error - error_prev) / dt/100,2);
  Serial.print(',');
  Serial.print(prop_setpoint/100,2);
  Serial.print(',');
  Serial.println(1.2);

  analogWrite(3, int(prop_setpoint * 255 / 100.0));
}
