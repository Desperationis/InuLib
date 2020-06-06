#pragma systemFile
#ifndef HELPERS_HEADER
#define HELPERS_HEADER

/*
 * Helpers.h
 *
 * General functions that are needed throughout the program.
*/


/*
 * [SETUP]
 *
 * Reset chassis' encoder's value to zero. Useful for preventing
 * integer overflow.
*/
void ResetEncoders();


/*
 * Clamps values down to -127 and 127. Used for motor speed.
*/
short Clamp(short value);


/*
 * "Steps" towards a value by a maximum amount.
*/
short Step(short original, short step, short target);

/*
 * "Steps" towards a value if the target's value's
 * is faster  than the original. Used for slew controller.
*/
short SlewStep(short original, short step, short target);


/*
 * Tells you whether or not an encoder has reached a threshold.
*/
bool HasReached(short encoderPort, short value);


/*
 * Tells you whether or not two encoders have reached a threshold.
 * Used by PID controller.
*/
bool BothHasReached(short encoder1, short encoder2, short value);




#endif
