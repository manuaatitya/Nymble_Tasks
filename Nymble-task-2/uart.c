# include "uart.h"

void UART_Init()
{
    // Set the prescaler value for the baud rate
    // Actually a 10 bit register so it's split up and set like this

    UBRR0H = (UART_BAUD_RATE_PRESCALAR >> 8);

    UBRR0L = (UART_BAUD_RATE_PRESCALAR);

    // Enable Receiver and Transmitter 
    // RXEN -> Reception Enable Register
    // TXEN -> Transmission Enable Register
    // UCSR -> UART Control Status Register
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set the data format
    UCSR0C = ASYNCHRONOUS_MODE | PARITY_MODE | STOP_BIT_SIZE | DATA_FRAME;
}

void UART_Transmit(unsigned char data)
{
    // UDRE -> UART Data register empty bit ? (True if empty and false if data is present)
    while((UCSR0A & (1 << UDRE0)) == 0) {};   // Until Serial port is available

    // UDR -> UART Data Register (which contains the data received or to transmit)
    UDR0 = data;
}

void UART_Transmit_CH_1(void)
{
    UART_Transmit('c');
    UART_Transmit('h');
    UART_Transmit('1');
    UART_Transmit(':');
    UART_Transmit(' ');
}

void UART_Transmit_CH_2(void)
{
    UART_Transmit('c');
    UART_Transmit('h');
    UART_Transmit('2');
    UART_Transmit(':');
    UART_Transmit(' ');
}

void UART_Transmit_CH_3(void)
{
    UART_Transmit('c');
    UART_Transmit('h');
    UART_Transmit('3');
    UART_Transmit(':');
    UART_Transmit(' ');
}

void UART_Transmit_CH_4(void)
{
    UART_Transmit('c');
    UART_Transmit('h');
    UART_Transmit('4');
    UART_Transmit(':');
    UART_Transmit(' ');
}

void UART_Transmit_padding(void)
{
    UART_Transmit(' ');
    UART_Transmit('|');
    UART_Transmit(' ');
}