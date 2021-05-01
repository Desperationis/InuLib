import pygame
import serial
import sys

# Start main loop to send serial data to the Cortex
serialInterface = serial.Serial('/dev/ttyS0',9600,timeout = 0,stopbits=1,bytesize=8)

pygame.init()

clock = pygame.time.Clock()
while True:
    if serialInterface.isOpen:
        #serialInterface.write([254]) # Header Byte
        #serialInterface.write([69])
        print(serialInterface.read(int(sys.argv[1])).decode('ascii'))
    else:
        print("Error: UART Serial interface is not open.")

    clock.tick(50)

