 #Programma PID workshop

## Voorbereiding
Bestudeer deze filmpjes:
- [intro PID workshop](https://www.youtube.com/watch?v=Fa7ecsAEizw)<br>
- [deel 2](https://www.youtube.com/watch?v=rr5ajN_1SYs)<br>
  
## Tijdens de workshop
- Sluit de ventilator aan, de zwarte draad naar de aarde van de 12 volt, de rode draad naar de +12 volt van de voeding, de oranje draad naar digital out pin 3 van de Arduino.
- Sluit de sensor aan, zwart naar de ground van de arduino, de rode draad naar de +5 volt van de arduino, de laatste draad naar de analoge ingang (A0) van de Arduino.
- Upload de volgende code naar de Arduino :
- Stuur de ventilator aan met 70% '''digitalWrite (3,179);'''  en balanceer de wip met de gewichtjes (zie filmpje hierboven).
- Speel met de Kp, Ki en Kd waarden totdat het systeem ongeveer regelt zoals in het eerste filmpje!
- Upload een document naar Canvas met een screenshot van je code waarin de Kp, Ki en Kd te zien zijn.
