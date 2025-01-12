// Read the temperature register on the BNO055 IMU

#include <stdio.h>
#include <assert.h>
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
const uint8_t WRITE_CMD = 0x00;
const uint8_t READ_CMD = 0x01;
const unsigned int WRITE_CMD_SIZE = 5;
const unsigned int WRITE_RSP_SIZE = 2;
const unsigned int READ_CMD_SIZE = 4;
const unsigned int READ_RSP_SIZE = 3;

void check_errors();
bool write8(uint8_t register_address, uint8_t data, bool debug = false);
uint8_t read8(uint8_t register_address, bool debug = false);

int main()
{
    stdio_init_all();
    sleep_ms(10000);
    printf("BNO055 temperature read\n");

    gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
    gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));

    uart_init(UART_ID, BAUD_RATE);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    sleep_ms(1000);

    // Sanity check
    if (0xA0 != read8(0x00))
    {
        printf("Invalid chip ID!\n");
        return -1;
    }

    // Configure BNO055
    write8(0x3D, 0x00, true);
    sleep_ms(20);

    //write8(0x3F, 0x20, true);
    //sleep_ms(100);

    write8(0x3E, 0x00, true);
    sleep_ms(10);

    //write8(0x07, 0x00, true);
    //write8(0x3F, 0x00, true);
    //sleep_ms(10);

    write8(0x3D, 0x07, true);
    sleep_ms(1000);

    while (true)
    {
        read8(0x34, true);
        sleep_ms(100);
    }
}

void check_errors()
{
    uint32_t status = uart_get_hw(UART_ID)->rsr;
    if (status & UART_UARTRSR_OE_BITS) { printf("Overrun error! "); }
    if (status & UART_UARTRSR_BE_BITS) { printf("Break error! "); }
    if (status & UART_UARTRSR_PE_BITS) { printf("Parity error! "); }
    if (status & UART_UARTRSR_FE_BITS) { printf("Framing error! "); }
}

bool write8(uint8_t register_address, uint8_t data, bool debug)
{
    uint8_t tx_buf[WRITE_CMD_SIZE] = {START_BYTE, WRITE_CMD, register_address, 1, data};
    uint8_t rx_buf[WRITE_RSP_SIZE] = {};

    // Issue write command
    if (debug)
    {
        printf("Command:  [ ");
        for (unsigned int i = 0; i < WRITE_CMD_SIZE; ++i)
        {
            printf("0x%02X ", tx_buf[i]);
        }
        printf("]\n");
    }
    uart_write_blocking(UART_ID, tx_buf, WRITE_CMD_SIZE);

    if (debug) { printf("Recieved: "); }
    if (uart_is_readable_within_us(UART_ID, 10000))
    {
        check_errors();

        // Read register data
        uart_read_blocking(UART_ID, rx_buf, WRITE_RSP_SIZE);

        if (debug)
        {
            printf("[ ");
            for (unsigned int i = 0; i < WRITE_RSP_SIZE; ++i)
            {
                printf("0x%02X ", rx_buf[i]);
            }
            printf("]\n");
        }

        if (0x01 == rx_buf[WRITE_RSP_SIZE - 1])
        {
            return true;
        }
        else if (debug)
        {
            printf("bad response code (0x%02X)\n", rx_buf[WRITE_RSP_SIZE - 1]);
        }

        return false;
    }
    else if (debug)
    {
        printf("timeout (10 ms)\n");
    }

    return false;
}

uint8_t read8(uint8_t register_address, bool debug)
{
    uint8_t tx_buf[READ_CMD_SIZE] = {START_BYTE, READ_CMD, register_address, 1};
    uint8_t rx_buf[READ_RSP_SIZE] = {};

    // Issue read command
    if (debug)
    {
        printf("Command:  [ ");
        for (unsigned int i = 0; i < READ_CMD_SIZE; ++i)
        {
            printf("0x%02X ", tx_buf[i]);
        }
        printf("]\n");
    }
    uart_write_blocking(UART_ID, tx_buf, READ_CMD_SIZE);

    if (debug) { printf("Recieved: "); }
    if (uart_is_readable_within_us(UART_ID, 10000))
    {
        check_errors();

        // Read register data
        uart_read_blocking(UART_ID, rx_buf, READ_RSP_SIZE);

        if (debug)
        {
            printf("[ ");
            for (unsigned int i = 0; i < READ_RSP_SIZE; ++i)
            {
                printf("0x%02X ", rx_buf[i]);
            }
            printf("]\n");
        }

        return rx_buf[READ_RSP_SIZE - 1];
    }
    else if (debug)
    {
        printf("timeout (10 ms)\n");
    }

    return 0;
}