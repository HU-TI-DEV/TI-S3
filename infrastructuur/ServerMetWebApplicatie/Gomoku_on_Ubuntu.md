### Installing WebApp Gomoku on Ubuntu

I have a [VM on Azure with Ubuntu](../Azure_Virtual_Machine/README.md). [Docker](../Azure_Virtual_Machine/Docker_on_Ubuntu.md) and [Docker Compose](../Azure_Virtual_Machine/Docker_Compose_on_Ubuntu.md) are installed. I will install the example application from the Git repositry.

The [example application Gomoku](https://github.com/HU-TI-DEV/VoorbeeldWebApp_Gomoku) can be installed using Docker Compose.

```bash
ssh -i ~/.ssh/harmsnippe.pem azureuser@9.163.104.14
sudo apt update && sudo apt upgrade -y
```

I will clone the Gomoku webapp in a named directory gomoku.

```bash
git clone https://github.com/HU-TI-DEV/VoorbeeldWebApp_Gomoku.git gomoku
```

You can use this as a template for your own Web Application. Follow the instructions explained [here](../ServerMetWebApplicatie/README.md#opzetten-van-server-en-de-voorbeeld-webapplicatie) to set up you team application. I just want to check if I can start all imgaes with Docker Compose.

I inspect the `docker-compose.yml` file. I create a password for the root user.

```bash
cd gomoku
nano docker-compose.yml
```

Create a password for the following variables.

```
MONGO_INITDB_ROOT_PASSWORD
APP_SECRET_KEY
```
Save and quit. 
You can first check if Docker and Docker Compose are installed.

```bash
docker --version
docker compose --version
```

Now try an run Docker Compose with this YAML file. We can start the application with the `up` command. With `-d` you can run the app in the background.

```bash
docker compose up -d
```

Check if our app is working: '9.163.104.14:5001'. Do not forget to open your port. I receive a 404 URL not found and see it as a good sign. Inspect the code and find that the enttry point to the game is here [`http://9.163.104.14:5001/gomoku/start`](http://9.163.104.14:5001/gomoku/start)

I made some changes to the html front-end. This is how I copied the file:

```bash
scp -i ~/.ssh/harmsnippe.pem play_gomoku.html azureuser@9.163.104.14:~/gomoku/gomoku/templates
```

If you need a restart use:

```bash
docker compose restart gomoku
```