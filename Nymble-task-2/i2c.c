# include "i2c.h"

// ---------------------------------- I2C initalisation function -------------------------------
void I2C_init()
{
    // Baud Rate value set
    // TWBR -> Two Wire Baud Rate 
    TWBR = 0x09;

    // TWEN -> Two Wire Enable Bit
    // TWCR -> Two Wire Control Register
    TWCR = (1 << TWEN);   // Enable I2C Communication

    // Set Prescaler value
    // TWSR -> Two Wire Status Register
    TWSR = (1 << TWPS1) | (0 << TWPS0);   // Assumed value of 16 for Prescaler
}
// ---------------------------------- I2C initalisation function -------------------------------


// ------------------ I2C Start ------------------------ 
void I2C_start()
{
    // Start the I2C Communication
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);

    // Check if I2C has started
    while(!(TWCR & (1 << TWINT))) ;

}
// ----------------------------------------------------- 

// ----------------------- I2C Stop Function --------------------------
void I2C_stop()
{
    // Stop the transmission and free the Data line
    TWCR = (1<<TWINT) | (1 << TWEN)|(1 << TWSTO); 
}
// --------------------------------------------------------------------

// --------------------------- I2C Read Function -------------------------------
char I2C_read()
{
    TWCR = (1 << TWINT) | (1 << TWEN);   // Enable I2C and clear the Interrupt
    while(!(TWCR & (1 << TWINT)));   // Read complete with data stored in TWDR

    // Read data received from TWDR register
    // TWDR -> Two Wire Data Register
    return TWDR;
}
// -----------------------------------------------------------------------------

// --------------------------- I2C Write Function -------------------------------
void I2C_write(char x)
{
    // Write value to the register
    // TWDR -> Two Wire Data Register
    TWDR = x;

    TWCR = (1 << TWINT) | (1 << TWEN);   // Enable I2C and clear the Interrupt

    while(!(TWCR & (1 << TWINT)));
}
// ------------------------------------------------------------------------------
