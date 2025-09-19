# Programma CYD Backbuffer

Deze les gaat over het gebruik van een backbuffer om (teken)data naar een scherm te sturen.

## Voorbereiding

- Lees over Heap Memory Allocation (https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/mem_alloc.html)
- Lees over Resource Acquisition Is Initialization or RAII (https://en.cppreference.com/w/cpp/language/raii.html)

In de implementatie is de backbuffer een class-member (class buffer) en niet meer een statische pointer zoals in ons vorige voorbeeld. Als we naar Ili9341Display.cpp kijken, zien we dat er in de constructor geen buffer wordt aangemaakt, maar in init() wordt met

```cpp
  backbuffer_ = static_cast<uint16_t*>(heap_caps_malloc(
  WIDTH * HEIGHT * sizeof(uint16_t),
  MALLOC_CAP_DMA));
```
een pointer naar het framebuffer-geheugen gealloceerd.

Die pointer (backbuffer_) is een private member van de Ili9341Display-class. In de destructor ~Ili9341Display() wordt vervolgens gecontroleerd of die pointer niet nullptr is en daarna weer vrijgegeven met free(backbuffer_). 

Dat betekent dus: De backbuffer “hoort” bij het object van de class.
Elke instantie van Ili9341Display krijgt zijn eigen buffer.
Resourcebeheer volgt **RAII**: allocatie in init(), vrijgave in destructor.
Dat maakt dat we een class buffer hebben gemaakt. Een buffer die eigendom is van de class, in plaats van een globale of lokale variabele.

## De opdracht

Bij deze opdracht is weer een [voorbeeld project](../../software/CYD/LCD_backbuffer/). De implementatie van de backbuffer is gegeven. Maak een project waar je visueel laat zien het verschil tussen “direct naar het scherm tekenen” en “tekenen naar backbuffer + blit”. Je moet hier dus teruggrijpen naar de implementatie uit het vorige voorbeeld "CYD drawables".
  
## Tijdens en na de les

- Geef twee voordelen van een backbuffer
- Maak van het werkende project een korte video
- Lever relvante code en screenshots in bij de Canvas opdracht **ESP32 CYD Backbuffer**

### Optioneel

- Waarom zou je `MALLOC_CAP_8BIT` en niet bijvoorbeeld `MALLOC_CAP_8BIT` in bovenstaande opdracht?