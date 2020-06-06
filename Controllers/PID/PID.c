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
	leftPID.kP = 0;
	leftPID.kI = 0;
	leftPID.kD = 0;

	rightPID.kP = 0;
	rightPID.kI = 0;
	rightPID.kD = 0;

	for(short i = 0; i < 2; i++) {
		target[i] = 0;
	}
	canPID = false;
}


void SetK(float kP, float kI, float kD) {
	leftPID.kP = kP;
	leftPID.kI = kI;
	leftPID.kD = kD;

	rightPID.kP = kP;
	rightPID.kI = kI;
	rightPID.kD = kD;
}


task PID() {
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
