# WSL instantie van Ubuntu_22_04_LTS opzetten

- Ik heb eerst de Ubuntu 22.04 LTS **uit de MS Store** geinstalleerd.
- Vervolgens een image ervan **gexporteerd naar tar**. (nu hij nog schoon is):
  - wsl --export Ubuntu-22.04 ubuntu-22_04.tar
  - Die tar geplaatst in D:\WSL (vind ik een mooie plek)
- Uit die tar image een **nieuwe Ubuntu WSL** geinstalleerd:
  - open eerst met **admin rights** een **windows powershell**
  - wsl --import U2204_RollatorNavigatie "D:\WSL\Ubuntu-22_04" "D:\WSL\ubuntu-22_04.tar"
- Met wsl --list --verbose kun je vervolgens **controleren** dat er een linux machine is toegevoegd met de naam "U2204_RollatorNavigatie".
- Open **een prompt in de specifieke WSL** met:
  - wsl -d U2204_RollatorNavigatie

Ik zie dan deze prompt:  
root@Marius2022:/mnt/d/WSL/U2204_RollatorNavigatie#

Ook zul je zien dat in de Windows verkenner helemaal links een "Linux" schijf bestaat met een subfolder met de naam "U2204_RollatorNavigatie".

### Wat betekent die mnt?
Je bent feitelijk tegelijkertijd in een tijdelijk gemounte (dwz aan de prompt gekoppelde) windows folder en in een folder in de linux folder hierarchy.
Als je niks expliciet maakt, wordt eerst gekeken in de huidige gemounte windows folder, daarna volgens mij in de huidige linux folder. Daarna pas naar paden in het windows path en linux path. Je kunt ook de mount on the fly aanpassen:  
cd /mnt/d/Documents  
Daardoor kun je in windows folders naar keuze met ubuntu commando's dingen met je windows files doen: cat, grep, python commandos uitvoeren.

Gebruik voor de zekerheid expliciete paden, zodat duidelijk is uit welke folderhierarchy een file wordt gebruikt in het geval in beide hierarchiën dezelfde namen voorkomen:  

- python /mnt/d/Documents/process_file.py   
- python /home/username/process_file.py

### Alleen de linux prompt zien
Zorg er nu voor dat je alleen de linux ziet:
- cd ~   
- cd ..
Als je nu intypt:
- ls
Dan zie je als het goed is de linux folders, waaronder de home folder.

### Docker installeren
- cd verder door naar je home/username directory. In mijn geval: /home/marius
- maak in die directory een folder met de naam docker aan:
  - mkdir docker  
  - cd docker   
  Het actieve pad is bij mij nu /home/marius/docker
  (dat lijkt me een logische naam voor docker gerelateerde dingen)  

Voor het installeren van docker probeerde ik:  
[Install Docker Engine on Ubuntu | Docker Docs](https://docs.docker.com/engine/install/ubuntu/)

.. maar dat gaf een rare error.  

Toen heb ik de convenience script geprobeerd:  
curl -fsSL https://get.docker.com -o get-docker.sh

sudo sh get-docker.sh

Dat lijkt gewerkt te hebben.

### Docker-compose installeren
Vervolgens docker-compose installeren met pip3 gaf dat een versie die een rare error gaf.

Daarom op aanraden van chatgpt de laatste versie geinstalleerd:

```
sudo curl -L "https://github.com/docker/compose/releases/download/$(curl -s https://api.github.com/repos/docker/compose/releases/latest | grep -oP '"tag_name": "\K(.*)(?=")')/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
```

sudo chmod +x /usr/local/bin/docker-compose

Dat werkte het wel.

Binnen die docker folder gaan we nu subfolders maken voor bij elkaar horende docker containers. Die containers kunnen dan vanuit de desbetreffende subfolders in een keer gestart of gestopt worden via een "docker-compose" commando. 

Volg daarvoor de beschrijving in [log_Opzetten_van_Server_en_Webapplicatie.md](./log_Opzetten_van_Server_en_Webapplicatie.md).