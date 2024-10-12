cmake_minimum_required(VERSION 3.13...3.27)

# Initialize pico-sdk from submodule
# Note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(playground)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# The project
add_subdirectory(hello_world)
add_subdirectory(blink_simple)