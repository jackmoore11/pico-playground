add_executable(hello_pwm
    hello_pwm.cpp
    )

# pull in common dependencies and additional pwm hardware support
target_link_libraries(hello_pwm pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(hello_pwm)
