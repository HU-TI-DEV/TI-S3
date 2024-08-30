## Doeltreffende numerieke wiskunde

### Inleiding
Twee eenvoudig bruikbare doch krachtige numerieke methoden die elke Technisch Informaticus in zijn toolkit zou moeten hebben, zijn de **Tailor reeks** en de **Newton Raphson** methode. De enige wiskunde die je voor beide methoden nodig hebt, is het kunnen bepalen van afgeleiden, maar eigenlijk zelfs dat niet, want dat kun je tegenwoordig eenvoudig met [Wolfram Alpha](https://www.wolframalpha.com/input?i=derivative+of+%5B%2F%2Fmath%3Alog%28x+%2B+2%2Fx%29+-+x%5E2%2F%2F%5D).

### Tailor reeks
Stel dat je microcontroller een bepaalde wiskundige operatie niet ondersteunt, of je wilt hem compile-time gebruiken en je compiler biedt geen constexpr variant aan, bijvoorbeeld voor een sinus of log functie. In zo'n geval kun je dergelijke functies zelf maken via een **tailor ontwikkeling**. [Deze pagina](https://en.wikipedia.org/wiki/Taylor_series) vertelt er meer over. Het enige wat je uiteindelijk gebruikt is de formule die zegt f(x) is bij benadering f(a) + f'(a)/1! + ..
De a is een x-as waarde rond waar je de benadering wilt maken. Vaak wordt a=0 gekozen. De benadering voor f(x) wordt nauwkeuriger als je meer termen toevoegt, en/of als x dichter bij a ligt.

### Newton Raphson
Newton Raphson is een andere numerieke methode, waarmee je in veel gevallen een vergelijking numeriek kunt oplossen, waarbij het moeilijk is om dat symbolisch te doen. Bijvoorbeeld: log(x + 2/x) - x^2 = 0. Lastig of onmogelijk om analytisch op te lossen, maar met Newton Raphson niet moeilijk wel numeriek te benaderen.
[Deze pagina](https://www.geeksforgeeks.org/newton-raphson-method/) legt het denk ik wel overzichtelijk uit.
Kanttekening: bij de eerste examples passen ze maar een iteratiestap toe. Typisch pas je (zoals bij Problem 4) meerdere iteratiestappen toe, en stop je als de absolute verandering van het benaderde antwoord onder een bepaalde drempel komt.
Ook voor het benaderen van een eenvoudige functie kan Newton Raphson afhankelijk van de functie waar het om gaat sneller convergeren dan een Tailor ontwikkeling. Je kunt dat wiskundig bewijzen of gewoon uitproberen met wat testcode.
