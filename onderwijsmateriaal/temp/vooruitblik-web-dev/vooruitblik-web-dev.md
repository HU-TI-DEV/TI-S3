# Vooruitblik Web Development

## Requirementsfase : universeel toepasbaar

Ontwikkeldoc tm Functionele Decompositie (het hele
requirements stuk) is universeel toepasbaar.  

## Ontwerpfase : per domein anders

### Embedded software : volgens "Design Like a Robot"

Met de Object Modellen begint de ontwerp-fase.  

De ontwerpflow volgens "Design Like A Robot (Object model, Class diagram, Taakstructurering, STD, Code) is perfect geschikt voor native toepassingen (in c++, embedded, c#, Unity3d etc). Gebruik die methode dit semester dus om de software voor de ESP32 mee te ontwerpen:

- Een handheld IR device om dingen in te stellen of uit te lezen. 
  (lamp of  energiemeters)

- De  Snelheids-meet-en-weergave-device.

- De “lamp” device .

- De “Rollator”device.

Doe dat in het bestaande Ontwikkeldocument.

### Meerdere devices -> ontwikkeldocument opsplitsen

Als je meerdere devices hebt (bijvoorbeeld een aparte voor de snelheidsmeter en een aparte voor de weergave), ga dan vanaf de Functionele Decompositie over op
meerdere ontwikkeldocumenten, elk voor het specifieke device, te beginnen met de objectmodellen ervan.  

## Webapplicatie

De Webapplicatie is een vreemde eend in de bijt. Die bestaat uit meerdere applicaties die met elkaar praten: een python/flask deel dat de html paginas retourneert en back-end-jobs uitvoert, een mongodb database voor databeheer, "html" dat bepaalt wat er in de browser te zien is en Javascript dat er dynamisch gedrag aan toevoegt.

De "Design like a robot" methode is daar niet een op een op toepasbaar.

Voor de web-applicaties krijg je bij een latere le s

Bij een latere les krijg je wat voorbeelden (inclusief code). Die geven een voorbeeld van hoe zo'n webapplicatie op te zetten.  
Als voorschot daarop kan ik al van twee webapplicaties een model tonen.
Dan heb je een idee van hoe je het ontwerp (en het resultaat) van zo'n web-applicatie in een model zou kunnen weergeven.

- [Object Model van Gomoku Web Applicatie](img/cbe3718e7b43463dac9eb9d34813efde29d367f8.svg)
- [Object Model van Teambuilder Web Applicatie](img/b72bafbba921788650df88c06f5deb609802d306.svg)
