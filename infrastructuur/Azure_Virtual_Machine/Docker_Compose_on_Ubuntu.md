### Installing Docker Compose on Ubuntu

Sometimes your application will consist of multiple Docker images that are dependent on each other. For this Docker Compose can help you simplify and make your deployment robust. 

[Docker should already be installed](./Docker_on_Ubuntu.md) on your system. I will login to my [VM on Azure](./README.md).

```bash
ssh -i ~/.ssh/harmsnippe.pem azureuser@9.163.104.14
sudo apt update && sudo apt upgrade -y
```

Install Docker Compose on your system

``` bash
sudo apt-get install docker-compose-plugin
```

On my system I had already installed Docker Compose `docker-compose-plugin is already the newest version (2.32.4-1~ubuntu.22.04~jammy).` To check your version or verify if it is already installed:

```bash
docker compose version
```

You now have all the tools to install [a server with Web Application](../ServerMetWebApplicatie/Gomoku_on_Ubuntu.md). 