if (TARGET tinyusb_device)
    add_executable(sg90_test
        sg90_test.cpp
        )

    # pull in common dependencies and additional pwm hardware support
    target_link_libraries(sg90_test pico_stdlib hardware_pwm)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(sg90_test 1)
    pico_enable_stdio_uart(sg90_test 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(sg90_test)
elseif(PICO_ON_DEVICE)
    message("Skipping sg90_test because TinyUSB submodule is not initialized in the SDK")
endif()