## Creating a Rest API in Python

We will need to make a simple Restfull API to demonstrate how to use POST and GET methods. I will use a part of the ti-lab-shop data items as a source for the REST-data. FastAPI seems like a nice package to create our API. source: [https://fastapi.tiangolo.com/tutorial/first-steps/](https://fastapi.tiangolo.com/tutorial/first-steps/)

```bash
mkdir RestAPI
cd RestAPI/
python3 -m venv ./venv
source venv/bin/activate
python3 -m pip install fastapi
```

First make a example.py in your projectfolder. I have Json data file for all the TI lab shop items. I will use that as my data source. 

```python
from fastapi import FastAPI, HTTPException
import json
import os

# Open and load JSON file
with open(os.path.join(os.path.dirname(__file__), 'items.json')) as file:
    items = json.load(file)  # items is now a dictionary

app = FastAPI()

@app.get("/v1/items")
def get_items():
    return {"items": items}

@app.get("/v1/items/list")
def list_all_items():
    return [item["name"] for item in items]

@app.get("/v1/items/{item_name}")
def get_item(item_name: str):
    for item in items:
        if item["name"].lower() == item_name.lower():
            return item
    raise HTTPException(status_code=404, detail="Item not found")
```

Now we should run the live server. 

```bash
pip install "fastapi[standard]"
fastapi dev example.py
```

I received an "application startup complete". Now how can we test if our API can be accessed with URIs? 

The server on my system has an IP of http://127.0.0.1:8000. <!-- markdown-link-check-disable-line -->

I will try to list all the contents of our sample data.

```html
http://127.0.0.1:8000/v1/items
```

Try our own GET method list.

```html
http://127.0.0.1:8000/v1/items/list
```

Request a specific item
```html
http://127.0.0.1:8000/v1/items/Resistor%20100%20Ohm
```

Note that you can make changes to your source Python file while the server is running. It will automatically note changes and restart the server.

Show the docs that are generated for you:

```html
http://127.0.0.1:8000/docs
```

Now you are ready to [deploy your first RestAPI on a server](./FastAPI_on_VM.md).