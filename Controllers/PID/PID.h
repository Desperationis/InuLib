#ifndef PID_HEADER
#define PID_HEADER

typedef struct {
	double kP;
	double kI;
	double kD;
	short proportion;
	short integral;
	short derivative;
	short pastError;
} PIDInfo;

/*
 * Calculate the motor speed of a motor given its encoder and information.
*/
short PIDCalculate(short encoderValue, short target, PIDInfo* info );
void PID(short target, short leftReverse, short rightReverse);

#endif
