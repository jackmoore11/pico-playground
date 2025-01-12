if (TARGET tinyusb_device)
    add_executable(bno055_temperature_read
    bno055_temperature_read.cpp
        )

    # pull in common dependencies and additional uart hardware support
    target_link_libraries(bno055_temperature_read pico_stdlib hardware_uart)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(bno055_temperature_read 1)
    pico_enable_stdio_uart(bno055_temperature_read 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(bno055_temperature_read)
elseif(PICO_ON_DEVICE)
    message("Skipping bno055_temperature_read because TinyUSB submodule is not initialized in the SDK")
endif()
