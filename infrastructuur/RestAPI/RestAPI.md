## Creating a Rest API in Python

We will need to make a simple Restfull API to demonstrate how to use POST and GET methods from you microcontroller. I will use a part of the ti-lab-shop data items as a source for the REST-data. FastAPI seems like a nice package to create our API. source: [https://fastapi.tiangolo.com/tutorial/first-steps/](https://fastapi.tiangolo.com/tutorial/first-steps/)

```bash
mkdir RestAPI
cd RestAPI/
python3 -m venv ./venv
source venv/bin/activate
python3 -m pip install fastapi
```

First make a example.py in your projectfolder. 

```python
from fastapi import FastAPI, HTTPException

# these are defined
LA = "1"
X = "1"

# Define items as a list of dictionaries
items = [
    {"name": "Resistor 100 Ohm", "price": 0.01, "free": 1, "place": f"{LA}, {X}, Y1", "path": "resistor", "image": "r-100-th.jpg", "text": "resistor 100 (brown black brown)"},
    {"name": "Resistor 1 KOhm", "price": 0.01, "free": 1, "place": f"{LA}, {X}, Y2", "path": "resistor", "image": "r-1k-th.jpg", "text": "resistor 1k (brown black red)"},
    {"name": "Resistor 10 KOhm", "price": 0.01, "free": 1, "place": f"{LA}, {X}, Y3", "path": "resistor", "image": "r-10k-th.jpg", "text": "resistor 10k (brown black orange)"},
    {"name": "Resistor 100 KOhm", "price": 0.01, "free": 1, "place": f"{LA}, {X}, Y4", "path": "resistor", "image": "r-100k-th.jpg", "text": "resistor 100k (brown black yellow)"},
    {"name": "LED 5 mm", "price": 0.10, "free": 1, "place": f"{LA}, {X}, Y5", "path": "led", "image": "led-5mm-th.jpg", "text": "LEDs 5mm through-hole"},
    {"name": "9V clip open end", "price": 0.10, "free": 1, "place": f"{LA}, {X}, Y6", "path": "power_connect", "image": "9v-clip.jpg", "text": "9V battery clip open end"}
]

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

I received an application startup complete. Now let test if our API can be accessed with URIs? The server on my system has an IP of http://127.0.0.1:8000. Let us try to list all the contents of our sample data.

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

Note that you can make changes to your source Python file while the server is running.
Show de docs:

```html
http://127.0.0.1:8000/docs
```

