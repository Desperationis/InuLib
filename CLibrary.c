#pragma systemFile
#include "CLibrary.h"

// TODO:
// 		PID Control


// Positive Power turns left motor clockwise. + Forward - Backward

// Left Axle Variables
// Ch4: X <- Ch3: Y Positive Down

// Right Axle Variables
// Ch1: X -> Ch2: Y Positive Down

// Public
short slewMotor[10];
short leftMotorPort;
short leftEncoderPort;
short rightMotorPort;
short rightEncoderPort;

double controllerSpeed;
double maximumMotorValue;

short taskDelay;
short slewStep;

// Private
double leftIntegral = 0.0;
double rightIntegral = 0.0;
double leftPastError = 0.0;
double rightPastError = 0.0;

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

void SetSlewStep(short step) {
	slewStep = step;
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

short GetSlewStep() {
	return slewStep;
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

short Step(short original, short step, short target){
	if(abs(original - target) > step){
		if(original > target) {
			return original - step;
		}
		return original + step;
	}
	return target;
}

short SlewStep(short original, short step, short target){
	if(abs(original - target) > step){
		// Ignore if target is "less" of a motor power than original
		if(abs(target) < abs(original) && target < 0 && original < 0) {
			return target;
		}
		if(abs(target) < abs(original) && target > 0 && original > 0) {
			return target;
		}
		return Step(original, step, target);
	}
	return target;
}

bool HasReached(short encoderPort, short value) {
	return abs(SensorValue[encoderPort]) > value;
}

bool BothHasReached(short enc1, short enc2, short value) {
	return HasReached(enc1, value) && HasReached(enc2, value);
}

// Tasks
task Slew() {
	for(short i = 0; i < 10; i++) {
		slewMotor[i] = 0;
	}

	while(true) {
		for(short i = 0; i < 10; i++) {
			motor[i] = Clamp(Step(motor[i], slewStep, slewMotor[i]));
		}
		delay(taskDelay);
	}
}

task LeftArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with left joystick.
		slewMotor[leftMotorPort] = Clamp(-vexRT[Ch3] - vexRT[Ch4]) * (maximumMotorValue / 127.0);
		slewMotor[rightMotorPort] = Clamp(-vexRT[Ch3] + vexRT[Ch4]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

task RightArcadeControl() {
	// Keep thread alive.
	while (true) {
		// Arcade control with right joystick.
		slewMotor[leftMotorPort] = Clamp(-vexRT[Ch2] + vexRT[Ch1]) * (maximumMotorValue / 127.0);
		slewMotor[rightMotorPort] = Clamp(-vexRT[Ch2] - vexRT[Ch1]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

task CustomTankControl() {
	// Keep thread alive.
	while (true) {
		// Tank control with both joysticks.
		slewMotor[leftMotorPort] = Clamp(-vexRT[Ch3]) * (maximumMotorValue / 127.0);
		slewMotor[rightMotorPort] = Clamp(-vexRT[Ch2]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

task GamerControl() {
	// Keep thread alive.
	while (true) {
		// Game control (Similar to controls in racing games)
		// Left Axis: up / down
		// Right Axis: right / left
		slewMotor[leftMotorPort] = Clamp(-vexRT[Ch3] + vexRT[Ch1]) * (maximumMotorValue / 127.0);
		slewMotor[rightMotorPort] = Clamp(-vexRT[Ch3] - vexRT[Ch1]) * (maximumMotorValue / 127.0);

		delay(taskDelay);
	}
}

// Functions
void MoveUntil(short encoderValue, short Lpow, short Rpow) {
	ResetEncoders();
	while(!BothHasReached(leftEncoderPort, rightEncoderPort, encoderValue)) {
		slewMotor[leftMotorPort] = Clamp(Lpow);
		slewMotor[rightMotorPort] = Clamp(Rpow);
		delay(taskDelay);
	}
	slewMotor[leftMotorPort] = 0;
	slewMotor[rightMotorPort] = 0;
}

short PIDCalculate(short encoderValue, short target, double* integral, double* pastError ) {
	double kP = 2.1;
	double kI = 0.0;
	double kD = 10;

	// LEFTMOTOR
	double difference = target - encoderValue;
	*integral += difference;
	double derivative = difference - *pastError;
	*pastError = difference;

	if(abs(difference) < 5) {
		*integral = 0;
	}

	return Clamp((difference * kP) + (*integral * kI) + (derivative * kD));
}

void PID(short target, short leftReverse, short rightReverse) {
	while(true) {
		slewMotor[leftMotorPort] = PIDCalculate(SensorValue[leftEncoderPort], target, &leftIntegral, &leftPastError) * leftReverse;
		slewMotor[rightMotorPort] = PIDCalculate(-SensorValue[rightEncoderPort], target, &rightIntegral, &rightPastError) * rightReverse;

		delay(taskDelay);
	}
}
