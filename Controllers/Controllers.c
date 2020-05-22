#ifndef CONTROLLERS_SOURCE

#define CONTROLLERS_SOURCE
#include "Controllers.h"
#include "../Globals/Globals.h"
#include "../Helpers/Helpers.h"

// TODO:
// 		PID Control


// Positive Power turns left motor clockwise. + Forward - Backward

// Left Axle Variables
// Ch4: X <- Ch3: Y Positive Down

// Right Axle Variables
// Ch1: X -> Ch2: Y Positive Down

// Public
short slewMotor[10];

// Private
PIDInfo leftPID;
PIDInfo rightPID;


// Tasks
task Slew() {
	for(short i = 0; i < 10; i++) {
		slewMotor[i] = 0;
	}

	while(true) {
		for(short i = 0; i < 10; i++) {
			// Replace with SlewStep for real-life
			motor[i] = Clamp(SlewStep(motor[i], GetSlewStep(), slewMotor[i] * GetControllerSpeed()));
		}
		delay(GetDelay());
	}
}

task LeftArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with left joystick.
		slewMotor[GetLeftMotor()] = Clamp(-vexRT[Ch3] - vexRT[Ch4]);
		slewMotor[GetRightMotor()] = Clamp(-vexRT[Ch3] + vexRT[Ch4]);

		delay(GetDelay());
	}
}

task RightArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with right joystick.
		slewMotor[GetLeftMotor()] = Clamp(-vexRT[Ch2] + vexRT[Ch1]);
		slewMotor[GetRightMotor()] = Clamp(-vexRT[Ch2] - vexRT[Ch1]);

		delay(GetDelay());
	}
}

task CustomTankControl() {
	// Keep thread alive.
	while (true) {
		// Tank control with both joysticks.
		slewMotor[GetLeftMotor()] = Clamp(-vexRT[Ch3]);
		slewMotor[GetRightMotor()] = Clamp(-vexRT[Ch2]);

		delay(GetDelay());
	}
}

task GamerControl() {
	// Keep thread alive.
	while (true) {
		// Game control (Similar to controls in racing games)
		// Left Axis: up / down
		// Right Axis: right / left
		slewMotor[GetLeftMotor()] = Clamp(-vexRT[Ch3] + vexRT[Ch1]);
		slewMotor[GetRightMotor()] = Clamp(-vexRT[Ch3] - vexRT[Ch1]);

		delay(GetDelay());
	}
}

// Functions
void MoveUntil(short encoderValue, short Lpow, short Rpow) {
	ResetEncoders();
	while(!BothHasReached(GetLeftEncoder(), GetRightEncoder(), encoderValue)) {
		slewMotor[GetLeftMotor()] = Clamp(Lpow);
		slewMotor[GetRightMotor()] = Clamp(Rpow);
		delay(GetDelay());
	}
	slewMotor[GetLeftMotor()] = 0;
	slewMotor[GetRightMotor()] = 0;
}

short PIDCalculate(short encoderValue, short target, PIDInfo* info ) {
	// LEFTMOTOR
	info->proportion = target - encoderValue;

	info->integral += info->proportion;
	info->derivative = info->proportion - info->pastError;

	info->pastError = info->proportion;

	if(abs(info->proportion) < 5) {
		info->integral = 0;
	}

	return Clamp((info->proportion * info->kP) + (info->integral * info->kI) + (info->derivative * info->kD));
}

void PID(short target, short leftReverse, short rightReverse) {
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
		slewMotor[GetLeftMotor()] = PIDCalculate(SensorValue[GetLeftEncoder()], target, &leftPID) * leftReverse;
		slewMotor[GetRightMotor()] = PIDCalculate(-SensorValue[GetRightEncoder()], target, &rightPID) * rightReverse;

		delay(GetDelay());
	}
}

#endif
