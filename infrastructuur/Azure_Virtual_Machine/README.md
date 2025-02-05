### Virtual Machine on Microsoft Azure

As a HU student you are eligible to trial use the Azure platform. This program is called 'HU Azure for Education'. Please contact the Semester Coordinator if you would like a Virtual Machine (VM) during this semester. [More about this service](https://github.com/kwintex/Azure4StudentProjects/blob/master/Documentation/UserManual.md#students).

The VM was setup for me. I received a `.pem` file and will save this to a secure location. First open a command line.

```bash
mv ~/Downloads/harmsnippe.pem ~/.ssh/
```

We need to set the right permissions for this `.pem` file.

```bash
chmod 400 ~/.ssh/harmsnippe.pem
```

Find your public IP for this VM. Go to Azure Portal -> Virtual Machines -> Select your VM -> In Overview or under Networking tab. You can find the Public IP address. In my case `9.163.104.14`.

Now connect with SSH. The azureuser is often used as the standard name. Replace if your name is different.

```bash
ssh -i ~/.ssh/harmsnippe.pem azureuser@9.163.104.14
```

There was not a response. In the logs we found that processes were being killed. After increasing the memory to 1GB a was able to login. Also the VM is shutdown during the night to save on costs. I tag my VM with `key="shutdown", value="no"`

## Installing nano

To edit text documents on the server I like to be able to use the program nano.

```bash
sudo apt update && sudo apt upgrade -y
sudo apt-get install nano
```

Now you can start nano from the commandline. For your applications you should use containers. Start with installing [Docker on Ubuntu](./Docker_on_Ubuntu.md).

Try to write your own [RestAPI](../RestAPI/README.md) and deploy it. Add a Flask webserver? Mongo DB?
