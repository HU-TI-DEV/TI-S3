### Deploy simple RestAPI with FastAPI on a Virtual Machine

You need a Virtual Machine or use Ubuntu in a Docker Container to create a RestAPI. In this example I am running a Ubuntu 
22.04.5 VM on the Azure platform. Ssh into your system then upgrade and install the packages.

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install python3 python3-pip python3-venv -y
```

We then create a folder for you [RestAPI](README.md) and create a [venv](../Python_Virtual_Environment/README.md). 

```bash
mkdir RestAPI
cd RestAPI
python3 -m venv venv
source venv/bin/activate
```

Now you can safely install the dependencies in the activated venv.

```bash
pip install fastapi uvicorn
```

We already made an RestAPI. I will copy this source file to the remote directory using `scp`.

```bash
scp -i ~/.ssh/harmsnippe.pem example.py azureuser@9.163.104.14:~/RestAPI/main.py
scp -i ~/.ssh/harmsnippe.pem items.json azureuser@9.163.104.14:~/RestAPI
```

Next run FastAPI using uvicorn

```bash
uvicorn main:app --host 0.0.0.0 --port 8000 --reload
```

The server has started. I can not reach the API using http://9.163.104.14:8000 and suspect the port is blocked. In the Azure platform I add a new security role under Networking -> Network settings for port 8000. Now that helps. I can access the RestAPI on [http://9.163.104.14:8000/v1/items/list](http://9.163.104.14:8000/v1/items/list).

We would like our application to start and stop with Systemd.

```bash
pip install gunicorn
```

Create a service file for FastAPI

```bash
sudo nano /etc/systemd/system/fastapi.service
```

With the following content:

```bash
[Unit]
Description=FastAPI application
After=network.target

[Service]
User=ubuntu
Group=ubuntu
WorkingDirectory=/home/ubuntu/fastapi-app
ExecStart=/home/ubuntu/fastapi-app/venv/bin/gunicorn -w 4 -k uvicorn.workers.UvicornWorker main:app --bind 0.0.0.0:8000
Restart=always

[Install]
WantedBy=multi-user.target
```

Enable and start your service like this:

```bash
sudo systemctl daemon-reload
sudo systemctl enable fastapi
sudo systemctl start fastapi
sudo systemctl status fastapi
```