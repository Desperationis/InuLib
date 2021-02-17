import requests
import pygame
import time
from math import floor

"""
    Sends http packets to serialWebserver.py about controller input.
"""


pygame.init() # Init controller library

joystick_count = pygame.joystick.get_count()
joystick = None
if joystick_count == 0:
    print("Error, I didn't find any joysticks.")
else:
    joystick = pygame.joystick.Joystick(0)
    joystick.init() # We don't need this reference later



while(True):
    pygame.event.get()

    if joystick_count != 0:
        r = requests.post("http://192.168.43.242:8008/", None, json =  {
            "X": floor(joystick.get_axis(0) * 126.0) + 126,
            "Y": floor(joystick.get_axis(1) * 126) + 126,
            "BTN1": 0,
            "BTN2": 0
        })


    time.sleep(0.016) # Send packets 60 times a second
