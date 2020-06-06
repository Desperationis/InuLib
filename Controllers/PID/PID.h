#pragma systemFile
#ifndef PID_HEADER
#define PID_HEADER

typedef struct {
	float kP;
	float kI;
	float kD;
	short proportion;
	short integral;
	short derivative;
	short pastError;
} PIDInfo;

/*
 * Calculate the motor speed of a motor given its encoder and information.
*/
short PIDCalculate(short encoderValue, short target, PIDInfo* info );

/*
 * [SETUP]
 *
 *
*/
void PID(short target);

#endif
