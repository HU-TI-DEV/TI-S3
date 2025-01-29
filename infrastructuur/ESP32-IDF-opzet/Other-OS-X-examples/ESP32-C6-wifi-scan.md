### Building ESP-IDF example files

I had some issues with using Arduino libraries on the ESP32 C6. The problem has not yet been identified. As a test I will now try to compile and flash the ESP-IDF wifi network scan.

Open a terminal and navigate to the esp directory. Setup your ESP-IDF environment.

```bash
get_idf 
```

I think the following example can show me if wifi is working on this device (at least perform an AP scan).

```bash
cp -r $IDF_PATH/examples/wifi/fast_scan .
```

Connect your ESP32 board and find the serial port it is connected to. 

```bash
ls /dev/cu.*
```

In my case it is still named /dev/cu.usbmodem21201

We will navigate to the wifi scan project and configure it. Set the target for ESP32 C6 development board.

```bash
cd fast_scan
idf.py set-target esp32c6
```

Now add our wifi credentials.

```bash
idf.py menuconfig
```

In the Example Configuration menu:

- Use `WiFi SSID` to set the SSID.
- Use `WiFi Password` to set the password.

Save and quit. These changes are now set in our sdkconfig

Build your project using:

```bash
idf.py build
```

Now flash and I also open a monitor

```bash
idf.py -p /dev/cu.usbmodem21201 flash monitor
```

The device finds a matching AP and connects to it. In the serial output it show me the ip it has received. 