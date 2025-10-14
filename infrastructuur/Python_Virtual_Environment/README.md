### Python Virtual Environment

To avoid dependency hell it is custom to use Python in a virtual environment (venv). This documents will show you the basics for starting a new Python project in a venv. source: [https://www.pythonguis.com/](https://www.pythonguis.com/tutorials/python-virtual-environments/?gad_source=1&gbraid=0AAAAAoRQ8xUfoibGbroBJeKqGokYN-P7a&gclid=Cj0KCQiAhvK8BhDfARIsABsPy4jpDuISLhiwhbeVlbeiXZhA_FNmcku5vlOj4hAE4PIugZE9olAAeEsaAhHgEALw_wcB)
Example is for Mac OS X with Python 3.13.1.


```bash
mkdir myproject
cd myproject/
```

```bash
python3 -m venv ./venv
ls
```

You will have a folder called venv in your projectfolder. The folder venv is a commonly accepted name. You can now install all packages you need for your project. To start using the virtual environment we have to activate it.

```bash
source venv/bin/activate
```

Your prompt is has now changed and the virtual environment is activated. We can now safely test and install packages we need. In the folder you can run Python files using `Python3 example.py` For a project where I needed to replace html links for Markdown formatted links beautifulsoup4 package is installed.

```bash
(venv) $ python -m pip install beautifulsoup4
```

To quit a virtual environment use:

```bash
(venv) $ deactivate
```

## Python processes

To view all running Python processes you can do the following.

```bash
ps -ef | grep python
```

If needed you can kill them by their process id. Example given, killing Python process with id 2430.

```bash
kill -9 2430
```

## Run as a service

When your system is depending on your Python software it is wise to run these components as a service. In case of a restart service can than be configured to start automatically.

First create a service file.

```bash
[Unit]
Description=My application
After=network.target

[Service]
ExecStart=/path/to/your/virtualenv/bin/python3 /path/to/your/my_application.py
WorkingDirectory=/path/to/your/project/directory
Restart=always
User=your_user_name

[Install]
WantedBy=multi-user.target
```

To find the path of your Python binary use.

```bash
which python  # While your virtual environment is active
```

Save it in the following directory '/etc/systemd/system/my_application.service'

Reload systemd.

```bash
sudo systemctl daemon-reload
```

Enable the service.

```bash
sudo systemctl enable my_application.service
```

Start the service.

```bash
sudo systemctl start my_application.service
```

Show the status of the service.

```bash
sudo systemctl status my_application.service
```

## View logs

Show the logs of your application.

```bash
journalctl -u my_application.service
```

Only log messages from the current boot.

```bash
journalctl -u my_application.service -b
```