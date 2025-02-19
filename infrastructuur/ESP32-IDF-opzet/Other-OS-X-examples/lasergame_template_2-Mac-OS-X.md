### Using the lasergame template project on Mac OS X

We have successfully installed the ESP-IDF. Now we are ready to try compiling the lasergame template with CleanRTOS. I navigate to my esp folder.

Do not forget to run get_idf in a new console. We are then ready to compile ESP projects.

```bash
get_idf
```

Clone the test_lasergame_2 repository.

```bash
git clone https://github.com/HU-TI-DEV/test_lasergame_2.git
```

We need to change into this directory. I use a ESP32 C6.

```bash
cd test_lasergame_2
idf.py set-target esp32c6
```

This results in an error because we do not have the Arduino components installed. I am running at ESP-IDF 5.4.

```bash
cd components
git clone -b idf-release/v5.4 https://github.com/hu-ti-dev/arduino-esp32.git
cd ..
```

We now have a hell of a lot of components. See if we run into other errors. I first delete my build directory. Then set the target again.

```bash
idf.py set-target esp32c6
```

I still have some errors:
	
	esp32-arduino requires CONFIG_FREERTOS_HZ=1000 (currently 100)

For compatibility with Arduino IDE components FreeRTOS periodic timer needs to be set at 1000Hz. VTaskDelay(1) will take 1 ms instead of 10ms.

Edit sdkconfig and change CONFIG_FREERTOS_HZ=100 to CONFIG_FREERTOS_HZ=1000

Now you cannot set the target again because then sdkconfig will be replaced. (Note what would be a clean solution to this?)

## Test a code example

I backup my main.cpp and use the main_for_wifi_scan_ard_ide_with_nvs.cpp as a source for my new main.cpp. In my main.cpp the following lines are uncommented:

```c++
// **** Arduino IDE Examples ****
#include <WifiScan.ino>
```

Find the serial port with:

```bash
ls /dev/cu.*
```

Let’s build and open a monitor:

```bash
idf.py -p /dev/cu.usbmodem21201 flash monitor
```

The device does not seem to finish the boot sequence.  
Use Ctrl-] to quit the monitor.  
The following solution does not help in my case:

```bash
idf.py menuconfig
```

Unselect Wifi NVS Flash in component config -> Wifi. This did not help.

I will first try another device. The board I select is ESP 32s.

```bash
idf.py --list-targets
idf.py set-target esp32
```

Edit sdkconfig and change CONFIG_FREERTOS_HZ=100 to CONFIG_FREERTOS_HZ=1000

Build again, note the change in USB device:

```bash
idf.py -p /dev/cu.usbserial-2120 flash monitor
```

Yes. Now we have more success. The network scan shows me a number of APs.  
With the [ESP32 C6 I compiled some ESP-IDF examples](./ESP32-C6-wifi-scan.md).

# Troubleshooting

## CONFIG_FREERTOS_HZ=100 -- how can I change this default?

Check the file 'test_lasergame_2/build/config/Kconfig.in'.

This should contain a line to import the FreeRTOS configuration:

    source "/Users/user_name/esp32/esp-idf/components/freertos/Kconfig"

If you look into the named file `esp-idf/components/freertos/Kconfig`
(this is where you installed the esp-idf), you should find a section

```text
        config FREERTOS_HZ
            # Todo: Rename to CONFIG_FREERTOS_TICK_RATE_HZ (IDF-4986)
            int "configTICK_RATE_HZ"
            range 1 1000
            default 100
            help
                Sets the FreeRTOS tick interrupt frequency in Hz (see configTICK_RATE_HZ documentation for more
                details).
```

Change the `default` from `100` to `1000`. Then `idf.py set-target esp32` again.
