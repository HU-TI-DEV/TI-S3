## Het Apparaat : een 3D Printer

Je zusje is heel verdrietig. De dop van haar balpen is zoek. Ze wil een 3D printer om een nieuwe te printen. Aardig als je bent, besluit je een 3D Printer voor haar te ontwerpen.

## GCode

Een 3D Printer is een apparaat dat commando's kan uitvoeren die staan in een bestand met "gcode". G-code commando's sturen de machine aan, instruerend waar naartoe te bewegen, hoe snel te bewegen en welk pad te volgen.

Voor 3D-printers wordt G-code gegenereerd door slicer-software, die een 3D-model vertaalt naar een instructieset voor de printer om het object laag voor laag te creëren.

Het gebruik van de belangrijkste G-code commando's wordt hier geïllustreerd: [GCode](../bronnen/g-code.md)

## Use cases

Voordat we de 3D Printer gaan maken, is het natuurlijk handig om in kaart te brengen wat we nu eigenlijk willen dat hij voor ons doet.  
Bedenk enkele use cases die relevant kunnen zijn voor dit apparaat. Wat moet je allemaal met zo'n ding kunnen doen?  
Brainstorm (eventueel met een medestudent) via bijvoorbeeld een mindmap.

### A) Use Case Diagram

De klant (je zusje) had zo haar eigen ideeën over wat het apparaat moet kunnen. In haar beleving is er een relevante actor, de gebruiker. Verder zijn volgens haar de relevante usecases: UC01_HoofdmenuNavigeren, UC02_3DModelSelecteren, UC03_3DPrinten en UC04_PrinterOnderhouden.  
De laatstgenoemde use case bevat op zijn beurt de sub-usecases UC05_ExtruderLeegmaken en UC06_ExtruderLadenMetNieuwMateriaal.

Creeer een overzicht van deze wensen van je zusje door een Use Case Diagram van de 3D-printer te maken.  
**Vergeet niet:**

- De systeemgrens
- De actor(en)
- Eventuele onderlinge relaties

Let in het bijzonder op de volgende criteria:
- [Criteria Use Case Diagram](../../../../../leerdoelen/portfolio-items/use-case-diagram.md)
- [Criteria Use Case Beschrijvingen](../../../../../leerdoelen/portfolio-items/use-case-beschrijving.md)

### B) Use Case Beschrijvingen

Ons use case diagram geeft ons een handig overzicht van wat we willen dat de printer doet. Nu willen we voor elke use case een beschrijving, zodat we wat precieser te weten komen wat het apparaat nu precies moet gaan doen.

Je zusje helpt je alvast een beetje op weg door de use case beschrijving van use case UC01_HoofdmenuNavigeren alvast voor je uit te schrijven:

<table style="border-collapse: collapse; border-style: solid;" border="1">
    <colgroup>
        <col style="width: 18%;" />
        <col style="width: 81%;" />
    </colgroup>
    <thead>
        <tr class="header">
            <th colspan="2">UC01_HoofdmenuNavigeren</th>
        </tr>
    </thead>
    <tbody>
        <tr class="odd">
            <td><strong>Actor</strong></td>
            <td>Gebruiker</td>
        </tr>
        <tr class="even">
            <td><strong>Samenvatting</strong></td>
            <td>Gebruiker navigeert door het hoofdmenu om toegang te krijgen tot verschillende functionaliteiten van de 3D-printer.</td>
        </tr>
        <tr class="odd">
            <td><strong>Preconditie</strong></td>
            <td>Gebruiker start de 3D-printer op, of is teruggekeerd uit een sub-menu.</td>
        </tr>
        <tr class="even">
            <td><strong>Beschrijving</strong></td>
            <td>
                <ol type="1">
                    <li>
                        <p>Het systeem toont het hoofdmenu met de verschillende opties: '3D-Model Selecteren&rsquo;, '3D-Printen&rsquo; en &lsquo;Printer Onderhouden&rsquo;. Onderaan wordt de filenaam van het laatst geselecteerde 3D-model weergegeven.</p>
                    </li>
                    <li>
                        <p>Gebruiker selecteert een optie uit het hoofdmenu.</p>
                        <ol type="a">
                            <li>
                                <p>Als de gebruiker '3D-Model Selecteren&rsquo; selecteert, start UC02_3DModelSelecteren.</p>
                            </li>
                            <li>
                                <p>Als de gebruiker '3D-Print' selecteert, start UC03_3DPrinten.</p>
                            </li>
                            <li>
                                <p>Als de gebruiker 'Printeronderhoud' selecteert, start UC04_PrinterOnderhouden.</p>
                            </li>
                        </ol>
                    </li>
                    <li>
                        <p>Na het voltooien van een een van bovenstaande usecases wordt weer teruggekeerd naar UC01_HoofdmenuNavigeren.</p>
                    </li>
                </ol>
            </td>
        </tr>
        <tr class="odd">
            <td><strong>Invariant</strong></td>
            <td>Zolang er sinds het opstarten van de 3D-printer nog geen 3D-model is geselecteerd, wordt de betreffende filenaam niet onderaan het menu weergegeven, en is de optie &lsquo;3D-Print&rsquo; grayed-out / niet selecteerbaar.</td>
        </tr>
    </tbody>
</table>

Natuurlijk, hier is de aanvullende HTML-tekst omgezet naar Markdown:

---

UC04_PrinterOnderhouden gebruikt op zijn beurt weer de sub use cases UC05_ExtruderLeegmaken en UC06_ExtruderLadenMetNieuwMateriaal.

Zoals je ziet aan het bovenstaande voorbeeld van je zus, bestaat een use case beschrijving uit een tabel met het volgende:

- **Naam** (moet functionaliteit uitdrukken)
- **Doel** (doel welk doel beoogt de actor met het uitvoeren van de use case)
- **Pre-conditie(s)** (in welke toestand is het systeem bij het begin van de uitvoering*)
- **Post-conditie(s)** (in welke toestand is het systeem na afloop van de uitvoering*)
- **Beschrijving** (een scenario die deze use case toelicht)
- **Uitzonderingen** (welke zijn de bijzondere gevallen die kunnen optreden*)  
  * Voor zover relevant

Ontwerp nu zelf de tabellen met use case beschrijvingen voor de overige 5 use cases.

### Canvas opdracht
Lever de commit-link naar het markdown document van je uitwerking in bij de Canvas Opdracht "3D Printer Serie".
