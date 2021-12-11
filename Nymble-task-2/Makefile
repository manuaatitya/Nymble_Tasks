MCU    = atmega328p
F_CPU  = 16000000
TARGET = i2c_adc_reader
PROGRAMMER = arduino
PORT = /dev/ttyUSB0

BAUD_RATE = 115200

CC      = avr-gcc 
OBJCOPY = avr-objcopy 

INCLUDES = -I./ -I/usr/lib/avr/include
CFLAGS   = -std=c99 -g -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(INCLUDES) -Os 
LDFLAGS  = -Wl,-gc-sections -Wl,-relax 

OBJECT_FILES = main.o uart.o i2c.o   # Object files part of the final program

all: $(TARGET).hex size

size:
	@if [ -f $(TARGET).obj ]; then avr-size -C --mcu=$(MCU) $(TARGET).obj; fi

clean: 
	rm -rf *.o *.hex *.obj

%.hex: %.obj 
	$(OBJCOPY) -R .eeprom -O ihex $< $@ 

%.obj: $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJECT_FILES) $(LDFLAGS) 

upload:
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD_RATE) -U flash:w$(TARGET).hex:i
