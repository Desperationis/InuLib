import pygame
import serial
import time
import threading
from math import *
from flask import request, Response, Flask

"""
    Sends packets to a VEX Cortex using UART. These packets contain controller data
    that is constantly received by an asynchronous web server.
"""
# Start up webserver
currentPacket = [126,126,0,0] # Asynchronous packet
webServer = Flask(__name__)
@webServer.route('/', methods=['POST', 'GET'])
def serverResponse():
    global currentPacket
    if request.method == "POST":
        currentPacket = [
            int(request.json["X"]),
            int(request.json["Y"]),
            int(request.json["BTN1"]),
            int(request.json["BTN2"])
        ]
        return "GET repos/Desperationis/2DStarve-Releases/releases"

    else:
        return Response(status=200)

def startServer():
    webServer.run(host='192.168.1.26', port=8008)

webServerThread = threading.Thread(target=startServer)
webServerThread.start()

# Start main loop to send serial data to the Cortex
serialInterface = serial.Serial('/dev/ttyS0',115200,timeout = 1)

while True:
    if serialInterface.isOpen:
        serialInterface.write([254]) # Header Byte
        serialInterface.write(currentPacket)
    else:
        print("Error: UART Serial interface is not open.")

    time.sleep(20 / 1000) # Don't send packets when the cortex is on delay() to avoid buffer overload

webServer.join()
