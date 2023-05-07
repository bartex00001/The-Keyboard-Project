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
wget https://github.com/Kitware/CMake/releases/download/v3.19.4/cmake-3.25.1.tar.gz
tar -zxvf cmake-3.25.1.tar.gz
cd cmake-3.25.1/
./bootstrap
make
sudo make install
```

## Build and flash

### VS code

The easiest way to build and flash the project is to use VScode.  
With _KeyboardDriver_ foler open in VSC, firstly run `CMake: Configure` and then `CMake: Build` in the command palette.  
This sholuld create a _build_ folder in the project root and a `*.uf2` file inside.  

Using the file explorer, navigate to the _build_ folder and copy the `KeyboardDriver.uf2` file to the Pico drive.  
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
cp KeyboardDriver.uf2 /media/your_username/PICO/
```
> Kepp in mind that the path to pico drive will be different on your computer.
