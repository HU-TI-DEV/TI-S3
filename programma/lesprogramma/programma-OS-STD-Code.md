# Operating systems, State Transistion Diagrams en Coderen...

## Voorbereiding

- Je hoeft je voor dit stukje niet voor te bereiden. In dit notebook wordt beschreven hoe operating systems werken, hoe je ze moet coderen en hoe je STD's moet maken. 

### Tijdens de les

De powerpoint:
[Operating systems, STD en code](./files/Operating Systems.pptx)

#### vTaskDelay
[vTaskDelay.zip](./files/vTaskDelay.zip)
1) Varieer de tijd die je meegeeft aan de taak als je hem initieert. 
2) Maak de tijd extreem lang...
3) Maak nog een extra taak aan. 

#### EventGroup
[EventGroup.zip](./files/EventGroup.zip)
1) Wat doet dit stukje in de constructor? 
   ```
   uint32_t waitMs = 5000????? 
   ```
2) Kijk in de logging hoe de taak op de verschillende onderstaande situatie reageerd...
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


-
-


## Na de les

- werk verder aan de opdrachten als je het nog niet af hebt.

## Canvas

- 
