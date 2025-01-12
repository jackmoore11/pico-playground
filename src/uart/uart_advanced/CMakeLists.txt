if (TARGET tinyusb_device)
    add_executable(uart_advanced
        uart_advanced.cpp
        )

    # pull in common dependencies and additional uart hardware support
    target_link_libraries(uart_advanced pico_stdlib hardware_uart)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(uart_advanced 1)
    pico_enable_stdio_uart(uart_advanced 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(uart_advanced)
elseif(PICO_ON_DEVICE)
    message("Skipping uart_advanced because TinyUSB submodule is not initialized in the SDK")
endif()
