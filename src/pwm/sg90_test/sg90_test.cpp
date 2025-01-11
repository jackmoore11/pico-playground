// Drive a SG90 servo through its range of angles
// 50 Hz PWM frequency
// 1 ms pulse width: 0 degrees, 2 ms pulse width: 180 degrees

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const unsigned int OUTPUT_PIN = 0;
const float CLOCK_RATE = 1.25e8f;
const float CLOCK_DIV = 125.0f;
const unsigned int TOP_COUNT = 20000;
const float MIN_ANGLE = 0.0f;
const float MAX_ANGLE = 180.0f;
const float MIN_PULSE_WIDTH = 0.0005f;
const float MAX_PULSE_WIDTH = 0.0025f;
const float PERIOD = CLOCK_DIV * TOP_COUNT / CLOCK_RATE;

void position_servo(float angle)
{
    if (angle < MIN_ANGLE)
    {
        angle = MIN_ANGLE;
    }
    else if (angle > MAX_ANGLE)
    {
        angle = MAX_ANGLE;
    }

    float pulse_width = MIN_PULSE_WIDTH + angle / MAX_ANGLE * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
    printf("[%f %f %f]\n", angle, pulse_width, pulse_width / PERIOD);
    pwm_set_gpio_level(OUTPUT_PIN, (uint16_t)(pulse_width / PERIOD * (TOP_COUNT + 1)));
    sleep_ms(10);
}

int main()
{
    stdio_init_all();
    gpio_set_function(OUTPUT_PIN, GPIO_FUNC_PWM);
    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, CLOCK_DIV);
    pwm_config_set_wrap(&config, TOP_COUNT);
    pwm_init(pwm_gpio_to_slice_num(OUTPUT_PIN), &config, true);

    while (true)
    {
        for (int angle = 0; angle <= 180; ++angle)
        {
            position_servo((float)(angle));
        }

        for (int angle = 180; angle >= 0; --angle)
        {
            position_servo((float)(angle));
        }
    }
}