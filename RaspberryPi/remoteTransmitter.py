import requests
import pygame
import time
from math import floor

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


clock = pygame.time.Clock()
while(True):
    pygame.event.get()

    if joystick_count != 0:
        r = requests.post("http://192.168.1.2:8008/", None, json =  {
            "X": floor(joystick.get_axis(2) * 126.0) + 126,
            "Y": floor(joystick.get_axis(1) * 126.0) + 126,
            "BTN1": 0,
            "BTN2": 0
        })


    clock.tick(60) # Send packets 60 times a second
