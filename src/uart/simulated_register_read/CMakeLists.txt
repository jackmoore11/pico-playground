if (TARGET tinyusb_device)
    add_executable(simulated_register_read
    simulated_register_read.cpp
        )

    # pull in common dependencies and additional uart hardware support
    target_link_libraries(simulated_register_read pico_stdlib hardware_uart)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(simulated_register_read 1)
    pico_enable_stdio_uart(simulated_register_read 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(simulated_register_read)
elseif(PICO_ON_DEVICE)
    message("Skipping simulated_register_read because TinyUSB submodule is not initialized in the SDK")
endif()
