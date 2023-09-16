# How to build

The project is meant to be built on linux with a GCC for arm compiler.

## Dependencies

### Pico sdk

This dev-kit provided by Raspberry Pi is needed for, well... development.  
You need it somewhere on your computer so download it and update (download) its submodules.  

```bash
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```

> Remember to replace _"your path to pico_sdk"_ in CMakeLists.txt with and actual path.

### Compilers and libraries for arm

```bash
sudo apt update
sudo apt install gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

### CMake

The project is built with newish version of CMake and therefore you need build it yourself.  

```bash
## You can pick newer version if it exists
version=3.27
build=0
mkdir ~/temp
cd ~/temp
wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz
tar -xzvf cmake-$version.$build.tar.gz
cd cmake-$version.$build/
./bootstrap
make
sudo make install
```

## Build and flash

### VS code

The easiest way to build and flash the project is to use VScode.  
With _KeyboardDriver_ foler open in VSC, firstly run `CMake: Configure` and then `CMake: Build` in the command palette.  
This sholuld create a _build_ folder in the project root and a `*.uf2` file inside.  

Using the file explorer, navigate to the _build/apps_ folder and copy the `KeyboardDriver.uf2` file to the Pico drive.  
The pico will restart and run the program.

> Note that sometimes during the first build intellisense might not work.  
> To fix this, just run `CMake: Configure` again.

### Command line

If you prefer to use the command line, you can do the same thing as above with the following commands:  
(starting from the KeyboardDriver folder)

```bash
# Setup and enter build folder
mkdir build
cd build

# Configure and build
cmake ..
make

# Copy the .uf2 file to the Pico drive
cp apps/KeyboardDriver.uf2 /media/your_username/PICO/
```

> Kepp in mind that the path to pico drive will be different on your computer.

## Debugging

Pico will, by default, output debug information to the USB serial port.  
To monitor this output, you can use `minicom`:

```bash
sudo apt install minicom
minicom -b 115200 -o -D /dev/ttyACM0
```

> The path to the serial port might be different on your computer.

## Credits

- [MightyPork/usb_hid_keys.h](https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2) - list of all HID keycodes
