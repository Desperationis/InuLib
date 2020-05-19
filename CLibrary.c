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

int controllerSpeed = 1;
double maximumMotorValue = 127.0;
int leftMotorPort;
int rightMotorPort;
int leftEncoderPort;
int rightEncoderPort;
int taskDelay = 20;

void SetLeftMotor(int port) {
	SetUpInfo i;
	leftMotorPort = port;
}

void SetRightMotor(int port) {
	rightMotorPort = port;
}

void SetLeftEncoder(int port) {
	leftEncoderPort = port;
}

void SetRightEncoder(int port) {
	rightEncoderPort = port;
}

void SetControllerSpeed(double speed) {
	controllerSpeed = speed;
	maximumMotorValue = 127.0 / speed;
}

void SetAverageDelay(int delayTime) {
	taskDelay = delayTime;
}

int GetDelay() {
	return taskDelay;
}

int Clamp(int value) {
	// Clamps integers to maximum motor value; 127
	if (value > 127) {
		return 127;
	}
	if (value < -127) {
		return -127;
	}
	return value;
}

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
		motor[leftMotorPort] = Clamp(-vexRT[Ch3]) * (maximumMotorValue / 127);
		motor[rightMotorPort] = Clamp(-vexRT[Ch2]) * (maximumMotorValue / 127);

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

void MoveForwardUntil(int encoderValue) {
	while( abs(SensorValue[leftEncoderPort]) < encoderValue || abs(SensorValue[rightEncoderPort]) < encoderValue) {

	}
}
