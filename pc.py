#!/usr/bin/env python
# Set the python interpreter to the Python version in the environment variable

# ------------------------------------------
#      Nymble Embedded Software Task
# ------------------------------------------

# Submitted by Manu Aatitya R P

# Required Libraries for the app

import serial   # The serial library to access the serial data
import yaml   # To read data from the config file
import time   # To calculate time between events

# Load the System config data
with open ('pc_config.yaml', 'r') as pc_config_file:
    pc_config = yaml.load(pc_config_file, Loader=yaml.SafeLoader)

# Get the Serial port name from the Config file
serial_port_name = pc_config["pc_config"]["serial_port"]

# Get the Serial baud rate from the Config file
serial_baud_rate = pc_config["pc_config"]["serial_baud_rate"]

# Configuring the Serial port based on pc configurations yaml file
serial_port = serial.Serial(serial_port_name, serial_baud_rate, timeout=1)
serial_port.flushInput()
serial_port.flush()

# Read data from the text file to send serially
data_transmit_file = open('data_to_be_sent.txt', "r")
data = data_transmit_file.read()
# print(data)

# Create a text file to save data that is received from MCU
data_received_file = open('data_received_file.txt', "a")

# Array to store serial data receiving speeds
data_receiving_speed = []

counter = 0
data_transmission_complete = False

while True:
    try:
        # If Serial port is empty 
        receive_start_time = time.time()
        if serial_port.in_waiting > 0:
            # Read Serial Data and convert into ASCII format
            serial_data = serial_port.read().decode("utf-8").rstrip()
        
        receive_end_time = time.time()
        
        # Write the bytes received to a text file (for checking later)
        data_received_file.write(serial_data)
        
        time_elapsed = (receive_end_time - receive_start_time)

        current_receiving_speed = (len(serial_data))/ time_elapsed
        data_receiving_speed.append(current_receiving_speed)
        print("Current Data Receiving Speed is {}".format(current_receiving_speed))
    
        if counter * 20 + 20 > len(data):
            data_to_send = data[counter*20:]
        else:

            # If data transmission is complete
            if data_transmission_complete == True:

                # Don't send any data
                data_to_send = ""
            else:

                # Send the last information to send
                data_to_send = data[counter * 20: counter*20 + 20]

                # Once transmission complete set flag to True
                data_transmission_complete = True

        # Send the data serially
        serial_port.write(data_to_send)

        counter += 1

    except:
        print("Keyboard Interrupt")
        break

# Print the data received
average_data_receiving_speed = sum(data_receiving_speed)/len(data_receiving_speed)
print("The average speed of receiving data is {}".format(average_data_receiving_speed))

# Clean the workspace and data

# Closing all open files
data_transmit_file.close()
data_received_file.close()