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
 * Arcade control with the left joystick. Supports slewing motors.
*/
task LeftArcadeControl();


/*
 * Arcade control with the right joystick. Supports slewing motors.
*/
task RightArcadeControl();


/*
 * Tank control with slewing support.
*/
task CustomTankControl();


/*
 * Control the chassis like a video game car! Supports slewing motors.
*/
task GamerControl();


/*
 * Calculate the motor speed of a motor given its encoder and information.
*/
short PIDCalculate(short encoderValue, short target, PIDInfo* info );                // Calculate motor speed using PID
void PID(short target, short leftReverse, short rightReverse);

#endif
