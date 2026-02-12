@startuml
state StateA
StateA --> StateB : eventBitButton1
StateA --> StateC : eventBitButton2
@enduml

@startuml
state StateA
StateA --> StateB : eventBitButton1
StateA --> StateB : eventBitButton2
@enduml

@startuml
state StateA
StateA --> StateB : eventBitButton1, eventBitButton2
@enduml

@startuml
state StateA
StateA --> StateB : eventBitButton1 + eventBitButton2
@enduml

@startuml
state StateA
StateA --> StateB : eventBitCounterSet [xQueueReceive(dataQueue, &val, 0); val>3]
@enduml

@startuml
state StateA
StateA --> StateB : eventBitCounterSet [counter>3]
@enduml


@startuml
state StateA : entry / counter++
state c1 <<choice>>
[*] --> StateA :/ counter = 0
StateA --> c1 : eventBitButton1
c1 --> StateA : [counter <3]
c1 --> StateB : [else]
@enduml


@startuml
state StateA 
state c1 <<choice>>
[*] --> StateA :/ counter = 0
StateA --> c1 : eventBitButton1
c1 --> StateA : [counter <3] / counter++
c1 --> StateB : [else]
@enduml



```c++
    case State::Ready:
      ESP_LOGI(TAG, "State is Executing");
      setLEDColor(Color::Green);
      do {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
      }
      while (!(executingCounter>3))
      break;
```



@startuml
skinparam state {
  BackgroundColor White
  BorderColor Black
  ArrowColor Black
}
hide empty description

state InstelControl {
    
    [*] --> Idle

    state Idle
    
    ' Interface definitie als notitie bij Idle
    note right of Idle
        <<interface>>
        meldTiptoetsIngedrukt(toetsID) / 
        poolTiptoetsId.write(toetsID); 
        flagTiptoetsIngedrukt.set()
    end note

    ' Toestanden definiëren met entry acties via dubbele punt syntax
    state LichtInstellen
    LichtInstellen : entry / ledControlLicht.knipperRgb(GEEL,ZWART,1)

    state ServoInstellen
    ServoInstellen : entry / ledControlServo.knipperRgb(GEEL,ZWART,1)

    state GeluidInstellen
    GeluidInstellen : entry / ledControlGeluid.knipperRgb(GEEL,ZWART,1)

    ' Keuzepunten
    state c_Licht <<choice>>
    state c_Servo <<choice>>
    state c_Geluid <<choice>>

    ' Transities
    Idle --> LichtInstellen : flagTiptoetsIngedrukt \n[poolTiptoetsId.read()==toetsID_enable]

    ' Van Licht naar Servo (via keuze check)
    LichtInstellen --> c_Licht : flagTiptoetsIngedrukt
    c_Licht --> ServoInstellen : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlLicht.setRgb(GROEN); \n bLichtEnabled=true
    c_Licht --> ServoInstellen : [else] / \n ledControlLicht.setRgb(RED); \n bLichtEnabled=false

    ' Van Servo naar Geluid (via keuze check)
    ServoInstellen --> c_Servo : flagTiptoetsIngedrukt
    c_Servo --> GeluidInstellen : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlServo.setRgb(GROEN); \n bServoEnabled=true
    c_Servo --> GeluidInstellen : [else] / \n ledControlServo.setRgb(RED); \n bServoEnabled=false

    ' Van Geluid naar Idle (via keuze check)
    GeluidInstellen --> c_Geluid : flagTiptoetsIngedrukt
    c_Geluid --> Idle : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlGeluid.setRgb(GROEN); \n bGeluidEnabled=true
    c_Geluid --> Idle : [else] / \n ledControlGeluid.setRgb(RED); \n bGeluidEnabled=false

}
@enduml


@startuml
skinparam state {
  BackgroundColor White
  BorderColor Black
  ArrowColor Black
}
hide empty description

