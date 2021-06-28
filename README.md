# InuLib
A general PROS library for controlling a VEX Cortex with support with Raspberry Pi integration.

# Features
This library mainly features two things: a system for controlling your robot easily with a VEX controller and packet-based serial reading and writing system.

## Controller System
Controlling a VEX robot is done through a state machine found in `Controllers.c` that takes in pointers to functions as inputs. These functions are of type `void` with no arguments and are called in an internal loop found in `Controllers.c`. Due to how it is programmed, you can really easily and quickly hot-swap between different type of controller configurations with a button without worrying about ending and starting background tasks. Built in controllers can be found in `Controllers.c` that read `enum`'s for motor ports.

The built-in controllers started with this system run in the background and are additionally slewed if the bog-standard slewing system is enabled. In addition to this, their sensitivity can be tuned with `control_set_scale()` so that a max or minimum speed can be set.

## Serial System
This library features a packet-based serial system on the UART ports of the VEX Cortex based on the defunct project [VEXSerial](https://github.com/EvolvedAwesome/VEXSerial) in `Serial.c`. Each "message" sent across the ports are of variable length and start with a header number defined to be 255, meaning only bytes with values between 0-254 can be sent at a time. 

The purpose of this system is to interface with a Raspberry Pi running a python script sending and reading serial data to the Cortex, though interfacing with any other device, like another Cortex, is very likely possible. I personally have used this system to control the Cortex with UDP sockets to send PS4 controller input from my computer, though anything is possible. Automated steering, for example, can be done if the Raspberry Pi has a camera and artifical intelligence to determine what inputs need to be sent. 

