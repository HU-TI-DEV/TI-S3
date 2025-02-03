### Virtual Machine on Microsoft Azure

As a HU student you are eligible to trial use the Azure platform. You can receive 50 credits for a 3 moth period. Please contact the Semester Coordinator if you would like a Virtual Machine (VM) during this semester.

The VM was setup for me. I received a `.pem` file and will save this to a secure location. First open a command line.

```bash
mv ~/Downloads/harmsnippe.pem ~/.ssh/
```

We need to set the right permissions for this `.pem` file.

```bash
chmod 400 ~/.ssh/harmsnippe.pem
```

Find your public IP for this VM. Go to Azure Portal -> Virtual Machines -> Select your VM -> In Overview or under Networking tab. You can find the Public IP address. In my case `9.163.104.14`.

Now connect with SSH. Replaxe azureuser if your name is different.

```bash
ssh -i ~/.ssh/harmsnippe.pem azureuser@9.163.104.14
```