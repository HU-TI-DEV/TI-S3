Verhaal over aanmaken van een batch file met de volgende inhoud:


```
PATH=C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Docker\Docker\resources\bin;C:\Program Files\Git\cmd;C:\Espressif\Python\Python313\;
call esp-idf\install.bat
call esp-idf\export.bat
```
- Het path gedeelte gaat voor iedereen anders zijn..
- Je moet dan ook een python interpreter installeren.

CHECKEN MET HAGEN!