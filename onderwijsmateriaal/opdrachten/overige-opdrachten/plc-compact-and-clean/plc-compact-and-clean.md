# PLC Compact and Clean
## Inleiding
Dit is een Extra Opdracht voor wie in een regenachtig weekend zijn PLC-ervaring wat wil vergroten. Voor de opdracht maken we gebruik van FX2N mitsubishi PLC clones. Dat is een goedkoop type (relatief) eenvoudige PLC's waar Harm een hele doos van heeft staan. Een zo'n PLC bevat maar 4 inputs en 2 outputs. Om deze opdracht niet te lastig te maken, beperken we hem, zodat we maar 1 zo'n PLC nodig hebben.

## Opdracht: Compact and Clean
Een aanbevolen opdracht voor een enkele FX2N is uit te gaan van [dit compact en clean ontwerp](../../../readers/compact-and-clean.pdf), en dat te implementeren op een F2XN PLC, waarbij de output mapping is weggelaten. Als je aan de twee outputs leds vastmaakt, zie je dus letterlijk de toestanden bestaande uit 2 bits circulair veranderen afhankelijk van de input button R.
Er zijn dan naast de PLC alleen 2 leds, 1 button en 3 weerstanden nodig. (dus geen flipflops en logica: dat gedrag maak je met de PLC: een uitgangspin komt overeen met de uitgang van een flipflop)

## Werking van de FX2N PLC 
Het is het handigst om eerst een "hello-world" aan de praat te krijgen: maak een ingang met een knopje hoog, en de uitgang laat een ledje branden. Vervolgens bestuderen hoe dat ding werkt. Wellicht komt het logboek dat ik zelf bijhield tijdens mijn experimenten met deze PLC van pas:
- [Logboek GxWorks2](../../../../infrastructuur/PLC/log_GxWorks2.md)
