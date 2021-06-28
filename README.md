# InuLib
A general PROS library for controlling a VEX Cortex with support with Raspberry Pi integration. "Inu" as in "Shiba Inu", which is the breed of my dog. 

# Features
This library mainly features two things: a system for controlling your robot easily with a VEX controller and packet-based serial reading and writing system.

## Controller System
Controlling a VEX robot is done through a state machine found in `Controllers.c` that takes in pointers to functions as inputs. These functions are of type `void` with no arguments and are called in an internal loop found in `Controllers.c`. Due to how it is programmed, you can really easily and quickly hot-swap between different type of controller configurations with a button without worrying about ending and starting background tasks. Built in controllers can be found in `Controllers.c` that read `enum`'s for motor ports.

The built-in controllers started with this system run in the background and are additionally slewed if the bog-standard slewing system is enabled. In addition to this, their sensitivity can be tuned with `control_set_scale()` so that a max or minimum speed can be set.

## Serial System
This library features a packet-based serial system on the UART ports of the VEX Cortex based on the defunct project [VEXSerial](https://github.com/EvolvedAwesome/VEXSerial) in `Serial.c`. Each "message" sent across the ports are of variable length and start with a header number defined to be 255, meaning only bytes with values between 0-254 can be sent at a time. 

The purpose of this system is to interface with a Raspberry Pi running a python script sending and reading serial data to the Cortex, though interfacing with any other device, like another Cortex, is very likely possible. I personally have used this system to control the Cortex with UDP sockets to send PS4 controller input from my computer, though anything is possible. Automated steering, for example, can be done if the Raspberry Pi has a camera and artifical intelligence to determine what inputs need to be sent. 

## Drawbacks
Being programmed in PROS 2.x, this library can only be run on the Cortex. This of course is pretty bad, since the newer V5 systems are much more common than the obsolote EDR system. This will most likely be fixed once I get my hands on a V5 system at my school.

Secondly, and most importantly, this library can only be run if a VEXnet controller is always connected to the Cortex. Because of this, certain configurations can't go to their full potential, such as using a very strong wifi signal to controller the Cortex anywhere in a house with a Raspberry Pi attached. It is because of this that the RobotC version of this project is kept alive as a branch. 

