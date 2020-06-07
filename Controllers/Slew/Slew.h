#pragma systemFile
#ifndef SLEW_HEADER
#define SLEW_HEADER

/*
 * Slew.h
 *
 * Slew Controller system. Deals with slewing motors.
*/


/*
 * Initialize slew controller variables. Called by InitCustomLibrary() automatically.
*/
void InitSlew();


/*
 * Passively slews motors. Needs to be started to take effect.
*/
task Slew();


/*
 * Slew step is the maximum difference in motor value allowed
 * before slewing.
 * This sets the slew step of the slew controller.
 * By default, slew step is set to 0.
 * Slewing affected by SetTaskDelay().
*/
void SetSlewStep(ubyte step);


/*
 * Get the slew step of the slew controller.
*/
ubyte GetSlewStep();


/*
 * Set the slew value of a motor. This value will be slowly
 * approached by the slew controller if enabled.
*/
void SetMotorSlew(tMotor port, byte speed);


/*
 * Allows a motor port to slew. By default, all motors
 * aren't slewed.
*/
void AllowSlew(tMotor port, bool active);


/*
 * Returns whether or not a motor is being slewed or not.
*/
bool CanSlew(tMotor port);

#endif
