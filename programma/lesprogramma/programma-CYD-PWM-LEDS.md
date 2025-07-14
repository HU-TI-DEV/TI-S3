# RGB led PWM

## Voorbereiding
- bestudeer de manual van de esp32 over [led control](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html).
- bestudeer deze [code](./PwmLed/). 

## Tijdens de les
Tijdens de les gaan we:
- de bronnen bestuderen bij [voorbereiding](#Voorbereiding). 
- naar deze [code](../../software/CYD/PwmLed/) kijken. 
- naar deze [code](../../software/CYD/RgbPwmLed/) kijken. 
- aan de slag met de opdracht! 

Een stukje theorie:  
Zoals je kunt zien in de code zijn er 2 classes: PwmLed en RgbLed.  
De PwmLed:
  - je kunt een PwmLed object aanmaken door de volgende gegevens mee te geven:
  
```gpio_num_t pin, ledc_channel_t channel, ledc_timer_t time```

- In de manual van [led control](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html) kun je zien wat deze dingen betekenen. 
- Je kan voor elke led (dus voor de r,g en de b) een apart object aanmaken van de class PwmLed. 
- Je zult zien dat we die objecten nodig hebben voor de RgbLed class.

De RgbLeD class:
- je kunt een PwmLed object aanmaken door de volgende gegevens mee te geven:

```PwmLed* red, PwmLed* green, PwmLed* blue```

- de class is nu nog redelijk onzinnig. Er zit enkel 1 methode/functie in. 
  
**Opdracht RGB_LED_PWM**
- download deze [code](../../software/CYD/RgbPwmLed/). 
- pas de ```RgbLed.hpp``` aan zodat deze class minimaal dezelfde functionaliteit heeft als deze [class](../../software/CYD/RgbLed/main/RgbLed.hpp).
- Zorg dat er relevant doxygen commentaar aan je code is toegevoegd (hpp & cpp). 

- kijk ook of je de kleur geel kunt implementeren. 
- Bonus: kijk of je ook een functie kan implementeren in de class zodat het licht langzaam van kleur verandert. 

## Na de les
- werk verder aan de opdrachten als je het nog niet af hebt. 

## Canvas

Voor de opdracht is een canvas entry, namelijk:
  - ESP32 LED & PWM (deel 3)

Bestudeer de canvas opdracht om te zien wat je precies moet inleveren. 


