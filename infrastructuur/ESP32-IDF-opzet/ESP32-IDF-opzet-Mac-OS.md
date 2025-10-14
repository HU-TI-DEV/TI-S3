# ESP32-project opzet, ESP32-IDF installatie

 Installing ESP-IDF on Mac OS. Tested on Mac M4 with Sequoia 15.1.1. Date: 24-01-2025

Source: [https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html)

Make a workspace:

```bash
mkdir -p ~/esp
cd ~/esp
```

I have Homebrew installed therefore I can use

```bash
brew install cmake ninja dfu-util
```

To install Ninja and CMake. As recommended I will try to install coach for faster builds.

```bash
brew install ccache
```

It tells me:
> To install symlinks for compilers that will automatically use
> ccache, prepend this directory to your PATH:
> `/opt/homebrew/opt/ccache/libexec`

```bash
sudo nano /etc/paths
```

Add /opt/homebrew/opt/ccache/libexec
Save and quit. Restart your terminal and navigate to your workspace folder. Check your settings using echo $PATH.

No errors related to the M4 processor. And Python version 3 is already installed on my system (version 3.13.1).

Now I will get the esp source files to buil the ESP-IDF.
Navigate to you workspace and clone the repository.

```bash
git clone -b v5.4 --recursive https://github.com/espressif/esp-idf.git
```

Version is the current stable version at this date: 24-01-2025.
Now we need to install tools, debugger, compiler used by the EDP-IDF. I choose to install tools for all supported targets.

```bash
cd ~/esp/esp-idf
./install.sh all
```

To make the compilation tools available in the $HOME directory run:

```bash
. ./export.sh
```

Now you are ready to build ESP-IDF projects!

But we first add the tools to our PATH environment so they are available from the command line. Navigate to your workspace folder and run:

```bash
. $HOME/esp/esp-idf/export.sh
```

Add export.sh to you bash profile:

```bash
nano ~/.zprofile
```

Add the following line:

alias get_idf='. $HOME/esp/esp-idf/export.sh’. Save and close, restart your terminal session.

```bash
get_idf 
```

This wil setup your ESP-IDF environment in any terminal session.

Now build our first hello world project from the examples given.

```bash
cp -r $IDF_PATH/examples/get-started/hello_world .
```

Connect your ESP32 board and find the serial port it is connected to. To show all your USB devices that are connected:

```bash
system_profiler SPUSBDataType
```

Find the serial port with:

```bash
ls /dev/cu.*
```

In my case it is named /dev/cu.usbmodem21201

We will navigate to the hello world project and configure it. Note that I use a ESP32 C6 development board.

```bash
cd hello_world
idf.py set-target esp32c6
idf.py menuconfig
```

You can use the menuconfig to setup things like WiFi. For now we exit and quit.

Build your project using:

```bash
idf.py build
```

Now you have a hello_world.bin firmware binary in your build folder. Let us flash it to the device:

```bash
idf.py -p <your serial port> flash
```

In my case `idf.py -p /dev/cu.usbmodem21201 flash monitor`

Note that flashing CH343 interface did not work for me.
I have to use the other USB-C connector on my ESP device.

You have your first Hello World program built and flashed to your device!

When you restart the terminal do not forget to run:

```bash
get_idf
```

We can now check if our program actually works:

```bash
idf.py monitor
```

It will show you the serial output from your ESP device.
