# Setting up environment

## Waarom gaat het fout? 

Meestal is de reden dat bv `MSYS2` wél een Python-Interpreter meebrengt, maar zonder de andere Python-tools zoals PIP.
- Tijdens de installatie van MSYS2 schrijft de installer de map met de tools ergens an het begin van jouw `PATH` omgevingsvariabele.
- Als je de naam van een programma intoetst (bv. `python`) dan zoekt Windows in alle mappen die in een lijst in de omgevingsvariabele `PATH` staan.
- Zodra Windows het eerste programma met een bijpassende naam gevonden heeft, wordt dit aangeroepen.
- Als het MSYS2-python.exe 'eerder' in de zoekpath staat dan een andere Python, dan wordt de tweede dus nooit gevonden.
- **Dan kan je de noodzakelijke certificaten niet installeren. Dit geeft een foutmelding.**

## Hoe kan ik dit oplossen?

1. Als je nog geen hebt, installeer een andere Python interpreter (inclusief de juiste pip tooling)
2. Maak een een `batch file` aan waarin je de `PATH` variabele naar de juiste Python Interpreter laat wijzen
3. Na het aanroepen van dit batch file run je dan het van `esp-idf\install.bat` aangegeven commando `python -m pip install certifi`
4. Daarna start je dan het `esp-idf\install.bat` opnieuw

### Hoe maak ik nu zo'n batch file aan? 

Daarvoor kan je (in een CMD.EXE terminal) ten eerste de inhoud van jouw bestaande `PATH` in een bestand schrijven.
Deze bewerken we dan met een editor (`notepad.exe` is voldoende):

```bash
C:\Espressif> path >set_env.bat
C:\Espressif> notepad set_env.bat
```

In Notepad schakel je dan het best onder het Menu `Format` de `Word Wrap` aan.  
Dan toont Notepad  een heel lange regel die begint met PATH=... met een lijst van mappen.

Het doel is deze `PATH` opniew to 'zetten', maar zonder overbodige (dubbele) onderdelen en vooal zonder mappen die ongewenste Python-versies bvatten (zoals MSYS2).

Daarvoor voegen we aan het begin een `SET ` toe en verwijderen dan van de ESP-IDF niet benodigde onderdelen uit de lijst van mappen.

Zo kan dat dan uitzien:

```bash
SET PATH=C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Docker\Docker\resources\bin;C:\Program Files\Git\cmd;C:\Espressif\Python\Python313\;
```
*voorbeeld PATH (een lange regel)*

Als je het liever meer overzichtelijk wil hebben kan je het `zetten` van de variabele `PATH` ook opsplitsen.

Dat ziet dan zo uit:

```bash
SET PATH=C:\WINDOWS\system32
SET PATH=%PATH%;C:\WINDOWS
SET PATH=%PATH%;C:\WINDOWS\System32\Wbem
SET PATH=%PATH%;C:\WINDOWS\System32\WindowsPowerShell\v1.0\
SET PATH=%PATH%;C:\WINDOWS\System32\OpenSSH\
SET PATH=%PATH%;C:\Program Files\Docker\Docker\resources\bin
SET PATH=%PATH%;C:\Program Files\Git\cmd;
SET PATH=%PATH%;C:\Espressif\Python\Python313\
```
*voorbeeld PATH (opgedeeld in onderdelen)*

> Het `PATH` gedeelte gaat voor iedereen iets anders zijn, experimenteer totdat je de juiste paden hebt.

Met `File` > `Save` sla je de wijzigingen op.

Dan kan je in jouw terminal het `set_env.bat` oproepen:

```bash
C:\Espressif> set_env.bat
SET PATH=C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Docker\Docker\resources\bin;C:\Program Files\Git\cmd;C:\Espressif\Python\Python313\;
C:\Espressif> 
```
(we zien als uitvoer wat in het set_env.bat staat)

Nu kunnen we de `PIP install`-beveel gebruiken en daarna opnieuw het `install.bat` proberen:

```bash
C:\Espressif> python -m pip install certifi
[downloading.... installing....]
C:\Espressif> cd esp-idf
C:\Espressif\esp-idf> install.bat
```

Als alles goed is loopt de installatie nu zonder (verdere) problemen door.

## Pro-tipp - export.bat aanroepen vanuit set_env.bat

Voor het ontwikkelen met de  ESP-IDF (Espressif Integrated Development Facility) is het nodig altijd een CMD.EXE-terminal te openen en het
export.bat script aan te roepen.

Daarvoor open je het set_env.bat en voeg een lijn toe:
```bash
SET PATH=.....
C:\Espressif\esp-idf\export.bat
```

> ALs je meer dan een batch-programma wil aanroepen dan moet een CALL vooraanstaan.
> Zie ook [call](https://stackoverflow.com/questions/1103994/how-to-run-multiple-bat-files-within-a-bat-file).

Veel succes!
