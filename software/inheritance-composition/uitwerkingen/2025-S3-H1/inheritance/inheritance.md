# Voor- en nadelen van inheritance

## Voordelen

| Voordeel | Uitleg |
|---------|--------|
| **Hergebruik van code** | Bestaande functionaliteit kan in meerdere klassen worden gebruikt zonder dat je dezelfde code opnieuw schrijft. Je hebt een parent en daar kan je telkens wat van pakken. |
| **Voorkomt duplicatie van code** | Functies en eigenschappen worden in één klasse gedefinieerd en kunnen door andere klassen worden overgenomen. Je hebt een parent en je kan daarvan alles pakken zodat er niks dubbel wordt geschreven. |
| **Eenvoudig uitbreidbaar** | Nieuwe klassen kunnen bestaande klassen uitbreiden en alleen de extra functionaliteit toevoegen die nodig is. De parent blijft hetzelfde en je kan extra dingen toevoegen in een andere class. |

## Nadelen

| Nadeel | Uitleg |
|--------|--------|
| **Fragiele basisklasse** | Als de basis- of superklasse verandert, kunnen subklassen onverwachte fouten of problemen krijgen. |
| **Diamant-probleem** | In sommige talen kan een subklasse meerdere keren dezelfde methode erven via verschillende paden, wat tot verwarring of errors kan leiden. |

---

## Wat zijn goede voorbeelden?

Een goed voorbeeld is een *parentklasse* **Dier**, die functies heeft zoals *eten* en *slapen*.

---

## Waar gaat het vaak fout?

### **Verkeerd gebruik van overerving**
Veel mensen gebruiken overerving alleen om code te hergebruiken, maar dat is niet de bedoeling. Je moet het alleen doen als er echt een *is-een* relatie bestaat.

### **Te diepe hiërarchieën**
Programmeurs bouwen soms enorme stambomen van klassen. Na een week snapt niemand de structuur meer, wat onderhoud moeilijk maakt.

### **Diamond-probleem**
Ontstaat bij meervoudige overerving: twee klassen erven van dezelfde basisklasse en de compiler weet niet meer welke versie hij moet gebruiken.

### **Te sterke koppeling**
Als je één basisklasse aanpast, moet je ineens overal in de code iets veranderen. Dat maakt het systeem kwetsbaar en slecht uitbreidbaar.

---

## UML diagrams – Inheritance

Dit is een voorbeeld van een UML-diagram waar inheritance voorkomt.  
De subklassen **Admin** en **Customer** erven van de basisklasse **User**.  
De functies en attributen die in `User` staan, worden dus meegenomen naar de subklassen — bijvoorbeeld `username` en `password`.

De attributen en functies die alleen in `Admin` of `Customer` staan, worden niet teruggeërfd door de parent.

De UML-diagram laat dus zien hoe inheritance wordt toegepast.

![UML](link naar de foto)

---

## Gemaakt door

- Freya van den Berg (UML diagram)
- Aya Brocatus 
- Radeiaan Nandoe
- Sjors Jansen
- Axl Schoenmakers
- Thor Oudejans
- Zakaria Ahmed
- Samuel Epp
- Casper van Mourik
- Nick Netsounski (pookie, aka Martin)
- Adriaan Abrahamse
- Tim Koning
- Kaj Boogaard
- Jochem Hoekstra
- Anton Steeghs
- Pepijn de Vries ❤️

---

## Bronnen

- https://www.uml-diagrams.org/inherited-property.html  
- https://en.cppreference.com/book/intro/inheritance  
- https://www.geeksforgeeks.org/cpp/inheritance-in-c  
- https://30dayscoding.com/blog/advantages-and-disadvantages-of-inheritance-in-cpp  
- https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/  
- https://stackoverflow.com/questions/418308/what-does-the-symbol-mean-in-a-uml-class-diagram  
- https://stackoverflow.com/questions/406081/why-should-i-avoid-multiple-inheritance  
- ChatGPT & andere generatieve AI
