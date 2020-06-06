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

enum MOTOR {
	LEFT = 0,
	RIGHT
};

/*
 * Calculate the motor speed of a motor given its encoder and information.
*/
short PIDCalculate(short encoderValue, short target, PIDInfo* info );

/*
 * [SETUP]
 *
 *
*/
task PID();

/*
 * [SETUP]
 * init before slew
 *
*/
void InitPID();

/*
 * [SETUP]
 *
 * Allows the chassis to be controlled by PID. Motors and encoders
 * most be defined beforehand in Setup. By default, the chassis
 * aren't controlled by PID.
*/
void AllowPID();

/*
 * Returns whether or not the chassis is being controlled by PID or not.
*/
bool CanPID();

void SetTarget(MOTOR side, short targetValue);

#endif
