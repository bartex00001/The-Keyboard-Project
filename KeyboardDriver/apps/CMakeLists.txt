# Add executable
add_executable(KeyboardDriver main.cpp)

pico_set_program_name(KeyboardDriver "KeyboardDriver")
pico_set_program_version(KeyboardDriver "0.1")

pico_enable_stdio_usb(KeyboardDriver 1)
pico_enable_stdio_uart(KeyboardDriver 0)

# Add the standard library to the build
target_link_libraries(KeyboardDriver
        pico_stdlib
        KeyboardUtlis)

# Add the standard include files to the build
target_include_directories(KeyboardDriver PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/..
)

pico_add_extra_outputs(KeyboardDriver)
