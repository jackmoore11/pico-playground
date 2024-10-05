cmake_minimum_required(VERSION 3.13...3.27)

# Initialize pico-sdk from submodule
# Note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(playground)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# The project
add_executable(hello_world
    hello_world.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hello_world pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hello_world)