### Installing Docker on Ubuntu

I use a Ubuntu VM machine on the Azure platform. I will log how much Docker will affect my Idle memory usage. 

```bash
cat /proc/meminfo
```
Next prepare for Docker installation. Source: [https://github.com/WCSCourses/index/blob/main/Docker_guide.md](https://github.com/WCSCourses/index/blob/main/Docker_guide.md)
First update.

```bash
sudo apt update && sudo apt upgrade -y
```

Install dependencies. Curl for example can be used to transport files using various network protocols.

```bash
sudo apt install -y apt-transport-https ca-certificates curl software-properties-common
```

Add the Docker GPG key.

```bash
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

Setup the Stable Repository.

```bash
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

Ready to install Docker.

```bash
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io
```

Use Docker commands without typing sudo.

```bash
sudo usermod -aG docker azureuser
```

In Semester 2 we already worked with [Docker and its commands](https://github.com/HU-TI-DEV/TI-S2/blob/main/infrastructuur/Docker/README.md).

