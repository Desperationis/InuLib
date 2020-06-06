#pragma systemFile
#ifndef PID_SOURCE
#define PID_SOURCE
#include "PID.h"
#include "../../Globals/Globals.h"
#include "../../Helpers/Helpers.h"
#include "../Slew/Slew.h"


PIDInfo leftPID;
PIDInfo rightPID;

short target[2];
bool canPID;


void InitPID() {
	for(short i = 0; i < 2; i++) {
		target[i] = 0;
	}
	canPID = false;
}


task PID() {
	double kP = 1.1;
	double kI = 0.0;
	double kD = 0;

	leftPID.kP = kP;
	leftPID.kI = kI;
	leftPID.kD = kD;

	rightPID.kP = kP;
	rightPID.kI = kI;
	rightPID.kD = kD;

	while(true) {
		if(canPID) {
			SetMotorSlew( GetLeftMotor(), PIDCalculate(SensorValue[GetLeftEncoder()], target[0], &leftPID));
			SetMotorSlew( GetRightMotor(), PIDCalculate(-SensorValue[GetRightEncoder()], target[1], &rightPID));
		}

		delay(GetDelay());
	}
}


short PIDCalculate(short encoderValue, short target, PIDInfo* info ) {
	// Calculate motor speed with PID info.
	info->proportion = target - encoderValue;

	info->integral += info->proportion;
	info->derivative = info->proportion - info->pastError;

	info->pastError = info->proportion;

	if(abs(info->proportion) < 5) {
		info->integral = 0;
	}

	return Clamp((info->proportion * info->kP) + (info->integral * info->kI) + (info->derivative * info->kD));
}


void SetPIDTarget(MOTOR side, short targetValue) {
	target[side] = targetValue;
}


void AllowPID(bool active) {
	canPID = active;
}


bool CanPID() {
	return canPID;
}


#endif
