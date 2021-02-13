#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

#include "Helpers.h"


/**
 * Permanently disable a motor from being able to slew.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
void DisableSlew(tMotor port);


/**
 * Determine if a motor is slewed or not.
 * Will not work until StartSlewTask(_slewStep)is called.
*/
bool CanSlew(tMotor port);

/**
 * Set the slew target of a motor, if possible. If not,
 * speed will be set using motor[].
*/
void SetSlewMotor(tMotor port, byte speed);


/**
 * The background task responsible for slewing motors.
 * It is recommended to start this with StartSlewTask().
*/
task Slew();


/**
 * Starts up the Slew() task and resets internal variables. By default,
 * motors are slewed. This can be changed using DisableSlew(port).
*/
void StartSlewTask();

#include "src/Slew.c"
#endif
