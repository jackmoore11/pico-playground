// Do a simulated register read

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1

const uint8_t START_BYTE = 0xAA;
const uint8_t READ_CMD = 0x01;
const uint8_t REGISTER = 0xFF;
const uint8_t DATA_LENGTH = 8;

int main()
{
    stdio_init_all();
    sleep_ms(10000);
    std::cout << "Simulated register read" << std::endl;

    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));

    uart_init(UART_ID, BAUD_RATE);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    uint8_t tx_buf[4] = {START_BYTE, READ_CMD, REGISTER, DATA_LENGTH};
    uint8_t rx_buf[4] = {};
    unsigned int iteration = 0;

    while (true)
    {
        // Write to TX
        uart_write_blocking(UART_ID, tx_buf, 4);
        sleep_ms(1);

        // Read from RX
        uart_read_blocking(UART_ID, rx_buf, 4);

        std::cout << "Iteration " << iteration << ":";
        for (unsigned int i = 0; i < 4; ++i)
        {
            if (rx_buf[i] == tx_buf[i])
            {
                std::cout << " Byte " << i << " match :)";
            }
            else
            {
                std::cout << " Byte " << i << " mismatch :(";
            }
        }
        std::cout << std::endl;

        ++iteration;
        sleep_ms(1000);
    }
}