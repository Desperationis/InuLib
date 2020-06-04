#ifndef SLEW_HEADER
#define SLEW_HEADER

/*
 * Slew.h
 *
 * Slew Controller system. Should always be called on task main().
 * Slews all motors.
*/


task Slew();                                                                         // Slew all motors
void SetMotorSlew(tMotor port, byte speed);
void InitSlew();
void AllowSlew(tMotor port);
bool CanSlew(tMotor port);

/*
 * Set maximum slew step of the slew controller. Slewing ffected by SetTaskDelay().
*/
void SetSlewStep(ubyte step);

ubyte GetSlewStep();                                                                 // Gets the step amount of slew controller

#endif
