import pygame
import time
from math import floor
from socket import *

"""
    Sends JSON data about controller input to the Raspberry Pi
"""

pygame.init() # Init controller library

joystick_count = pygame.joystick.get_count()
joystick = None
if joystick_count == 0:
    print("Error, I didn't find any joysticks.")
else:
    joystick = pygame.joystick.Joystick(0)
    joystick.init() # We don't need this reference later

s = socket(type=SOCK_DGRAM)
clock = pygame.time.Clock()
while(True):
    pygame.event.get()

    if joystick_count != 0:
        x = [str(floor(joystick.get_axis(0) * 126.0) + 126),
                str(floor(joystick.get_axis(1) * 126.0) + 126),
                "0",
                "0"]
        s.sendto(",".join(x).encode('utf-8'), ('192.168.1.4', 5000))


    clock.tick(30) # Send packets 60 times a second
