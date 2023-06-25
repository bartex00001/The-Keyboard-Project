cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
set(PICO_SDK_PATH "~/Documents/personal/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(KeyboardDriver C CXX ASM)
add_compile_definitions(CFG_TUSB_CONFIG_FILE="KeyboardDriver/tusb_config.h")

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(apps)

add_subdirectory(src)
