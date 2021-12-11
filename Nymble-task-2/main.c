# include <stdio.h>

# include "uart.h"   // Custom library for UART Transmission
# include "i2c.h"   // Custom Library for I2C Communication

// Get Slave Address from Data Sheet
# define MAX11607_I2C_SLAVE_ADDRESS 0x34

// To store the data from MAX11607
uint8_t data[8];

// To store the ADC Value
uint16_t ADC_value[4];

void convert_data_to_ADC_values()
{
    for(int i = 0; i < 4; i++)
    {
        ADC_value[i] = (uint16_t) (data[2 * i + 1] << 8 | data[2 * i]);
    }
}

void send_10_bit_ADC_to_UART(uint16_t ADC_value)
{
    uint8_t ones_position = ADC_value % 10;
    ADC_value = ADC_value / 10;

    uint8_t tens_position = ADC_value % 10;
    ADC_value = ADC_value / 10;

    uint8_t hundreds_position = ADC_value % 10;
    ADC_value = ADC_value / 10;

    uint8_t thousands_position = ADC_value;

    UART_Transmit(thousands_position);
    UART_Transmit(hundreds_position);
    UART_Transmit(tens_position);
    UART_Transmit(ones_position);
}


int main()
{
    // Initialise UART Communication
    UART_Init();

    // Initialise I2C Communication
    I2C_init();

    // Start I2C Communication
    I2C_start();

    // Write Slave Address to begin communication

    // Configure the MAX11607 for single-ended mode, use VDD for reference
    I2C_write(MAX11607_I2C_SLAVE_ADDRESS);   // set up  (bit 7 = 1), use VDD as reference, internal clock, unipolar
    I2C_write(0x80 | 0x02);

    I2C_write(MAX11607_I2C_SLAVE_ADDRESS);   // configure (bit 7 = 0), all channels, single ended (bit 0 = 1)
    I2C_write(0x06 | 0x01);

    I2C_stop();   // Stop the I2C Communication

    while (1)
    {
        // Start the I2C Communication
        I2C_start();
        
        // Get 8 bytes of data from the ADC board
        for(int i = 0; i < 8; i++)
        {
            data[i] = (int)I2C_read();
        }

        convert_data_to_ADC_values();

        // Stop the I2C Communication
        I2C_stop();

        UART_Transmit_CH_1();
        send_10_bit_ADC_to_UART(ADC_value[0]);
        UART_Transmit_padding();


        UART_Transmit_CH_2();
        send_10_bit_ADC_to_UART(ADC_value[1]);
        UART_Transmit_padding();


        UART_Transmit_CH_3();
        send_10_bit_ADC_to_UART(ADC_value[2]);
        UART_Transmit_padding();


        UART_Transmit_CH_4();
        send_10_bit_ADC_to_UART(ADC_value[3]);
        UART_Transmit('\n');

        // Introduce slight delay
        _delay_ms(500);
    }
    
    return 0;
}