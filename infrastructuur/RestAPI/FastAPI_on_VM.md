### Deploy simple RestAPI with FastAPI on a Virtual Machine

You need a Virtual Machine or use Ubuntu in a Docker Container to create a RestAPI. In this example I am running a Ubuntu 
22.04.5 VM on the Azure platform. Ssh into your system then upgrade and install the packages. In this environment I will run a [Docker](../Azure_Virtual_Machine/Docker_on_Ubuntu.md) for the Rest application. On my local machine I have prepared this app with the following files and directory structure. source [https://fastapi.tiangolo.com/deployment/docker/#create-the-fastapi-code](https://fastapi.tiangolo.com/deployment/docker/#create-the-fastapi-code)

```txt
RestAPI/
│── app/
│   ├── __init__.py
│   ├── main.py
|   ├── items.json
│── requirements.txt
│── Dockerfile
│── docker-compose.yml

```

I already [made a RestAPI](./README.md) with FastAPI. The `__init__.py` is an empty file.

In the `requirements.txt` file I add the following:

```txt
fastapi[standard]
```

Then create a Dockerfile with this content:

```txt

FROM python:3.10

WORKDIR /code

COPY ./requirements.txt /code/requirements.txt

RUN pip install --no-cache-dir --upgrade -r /code/requirements.txt

COPY ./app /code/app

COPY ./app/items.json /code/app/items.json

CMD ["fastapi", "run", "app/main.py", "--port", "8000"]
```

Login to your VM on Azure. Then create a directory for the app.

```bash
mkdir RestAPI
```

 I will copy the source files to the remote directory using `scp`. Navigate with a terminal window to your local saved files. With `scp` you can copy files `scp -i ~/.ssh/harmsnippe.pem example.py azureuser@9.163.104.14:~/RestAPI/destination_example_file.py`. Using the -r flag you should be able to copy a complete directory. This does not work for me? I copy the important files from my local folder to the remote server. I created the directories remotely.

```bash
scp -i ~/.ssh/harmsnippe.pem docker-compose.yml azureuser@9.163.104.14:~/RestAPI
scp -i ~/.ssh/harmsnippe.pem Dockerfile azureuser@9.163.104.14:~/RestAPI
scp -i ~/.ssh/harmsnippe.pem requirements.txt azureuser@9.163.104.14:~/RestAPI
cd app
scp -i ~/.ssh/harmsnippe.pem main.py azureuser@9.163.104.14:~/RestAPI/app
scp -i ~/.ssh/harmsnippe.pem items.json azureuser@9.163.104.14:~/RestAPI/app
scp -i ~/.ssh/harmsnippe.pem __init__.py azureuser@9.163.104.14:~/RestAPI/app
```

Navigate to the RestAPI folder on the VM. Build and run the Docker.

```bash
docker build -t restapi .
```

Repositry name must be lowercase. Run the container:

```bash
docker run -d --name restapi-container --restart unless-stopped -p 8000:8000 restapi
```

The server has started. I can not reach the API using http://9.163.104.14:8000 and suspect the port is blocked. In the Azure platform I add a new security role under Networking -> Network settings for port 8000. Now that helps. I can access the RestAPI on [http://9.163.104.14:8000/v1/items/list](http://9.163.104.14:8000/v1/items/list) and the [docs](http://9.163.104.14:8000/docs).
