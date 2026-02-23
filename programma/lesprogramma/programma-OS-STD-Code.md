# Operating systems, State Transistion Diagrams en Coderen...

## Voorbereiding

Bekijk de volgende video's:
- [video 1](https://youtu.be/kP-pP6FEu8I?si=E8p51WUj5l8jayeM)
- [video 2](https://youtu.be/WQGAs9MwXno?si=u5gYhdr_75saWNnz)

In dit notebook wordt beschreven hoe operating systems werken, hoe je ze moet coderen en hoe je STD's moet maken. 

### Tijdens de les

De powerpoint:
[Operating systems, STD en code](./files/Operating_Systems.pptx)

#### vTaskDelay
Unzip de volgende file in de apps folder van de s3-template:  
[vTaskDelay.zip](./files/vTaskDelay.zip)  
Zorg dat de filestructuur er als volgt uiziet:
```
├── espressif
      └── s3-template
               └──apps
                    └──vTaskDelay
                          ├── app
                          ├── components
                          └── main
```

1) Varieer de tijd die je meegeeft aan de taak als je hem initieert. 
2) Maak de tijd extreem lang...
3) Maak nog een extra taak aan. 

#### EventGroup
Unzip de volgende file in de apps folder van de s3-template:  
[EventGroup.zip](./files/EventGroup.zip)
1) Wat doet dit stukje in de constructor? 
   ```
   uint32_t waitMs = 5000????? 
   ```
2) Kijk in de logging hoe de taak op de verschillende onderstaande situaties reageerd...
```
        ESP_LOGI("APP_MAIN","set BIT_0 and BIT_4");
        xEventGroupSetBits(myEventGroup, BIT_0); 
        xEventGroupSetBits(myEventGroup, BIT_4); 
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI("APP_MAIN","set BIT_0 | BIT_4 (really at the same time)");
        xEventGroupSetBits(myEventGroup, BIT_0 | BIT_4); 
        vTaskDelay(pdMS_TO_TICKS(1000));
```
Teken op een papier wanneer de taak zijn kans krijgt en wat hij dan doet? 
(je kan ook dit stukje overnemen in een .md file en er dan in cursief bij zetten als hij zijn kans grijpt...)

#### Queue
Unzip de volgende file in de apps folder van de s3-template:  
[Queue.zip](./files/Queue.zip)
1) Voeg een Vtask delay van 2500ms toe aan de consumertask (voor de closing } van de for loop). Snap je wat er gebeurt?

#### Mutex
Unzip de volgende file in de apps folder van de s3-template:  
[SemaphoreCreateMutex.zip](./files/SemaphoreCreateMutex.zip)
1) kopieer de code van main2.cpp naar main.cpp. 
2) Snap je wat er gebeurt?

#### Timer
Unzip de volgende file in de apps folder van de s3-template:  
[xTimerCreate.zip](./files/xTimerCreate.zip)
1) verander de "auto reload timer" naar pdFALSE
2) Snap je wat er gebeurt?

#### Template
Unzip de volgende file in de apps folder van je s3-template:  
[StateMachineTemplate.zip](./files/StateMachineTemplate.zip)
1) Run doxygen om te kijken wat de template eigenlijk doet.
2) Run de code om te kijken wat het eigenlijk doet (tip: blijf meerdere keren op de boot button knop drukken).
3) Verander #define kEnableLog 0 in #define kEnableLog 1 (in counter.cpp) en run hem nog een keer.
4) Bekijk de Counter_std.png en de MachineControl_std.png in de root van de zip....
5) TO BE CONTINUED!!!   

Mocht je hier al aan zijn gekomen, dan kun je verder gaan met [programma-std-code-introductie](./programma-std-code-intro.md)

## Na de les

- werk verder aan de opdrachten als je het nog niet af hebt.

## Canvas
Er zijn geen specifieke opdrachten die je hoeft in te leveren. Zorg wel dat je alles goed verwerkt in je logboek. 
