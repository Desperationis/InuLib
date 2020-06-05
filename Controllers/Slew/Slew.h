#ifndef SLEW_HEADER
#define SLEW_HEADER

/*
 * Slew.h
 *
 * Slew Controller system. Should always be called on task main().
 * Slews all motors.
*/

/*
 * Passively slews all motors. Should be run after InitSlew().
*/
task Slew();

/*
 * Set the slew value of a motor. This value will be slowly
 * approached by the slew controller.
*/
void SetMotorSlew(tMotor port, byte speed);

/*
 * [SETUP]
 *
 * Initialize slew controller variables. Should be run
 * before using Slew().
*/
void InitSlew();

/*
 * [SETUP]
 *
 * Allows a motor port to slew. By default, all motors
 * aren't slewed.
*/
void AllowSlew(tMotor port);

/*
 * Returns whether or not a motor is being slewed or not.
*/
bool CanSlew(tMotor port);

/*
 * [SETUP]
 *
 * Set maximum slew step of the slew controller. Slewing ffected by SetTaskDelay().
*/
void SetSlewStep(ubyte step);

/*
 * Get the maximum slew step of the slew controller.
*/
ubyte GetSlewStep();

#endif
