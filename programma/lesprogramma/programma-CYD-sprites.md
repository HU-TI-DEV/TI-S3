# Programma CYD Sprites

Deze les gaat over het maken en tonen van sprite.

## Voorbereiding

- Lees over [sprites](https://en.wikipedia.org/wiki/Sprite_(computer_graphics))

## De opdracht

Bij deze opdracht is er weer een [voorbeeld project](../../software/CYD/Game_sprites/). 

Dit template is de basis waar later game-play elementen aan toe kunnen worden gevoegd. Dit is het laatste template dat we geven. Vanaf hier maak je zelf het eindproduct, je persoonlijke Game. Er volgen wel nog ESP32 lessen waar je elementen van kan gebruiken. Veel van de code in dit template is gegeven. Vul onderdelen die je in vorige opdrachten hebt gemaakt aan zoals `primitives` en `keyinput`. Je game mag ook gebruik maken van andere gebruikersinput zoals een joystick. Voor deze opdracht is dat nog geen vereiste.

Ja maakt tijdens deze opdracht: 
  - Een eigen speler (entity)
  - Deze afbeelding zet je om naar een C-array met behulp van de ([LVGL tool](https://lvgl.io/tools/imageconverter))
  - Integreer de sprite in het voorbeeld project
  - Game-play: Voeg een speelveld toe waar je karakter entities kan vernietigen (Heb je een ander idee dan mag dat ook). Log en laat in de console in ieder geval een score zien.
  - Beantwoord de vragen in de opdracht

We introduceren een entiteit (Entity) een abstract basis-object met minimaal `update(dt, width, height)` en `draw(display)`. Elke game-entiteit (speler, vis, kogel, etc.) weet zelf hoe hij beweegt (in update) en hoe hij getekend wordt (in draw).

In `main.cpp` maken we een speler aan:
```cpp
    PlayerHandle player = acquirePlayerShark();
    centerPlayerShark(Ili9341Display::WIDTH, Ili9341Display::HEIGHT);
    initPlayerSharkVelocity(20.0f, 10.0f);
```
Wat doet dit stukje code? Leg deze drie regels code stap voor stap uit.

De speler is één specifieke Entity. Via een handle krijgt player twee dingen:
`player.entity` de te registreren entiteit.
`player.input` een input dat iets kan ontvangen. In dit geval de knoppen van de keypad.

De Scene beheert een collectie van Entities. De `scene.add(player.entity)` is de registratie van de speler in een interne lijst. De `scene.setInputTarget(player.input)` zorgt voor inputrouting. Het vertelt de Scene waar de keypad events heen moeten. De simulatie en redering wordt gedaan door `scene.update(dt, W, H)` dat alle entities doorloopt en `scene.draw(display)` laat deze tekenen.

De analoge input registreren we als volgt:
```cpp
    AnalogButtonReader buttons(ADC1_CHANNEL_7, GPIO_NUM_35, 200); // 200 ms poll
    buttons.setCallback([&](Button button){
        scene.onButton(button);
    });
    buttons.start();
```
Leg uit waarom dit onze speler van plaats kan veranderen? Nadat je een input geeft via het keypad gaat onze speler versnellen. Welke stuk code is daar verantwoordelijk voor? Kan je een beter implementatie voor versnelling verzinnen?

De daadwerkelijke game-loop komt je waarschijnlijk bekend voor. Alleen is `vTaskDelay(frame);` afhankelijk van `frame`. Waarom is dit gedaan? Is er een beter implementatie mogelijk?

## Tijdens en na de les

- Krijg je les over de werking en het ontstaan van [games](https://youtu.be/dzN2pgL0zeg?si=HyszYZOeC7fJc9En) & [sprites](https://youtu.be/cT_FB_8f3ps?si=sZvbhYq1M5cYqEuM).
- Lever relevante code en screenshots in bij de Canvas opdracht **ESP32 CYD Sprites**

### Optioneel

- Voeg transparantie toe aan je sprite & code.
- Voeg een frame timer toe voor 'smoother' game play en consistente snelheid.

## Referenties

- https://en.wikipedia.org/wiki/Sprite_(computer_graphics)
