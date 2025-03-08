### GET and POST requests using ESP32 C6

It always nice to be able to do GET and POST request from your device. First let us try to compile and flash the example http-request. Then we will integrate this code as a library in our lasergame_template_2.

```bash
get_idf 
cp -r $IDF_PATH/examples/protocols/http_request .
cd http_request/ 
idf.py set-target esp32c6
```

We need to set the WiFi credentials in menuconfig.

```bash
idf.py menuconfig
```

In the Example Configuration menu:

- Use `WiFi SSID` to set the SSID.
- Use `WiFi Password` to set the password.

```bash
idf.py build
idf.py -p /dev/cu.usbmodem21201 flash monitor
```

All the examples seem to work. The code does not however have an example of a GET and POST request as far as I can see. The esp_http_client by looking at the code does have these examples.

```bash
cd ..
cp -r $IDF_PATH/examples/protocols/esp_http_client .
cd esp_http_client/ 
idf.py set-target esp32c6
```

Add your WiFi credentials. Build and flash. Except for a minor error with an wrong url all tests run. The GET request has the following response:

```
I (6838) HTTP_CLIENT: HTTP GET Status = 200, content_length = 262
I (6838) HTTP_CLIENT: 7b 0a 20 20 22 61 72 67 73 22 3a 20 7b 0a 20 20
I (6838) HTTP_CLIENT: 20 20 22 65 73 70 22 3a 20 22 22 0a 20 20 7d 2c
I (6848) HTTP_CLIENT: 20 0a 20 20 22 68 65 61 64 65 72 73 22 3a 20 7b
I (6848) HTTP_CLIENT: 0a 20 20 20 20 22 48 6f 73 74 22 3a 20 22 68 74
I (6858) HTTP_CLIENT: 74 70 62 69 6e 2e 6f 72 67 22 2c 20 0a 20 20 20
I (6868) HTTP_CLIENT: 20 22 55 73 65 72 2d 41 67 65 6e 74 22 3a 20 22
I (6868) HTTP_CLIENT: 45 53 50 33 32 20 48 54 54 50 20 43 6c 69 65 6e
I (6878) HTTP_CLIENT: 74 2f 31 2e 30 22 2c 20 0a 20 20 20 20 22 58 2d
I (6888) HTTP_CLIENT: 41 6d 7a 6e 2d 54 72 61 63 65 2d 49 64 22 3a 20
I (6888) HTTP_CLIENT: 22 52 6f 6f 74 3d 31 2d 36 37 39 62 65 32 32 35
I (6898) HTTP_CLIENT: 2d 30 66 33 38 35 62 32 34 37 37 63 63 36 63 39
I (6898) HTTP_CLIENT: 35 31 31 31 37 66 36 64 32 22 0a 20 20 7d 2c 20
I (6908) HTTP_CLIENT: 0a 20 20 22 6f 72 69 67 69 6e 22 3a 20 22 39 32
I (6918) HTTP_CLIENT: 2e 32 35 34 2e 34 31 2e 31 37 22 2c 20 0a 20 20
I (6918) HTTP_CLIENT: 22 75 72 6c 22 3a 20 22 68 74 74 70 3a 2f 2f 68
I (6928) HTTP_CLIENT: 74 74 70 62 69 6e 2e 6f 72 67 2f 67 65 74 3f 65
I (6928) HTTP_CLIENT: 73 70 22 0a 7d 0a
```

The HEX corresponds to a JSON object. Use an online converter or ask ChatGPT. The data is a json object.

```json
{
  "args": {
    "esp": ""
  },
  "headers": {
    "Host": "httpbin.org",
    "User-Agent": "ESP32 HTTP Client/1.0",
    "X-Amzn-Trace-Id": "Root=1-679be225-0f385b2477cc6c951117f6d2"
  },
  "origin": "92.254.41.17",
  "url": "http://httpbin.org/get?esp"
}
```

## Include this example code as lib in the template

You can include the C ESP-IDF example files as library in the lasergame C++ template. There are quite some steps involved to accomplish this. There is a [video that explains most of the steps](https://www.youtube.com/watch?v=paXRrsztJp0) to [include this code as a library in the lasergame_template_2](./ESP-IDF_include_example_as_library.md)

