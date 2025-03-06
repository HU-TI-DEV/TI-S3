Waarom gaat het fout? Meestal is de reden dat bv MSYS2 een Python-Interpreter meebrengt, maar zonder de tools zoals PIP. Dan kan je de noodzakelijke certificaten niet installeren. Dit geeft een foutmelding.

Oplossing is:
- installeren van een andere python interpreter (inclusief de juiste pip tooling)
- een batch file aan maken (bv set-env.bat) waarin je de path variabelen naar de juiste python interpreter laat wijzen.

Dit laatste doe je door een .bat aan te maken met de volgende inhoud:
```
PATH=C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Docker\Docker\resources\bin;C:\Program Files\Git\cmd;C:\Espressif\Python\Python313\;
call esp-idf\install.bat
call esp-idf\export.bat
```
- *Het path gedeelte gaat voor iedereen anders zijn, experimenteer totdat je de juiste paden hebt.
- de call in de .bat is nodig omdat hij anders na install.bat ermee ophoudt. Zie ook [call](https://stackoverflow.com/questions/1103994/how-to-run-multiple-bat-files-within-a-bat-file).

Veel succes!
