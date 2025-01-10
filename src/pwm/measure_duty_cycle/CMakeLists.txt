if (TARGET tinyusb_device)

    add_executable(pwm_measure_duty_cycle
        measure_duty_cycle.cpp
        )
    
    # pull in common dependencies and additional pwm hardware support
    target_link_libraries(pwm_measure_duty_cycle pico_stdlib hardware_pwm)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(pwm_measure_duty_cycle 1)
    pico_enable_stdio_uart(pwm_measure_duty_cycle 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(pwm_measure_duty_cycle)
elseif(PICO_ON_DEVICE)
    message("Skipping pwm_measure_duty_cycle because TinyUSB submodule is not initialized in the SDK")
endif()