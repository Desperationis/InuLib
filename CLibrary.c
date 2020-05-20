#pragma systemFile
#include "CLibrary.h"

// TODO:
//		Slew Control
// 		PID Control
//		Precision Control With Encoder


// Positive Power turns left motor clockwise. + Forward - Backward

// Left Axle Variables
// Ch4: X <- Ch3: Y Positive Down

// Right Axle Variables
// Ch1: X -> Ch2: Y Positive Down

short leftMotorPort;
short leftEncoderPort;
short rightMotorPort;
short rightEncoderPort;

double controllerSpeed;
double maximumMotorValue;

short taskDelay;

// Setters
void SetLeftMotor(short port) {
	leftMotorPort = port;
}

void SetRightMotor(short port) {
	rightMotorPort = port;
}

void SetLeftEncoder(short port) {
	leftEncoderPort = port;
}

void SetRightEncoder(short port) {
	rightEncoderPort = port;
}

void SetControllerSpeed(double speed) {
	if(speed <= 1) {
		controllerSpeed = speed;
		maximumMotorValue = 127.0 * speed;
	}
}

void SetAverageDelay(short delayTime) {
	taskDelay = delayTime;
}

// Getters
short GetLeftMotor(){
	return leftMotorPort;
}

short GetRightMotor(){
	return rightMotorPort;
}

short GetLeftEncoder(){
	return leftEncoderPort;
}

short GetRightEncoder(){
	return rightEncoderPort;
}

short GetDelay() {
	return taskDelay;
}

// Helper Functions
void ResetEncoders() {
	SensorValue[leftEncoderPort] = 0;
	SensorValue[rightEncoderPort] = 0;
}

short Clamp(short value) {
	// Clamps integers to maximum motor value; 127
	if (value > 127) {
		return 127;
	}
	if (value < -127) {
		return -127;
	}
	return value;
}

bool HasReached(short encoderPort, short value) {
	return abs(SensorValue[encoderPort]) > value;
}

bool BothHasReached(short enc1, short enc2, short value) {
	return HasReached(enc1, value) && HasReached(enc2, value);
}

// Tasks
task LeftArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with left joystick.
		motor[leftMotorPort] = Clamp(-vexRT[Ch3] - vexRT[Ch4]) * (maximumMotorValue / 127.0);
		motor[rightMotorPort] = Clamp(-vexRT[Ch3] + vexRT[Ch4]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}


task RightArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with right joystick.
		motor[leftMotorPort] = Clamp(-vexRT[Ch2] + vexRT[Ch1]) * (maximumMotorValue / 127.0);
		motor[rightMotorPort] = Clamp(-vexRT[Ch2] - vexRT[Ch1]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

task CustomTankControl() {
	// Keep thread alive.
	while (true) {
		// Tank control with both joysticks.
		motor[leftMotorPort] = Clamp(-vexRT[Ch3]) * (maximumMotorValue / 127.0);
		motor[rightMotorPort] = Clamp(-vexRT[Ch2]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

task GamerControl() {
	// Keep thread alive.
	while (true) {
		// Game control (Similar to controls in racing games)
		// Left Axis: up / down
		// Right Axis: right / left
		motor[leftMotorPort] = Clamp(-vexRT[Ch3] + vexRT[Ch1]) * (maximumMotorValue / 127.0);
		motor[rightMotorPort] = Clamp(-vexRT[Ch3] - vexRT[Ch1]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

// Functions
void MoveUntil(short encoderValue, short Lpow, short Rpow) {
	ResetEncoders();
	while(!BothHasReached(leftEncoderPort, rightEncoderPort, encoderValue)) {
		motor[leftMotorPort] = Clamp(Lpow);
		motor[rightMotorPort] = Clamp(Rpow);
		delay(taskDelay);
	}
	motor[leftMotorPort] = 0;
	motor[rightMotorPort] = 0;
}
