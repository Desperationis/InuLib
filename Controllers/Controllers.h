#ifndef CONTROLLERS_HEADER
#define CONTROLLERS_HEADER
#include "../Globals/Globals.h"

/*
 * Controllers.h
 *
 * Functions and Tasks that directly control the robot's movements.
 *
*/

/*
 * Slew Controller system. Should always be called on task main().
 * Slews all motors.
*/

task LeftArcadeControl();                                                            // Control chassis with only the left joystick
task RightArcadeControl();                                                           // Control chassis with only the right joystick
task CustomTankControl();                                                            // Control chassis with both joysticks like a tank
task GamerControl();                                                                 // Control chassis with both joysticks like a gamer

// Functions
short PIDCalculate(short encoderValue, short target, PIDInfo* info );                // Calculate motor speed using PID
void PID(short target, short leftReverse, short rightReverse);

#endif
