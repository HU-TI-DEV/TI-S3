# STD en code 

@startuml
mainframe **std** MachineControl
state Ready
Ready : entry / setLEDColor(Color::Green)
Error : entry / setLEDColor(Color::Red)
Ready --> Error              : after(2000ms)[execCounter>3]

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

