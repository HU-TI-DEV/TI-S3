# Opdracht STD naar Code - IR verzender
Deze opdracht gaat ervan uit dat je eerder een werkende oplossing voor een [ir-ontvanger](../std-code-ir-ontvanger/std-code-ir-ontvanger.md) hebt gemaakt.

- Houd tijdens het maken van deze opdracht in je **logboek** bij waar je tegenaan loopt.
- [Lees hier](../../../../hardware-interfacing/infraroodcommunicatie/README.md) over infrarood communicatie en in het bijzonder over het NEC-protocol en de hardware voor het verzenden van IR signalen.
- Ontwerp een STD voor het verzenden van groepen van 1 tot 8 bytes aan informatie via infrarood, gebruikmakende van het NEC protocol.
- Implementeer het in code met behulp van CleanRTOS.
- **Test** het resultaat door de informatie te ontvangen met de eerder gerealiseerde NEC-infrarood-ontvanger (op een andere esp32, of als je die niet hebt, op een andere thread op dezelfde esp32).
Verzend bijvoorbeeld teksten tot 8 karakters.
- Lever de uiteindelijke code, inclusief de testcode (de tweede commit) pas in op de bijbehorende canvas opdracht **zodra de test succesvol is**.
