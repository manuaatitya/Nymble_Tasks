# Code to Read 4 channel 10 bit ADC via I2C:

| --- [**main.c**](https://github.com/manuaatitya/Nymble_Tasks/blob/master/Nymble-task-2/main.c)

       | ---- Contains the main application code
       
| ---- [**Makefile**](https://github.com/manuaatitya/Nymble_Tasks/blob/master/Nymble-task-2/Makefile)

       | ---- Contains the compile and build instructions 
       
| ---- [**uart.c**](https://github.com/manuaatitya/Nymble_Tasks/blob/master/Nymble-task-2/uart.c)

       | ---- Contains the UART related configurations for ATMega328p and the corresponding header file "uart.h" is also included
       
| ---- [**i2c.c**](https://github.com/manuaatitya/Nymble_Tasks/blob/master/Nymble-task-2/i2c.c)

       | ---- Contains the I2C related configurations to read data from ADC board and the corresponding header file "i2c.h" is also included
       
| ---- [**i2c_adc_reader.hex**](https://github.com/manuaatitya/Nymble_Tasks/blob/master/Nymble-task-2/i2c_adc_reader.hex)

       | ---- The hex file generated from the build. (i2c_adc_reader.o is the intermediate file in the build process) 
       

The compilation output is as follows:
![compile](https://user-images.githubusercontent.com/32318187/145660224-703cac0c-a2f9-4bef-b9dd-93274adb4f05.png)