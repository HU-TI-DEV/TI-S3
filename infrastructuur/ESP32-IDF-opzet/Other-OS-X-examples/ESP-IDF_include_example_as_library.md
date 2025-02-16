## Include ESP-IDF example code as library

We will now try to use the tested Get and Post functions to be included in our lasergame template. For video instructions [see this walk-through](https://www.youtube.com/watch?v=paXRrsztJp0).  I have opened a new terminal and will navigate to:

```bash
cd /esp/test_lasergame_2
get_idf
idf.py set-target esp32c6
```

I have to (re)edit sdkconfig and change CONFIG_FREERTOS_HZ=100 to CONFIG_FREERTOS_HZ=1000

Now we will remove dependencies.lock and the build folder from the esp_http_client folder. Then I copy this folder in the libs directory from the lasergame template.

Check if this project builds in this new location. Navigate to the folder and build.

```bash
cd /libs/esp_http_client
idf.py build
```

Yes. Still going strong. Maybe flash it?

```bash
idf.py -p <your serial port> flash
```

For me `idf.py -p /dev/cu.usbmodem21201 flash monitor`

Now we are ready to make modifications to build everything from the main folder.

Add a header file to your main:

```C++
#include <esp_http_client_example.h>
```

In the `esp_http_client_example.c` file we should rename the function `app_main` because we already have this function name in our lasergame template.

I rename `app_main` in `setup` and add a void function that does nothing else but sleep.

```C++
void loop(void){
    vTaskDelay(1000);
}
```

These functions we want to call from our own task main. The declarations of these functions need to be added to the header file. Now create the header file `esp_http_client_example.h`. To use these C functions from our C++ code we need to add `extern "C"`. This is our header file.

```C++
#pragma once


#ifdef __cplusplus
extern "C" {
#endif

//C routines   
void setup(void);
void loop(void);

#ifdef __cplusplus
}
#endif
```

Also include this header file in the corresponding C code. Then add the lib folder and .c file to the makelist (`CMakeLists.txt`). 

In the includes section add:

```C++
"../libs/esp_http_client/main"
```

Under component sources add:

```C++
"../libs/esp_http_client/main/esp_http_client_example.c"
```

From the example take the wifi configuration from the sdkconfig and add it to the sdkconfig from the lasergame template.

```C++
#
# Example Connection Configuration
#
CONFIG_ENV_GPIO_RANGE_MIN=0
CONFIG_ENV_GPIO_RANGE_MAX=30
CONFIG_ENV_GPIO_IN_RANGE_MAX=30
CONFIG_ENV_GPIO_OUT_RANGE_MAX=30
CONFIG_EXAMPLE_CONNECT_WIFI=y
# CONFIG_EXAMPLE_WIFI_SSID_PWD_FROM_STDIN is not set
CONFIG_EXAMPLE_PROVIDE_WIFI_CONSOLE_CMD=y
CONFIG_EXAMPLE_WIFI_SSID="<replace with your SSID>">
CONFIG_EXAMPLE_WIFI_PASSWORD="<replace with your password>"
CONFIG_EXAMPLE_WIFI_CONN_MAX_RETRY=6
# CONFIG_EXAMPLE_WIFI_SCAN_METHOD_FAST is not set
CONFIG_EXAMPLE_WIFI_SCAN_METHOD_ALL_CHANNEL=y
```

In the `esp_http_client_example.c` I have removed all functions with https for not adding more complexity.

Include the content from the `idf_component.yaml' into the yml file of the lasergame template. Addt this under dependencies:

```C++
  protocol_examples_common:
    path: ${IDF_PATH}/examples/common_components/protocol_examples_common
  esp_stubs:
    path: ${IDF_PATH}/examples/protocols/linux_stubs/esp_stubs
    rules:
    - if: "target in [linux]"
```

Lets build
```bash
idf.py build
```

I receive the following error `error: conflicting declaration of 'void setup()' with 'C' linkage`

The loop and setup functions conflict with the Arduino standard functions so we should rename them.

```C++
void http_client_setup(void);
void http_client_loop(void);
```

We build again and note that the `CONFIG_EXAMPLE_HTTP_ENDPOINT` is not defined. I will also define this global variable in the header file.

```C++
#define CONFIG_EXAMPLE_HTTP_ENDPOINT "httpbin.org"
```

I now receive the following error `Error: app partition is too small for binary app-template.bin`

I first try:

```bash
idf.py fullclean
idf.py build
```

That did not help. I will try to allocate more space for the application in `partitions.csv`. The content is now:

```csv
nvs,      data, nvs,     0x9000,  0x5000,
otadata,  data, ota,     0xe000,  0x2000,
app0,     app,  ota_0,   0x10000, 0x770000,  # 7.5 MB for app0
spiffs,   data, spiffs,  0x780000,0x80000,   # 512 KB for SPIFFS
```