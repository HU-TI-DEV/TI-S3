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

There was not a response. In the logs we found tha processes were beigin killed. After increasing the memory to 1GB a was able to login. Also the VM is shutdown during the night to save on costs. I tag my VM with `key="shutdown", value="no"`

Try to deploy your own [RestAPI](../RestAPI/README.md) or Flask webserver.
