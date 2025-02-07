# CleanRTOS

## Voorwoord

De onderstaande informatie is in meer detail (in het engels) ook terug te vinden bij de CleanRTOS code zelf, in de src directory, in de files ``_crt_Readme.txt`` en ``_crt_Logger_Readme.txt``.

Daarnaast is in de comment sectie van elk van de klassen zelf een en ander in (nog) meer detail uitgelegd.

## Wat is CleanRTOS?

CleanRTOS is een flinterdunne wrapper rond freeRTOS. Daarnaast bevat het nog een aantal additionele classen die helpen overzichtelijke embedded software te schrijven en te debuggen.

### Wat is freeRTOS?

FreeRTOS is een open source, veel toegepaste RTOS. Het is een standaard onderdeel van de ESP32 firmware.

#### Wat is een RTOS?

Een RTOS staat voor "Real Time Operating System". Het is bedoeld om voor microcontrollers (net als operating systems zoals Linus en Windows) overzichtelijke multi-threaded code te kunnen schrijven.

## Waarom CleanRTOS?

Gebruik van CleanRTOS levert veel overzichtelijkere en to-the-point code op. Ook voorkomt het allerlei potentiele valkuilen die komen bij het direct gebruik van freeRTOS. 

## CleanRTOS klassen

CleanRTOS bestaat uit een kleine verzameling van klassen, welke is onder te verdelen in klassen die freeRTOS wrappen en enkele andere handige klassen.

### FreeRTOS wrappers - de belangrijkste

Bij goed software ontwerp zul je vrijwel uitsluitend de volgende 5 CleanRTOS klassen toepassen:

- Task
  - Afgeleide klassen hiervan gedragen zich als taak: hun main functie draait "parallel" aan die van andere taken.
- Flag
  - De ene taak kan de andere taak een "seintje" geven door een "flag" van die andere taak te setten. Die andere taak kan daar op wachten.
- Queue
  - De ene taak kan brokken informatie (bytes, structs, etc) versturen naar een queue van een andere taak. Die andere taak kan die brokken informatie een voor een uit de queue lezen op een moment dat het hem uitkomt.
- Pool
  - Een pool is een brok "gedeelde data" welke meerdere taken veilig kunnen lezen en/of aanpassen.
- Timer
  - Een timer is een "wekker". Je kunt hem periodiek af laten gaan of eenmalig.  Een taak kan op zo'n timer wachten.

### FreeRTOS wrappers - voor incidenteel gebruik

Voor uitzonderlijke gevallen, waar bovenstaande 5 klassen geen soelaas bieden, kunnen de volgende CleanRTOS klassen uitkomst bieden:

- Mutex
  - Met een Mutex kun je toegang tot bronnen die gebruikt worden door meerdere taken veilig reguleren. De implementatie in CleanRTOS detecteert automatisch potentiele deadlocks.
- MutexSection
  - Mocht je een Mutex willen gebruiken, dan is het aan te raden om in plaats daarvan MutexSection te gebruiken. Dat levert overzichtelijker en minder foutgevoelige code op (omdat de ingebouwde Mutex bij verlaten van de scope weer automatisch wordt vrijgegeven).

### Handige Utility klassen

Daarnaast bevat CleanRTOS nog een paar handige Utility klassen.

- Logger
  - Dit is een razendsnelle logger. Een log kost slechts een paar clock-cycli. Handig bij het debuggen. Zodra je op een 'Dump Button' klikt, wordt de gecachte log informatie naar het scherm geschreven.
- Handler
  - Dit is een generieke Handler klasse. Je kunt daarmee periodieke taken met dezelfde periode samenvoegen in een enkele taak. Dat bespaart resources en task-switch tijd.

## Uitleg via Video Serie
Via de volgende video serie kun je je vanuit je luie stoel laten uitleggen hoe een en ander met CleanRTOS werkt. Het bestaat uit videos die het eenvoudige gebruik/toepassen van CleanRTOS laten zien. Er zijn ook videos die uitleggen hoe het onder de motorkap werkt, zodat je een-op-een de relatie met FreeRTOS kunt zien.

- [CleanRTOS overview](https://youtu.be/P5RiUsPRDdY)
- [CleanRTOS Task gebruik](https://youtu.be/3W2uBrb0YAI)
- [CleanRTOS Flag gebruik en highwatermark check](https://youtu.be/j3TUx1L2b-8)
  - [CleanRTOS Task Waitable Flag Onder de motorkap](https://youtu.be/I1adj-1ucKg)
- [CleanRTOS Queue gebruik](https://youtu.be/6gtzlrYGRNo)
  - [CleanRTOS Queue onder de motorkap](https://youtu.be/69_BV3WDosI)
- [CleanRTOS Timer gebruik](https://youtu.be/gYyz0YWCRuk)
  - [CleanRTOS Timer onder de motorkap](https://youtu.be/ISTA7LL_qOo)
- [CleanRTOS MutexSection gebruik](https://youtu.be/SHOObIFtfrE)
  - [CleanRTOS Mutex Pool onder de motorkap](https://youtu.be/CShOFS78phQ)
- [CleanRTOS Pool gebruik](https://youtu.be/KUTgI4alVLw)
- [CleanRTOS Logger gebruik](https://youtu.be/XdClbnqFyQM)
  - [CleanRTOS Logger onder de motorkap](https://youtu.be/iMpHRoj--sA)
- [CleanRTOS Handler gebruik](https://youtu.be/8YMu4JQdMy8)
  - [CleanRTOS Handler onder de motorkap](https://youtu.be/tc_VfyLXJcc)
- [CleanRTOS wachten op meerdere waitables tegelijk](https://youtu.be/VneJ876W3KA)