state InstelControl {
    
    [*] --> Idle

    state Idle
    
    ' Interface definitie als notitie bij Idle
    note right of Idle
        <<interface>>
        meldTiptoetsIngedrukt(toetsID) / 
        poolTiptoetsId.write(toetsID); 
        flagTiptoetsIngedrukt.set()
    end note

    ' Toestanden definiëren met entry acties via dubbele punt syntax
    state LichtInstellen
    LichtInstellen : entry / ledControlLicht.knipperRgb(GEEL,ZWART,1)

    state ServoInstellen
    ServoInstellen : entry / ledControlServo.knipperRgb(GEEL,ZWART,1)

    state GeluidInstellen
    GeluidInstellen : entry / ledControlGeluid.knipperRgb(GEEL,ZWART,1)

    ' Keuzepunten
    state c_Licht <<choice>>
    state c_Servo <<choice>>
    state c_Geluid <<choice>>

    ' Transities
    Idle --> LichtInstellen : flagTiptoetsIngedrukt \n[poolTiptoetsId.read()==toetsID_enable]

    ' Van Licht naar Servo (via keuze check)
    LichtInstellen --> c_Licht : flagTiptoetsIngedrukt
    c_Licht --> ServoInstellen : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlLicht.setRgb(GROEN); \n bLichtEnabled=true
    c_Licht --> ServoInstellen : [else] / \n ledControlLicht.setRgb(RED); \n bLichtEnabled=false

    ' Van Servo naar Geluid (via keuze check)
    ServoInstellen --> c_Servo : flagTiptoetsIngedrukt
    c_Servo --> GeluidInstellen : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlServo.setRgb(GROEN); \n bServoEnabled=true
    c_Servo --> GeluidInstellen : [else] / \n ledControlServo.setRgb(RED); \n bServoEnabled=false

    ' Van Geluid naar Idle (via keuze check)
    GeluidInstellen --> c_Geluid : flagTiptoetsIngedrukt
    c_Geluid --> Idle : [poolTiptoetsId.read()==toetsID_enable] / \n ledControlGeluid.setRgb(GROEN); \n bGeluidEnabled=true
    c_Geluid --> Idle : [else] / \n ledControlGeluid.setRgb(RED); \n bGeluidEnabled=false

}
@enduml




@startuml
skinparam state {
  BackgroundColor White
  BorderColor Black
  ArrowColor Black
}
hide empty description

state ArtikelInvoer {
    
    ' Startpunt
    [*] --> Idle

    state Idle

    ' Interface definitie
    note right of Idle
        <<interface>>
        startInvoer() / flagStartInvoer.set()
        buttonPressed(buttonID) / buttonQueue.write(buttonId)
    end note

    ' Toestand: WachtOpToets
    state WachtOpToets
    WachtOpToets : entry / display.clear(); \n display.toonBericht("Type een artikelnummer: " + string(getal))

    ' Keuzepunt voor toetsafhandeling
    state c_ToetsCheck <<choice>>

    ' --- Transities ---

    ' Van Idle naar WachtOpToets
    Idle --> WachtOpToets : flagStartInvoer / \n getal=0; \n timer10sec.start()

    ' Timeout event (terug naar Idle)
    WachtOpToets --> Idle : timer10sec / \n snoepVerkoopController.timeoutOpgetreden()

    ' Toets lezen -> naar keuze element
    WachtOpToets --> c_ToetsCheck : toets = buttonQueue.read()

    ' --- Keuzes vanuit c_ToetsCheck ---

    ' 1. Cijfertoets (Blijft in WachtOpToets)
    c_ToetsCheck --> WachtOpToets : [isCijferToets(toets)] / \n getal = getal * 10 + toetsToInt(toets)

    ' 2. Delete toets (Blijft in WachtOpToets)
    c_ToetsCheck --> WachtOpToets : [isDelToets(toets)] / \n getal = getal / 10

    ' 3. Clear toets (Blijft in WachtOpToets)
    c_ToetsCheck --> WachtOpToets : [isClearToets(toets)] / \n getal = 0

    ' 4. Else (Ongeldige toets, blijft in WachtOpToets)
    c_ToetsCheck --> WachtOpToets : [else]

    ' 5. Enter toets (Klaar -> Naar Idle)
    c_ToetsCheck --> Idle : [isEnterToets(toets)] / \n snoepVerkoopController.invoerIsKlaar(getal)

    ' 6. Cancel toets (Afbreken -> Naar Idle)
    c_ToetsCheck --> Idle : [isCancelToets(toets)] / \n snoepVerkoopController.invoerIsKlaar(-1)

}
@enduml
