# C++ bouwen met VSCode (Windows)
- Eerst C++ en C++ extension packs installeren.

- Vervolgens ergens g++ installeren [door MinGw64 te installeren](https://code.visualstudio.com/docs/cpp/config-mingw).
  .. de installpackage heet msys2 en heb ik geinstalleerd in default folder ervoor: c:\msys64

- In de "MSYS2 UCRT64" prompt die opent het pacman commando van de bovenstaande webpagina uitvoeren. Die vraagt wat van MinGW64 te installeren. Ik kies default/ alles.

- Als je nu in windows (bij opstarten) "MSYS2" typt, dan zie je dat je een heleboel bash-shells kunt opstarten, waarvan eentje MSYS2 MinGW 64.

- Voeg C:\msys64\ucrt64\bin toe aan het user envrionment variables path van windows in control-panel.

- Dan starten met:``code .`` **vanaf de command line** (althans, de eerste keer, als je dan eerst VSCode opent werkt het niet). Dan lijkt het te werken als je Run and Debug klikt of de g++ compiler selecteert. 

- De output van de couts verschijnt in de terminal (niet in de debug console) van vscode.

NB: bovenstaande is een log van mijn persoonlijke ervaringen, en dus een momentopname. Het kan zo maar zijn dat bepaalde details inmiddels anders zijn.