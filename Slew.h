#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

#include "Helpers.h"


/**
 * Set whether or not a motor will be slewed by setSlewMotor();
 * All motors are slewed by default.
 * Will not work until startSlewTask()is called.
*/
void setSlew(tMotor port, bool active);


/**
 * Whether or not a motor is being slewed or not.
 * Will not work until startSlewTask()is called.
*/
bool isSlewed(tMotor port);


/**
 * Set the slew target of a motor if the port is activated. If not,
 * speed will be set using motor[].
 * Will not work until startSlewTask()is called.
*/
void setSlewMotor(tMotor port, byte speed);


/**
 * The background task responsible for slewing motors.
 * It is recommended to start this with startSlewTask().
*/
task Slew();


/**
 * Starts up the Slew() task and resets internal variables. By default,
 * motors are slewed. This can be changed using setSlew(port, active).
*/
void startSlewTask();

#include "src/Slew.c"
#endif
