# ifndef I2C_H   // Start defintion for I2C Library
#  define I2C_H

# include <avr/io.h>
# include <util/delay.h>

// ATMEGA uses TWI (Two Wire Interface) Registers for I2C Communication

// Using 100 KHz as speed for the I2C 
# define SCL_FREQUENCY 100000UL   

// I2C Initialization function
void I2C_init();

// I2C Start function
void I2C_start();

// I2C Stop function
void I2C_stop();

// I2C Read function
char I2C_read();

// I2C Write function
void I2C_write(char data);

# endif   // End definition for I2C Library