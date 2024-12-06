# Testen

Het testen van code is opgesplitst in een verzameling van tests. Unit tests voor de kleinste eenheden, integratie tests voor de samenwerking van eenheden en systeem tests voor het geheel.

Bijvoorbeeld unit tests voor de klassen die volgen uit boundary objecten. Aparte tests voor control objecten die gebruik maken van die boundary objecten. En uiteraard natuurlijk tests voor het systeem als geheel.

## Criteria 
- Er is een markdown bestand met daarin een **testplan**. 
Daarin wordt aangegeven **hoe** de betreffende tests uitgevoerd kunnen worden. Het kan gaan om het starten van een testprogramma, het aansluiten van hardware, het uitvoeren van handelingen, etc.
- Vooral de unit tests kunnen **geautomatiseerd** worden.
- Voor integratie-tests kan dat vaak ook, door een deel van het systeem te simuleren (door **stubs** te gebruiken voor de echte hardware / andere klassen).
- Zorg ervoor dat de tests **reproduceerbaar** zijn.
- Zorg ervoor dat **alle publieke functies** getest worden.
- En eventueel ook complexe **private functies**. 
- Zorg ervoor dat de **grenzen** van die functies getest worden.
- Zorg ervoor dat de **foutafhandeling** getest wordt.
- Zorg ervoor dat de **laatste testresultaten / laatste testrapport** voorzien is van een datum en tijd, en dat dingen die (nog) niet werken er duidelijk in zijn aangegeven. 
- Gebruik bijvoorbeeld in de repo van het project de volgende structuur voor tests:
    - tests/
        - unit/
          - test_class1/
            - docs/
            - src/
            - testresults/
          - test_class2/
            - docs/
            - src/
            - testresults/
        - integration/
          - test_class1_class2
            - docs/
            - src/
            - testresults/
        - system/
            - test_system
                - docs/
                - src/
                - testresults/
