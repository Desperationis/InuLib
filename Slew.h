#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

#ifndef SLEW_STEP
	// The maximum amount of motor speed difference per tick.
	// Lower values are better.
	#define SLEW_STEP 15
#endif

/**
 * Set whether or not a motor will be slewed by setSlewMotor();
 * All motors are slewed by default.
 * Will not work until Slew() is started.
*/
void setSlew(tMotor port, bool active);


/**
 * Whether or not a motor is being slewed or not.
 * Will not work until Slew() is started.
*/
bool isSlewed(tMotor port);


/**
 * Set the slew target of a motor if the port is activated. If not,
 * speed will be set using motor[].
 * Will not work until Slew() is started.
*/
void setSlewMotor(tMotor port, byte speed);


/**
 * Starts slewing all motor ports. If not deactivated by setSlewMotor(),
 * every single motor port in motor[] will, by default, not be able to be controlled through
 * the array, but only by setSlewMotor().
*/
task Slew();

#include "src/Slew.c"
#endif
