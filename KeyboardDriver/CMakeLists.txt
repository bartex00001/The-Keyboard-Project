cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
set(PICO_SDK_PATH "your path to pico_sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(KeyboardDriver C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable
add_executable(KeyboardDriver KeyboardDriver.cpp)

pico_set_program_name(KeyboardDriver "KeyboardDriver")
pico_set_program_version(KeyboardDriver "0.1")

pico_enable_stdio_usb(KeyboardDriver 1)
pico_enable_stdio_uart(KeyboardDriver 0)

# Add the standard library to the build
target_link_libraries(KeyboardDriver
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(KeyboardDriver PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..
)

pico_add_extra_outputs(KeyboardDriver)
