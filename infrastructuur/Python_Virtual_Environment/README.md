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

You will have a folder called venv in your projectfolder. The folder venv is a commonly accepted name. You can not install all packages you need for your project. To start using the virtual environment we have to activate it.

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