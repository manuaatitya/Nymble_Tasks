#ifndef UART_H   // Start definition for UART
# define UART_H

# include <avr/io.h>   // Include the AVR Library
# include <util/delay.h>   // Library to set the BAUD Rate

# define UART_BAUD_RATE 115200   // BAUD Rate for Serial Communication

// Select mode first - Here Asynchronous Mode is selected
// Use equation from datasheet to calculate the prescaler value
# define UART_BAUD_RATE_PRESCALAR ((F_CPU)/(UART_BAUD_RATE * 16UL) - 1)

// Select Asynchronous Mode
# define ASYNCHRONOUS_MODE (0 << UMSEL00)

//  ------------------ Set Parity Bit Modes ------------------------
// UPM -> UART Parity Mode
# define ODD_PARITY (3 << UPM00)

# define EVEN_PARITY (2 << UPM00)

# define DISABLED (0 << UPM00)

// Defined mode is Disabled Mode in Parity
# define PARITY_MODE DISABLED
//  ----------------------------------------------------------------

//  ------------------ Set Start and Stop Bit Modes ------------------------
// USBS -> USB Stop Bit 
# define ONE_BIT (0 << USBS0)
# define TWO_BIT (1 << USBS0)

# define STOP_BIT_SIZE ONE_BIT
//  -------------------------------------------------------------------------

//  ------------------ Set Data Frame Size ------------------------
# define EIGHT_BIT (3 << UCSZ00)
# define DATA_FRAME EIGHT_BIT
//  ---------------------------------------------------------------

// Initialise the UART Communication
void UART_Init();

// Initialise the UART Transmission
void UART_Transmit(unsigned char data);

// Transmit data for better readability

void UART_Transmit_CH_1(void);

void UART_Transmit_CH_2(void);

void UART_Transmit_CH_3(void);

void UART_Transmit_CH_4(void);

void UART_Transmit_padding(void);

#endif   // End defintion for UART