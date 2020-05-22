#ifndef GLOBALS_SOURCE

#define GLOBALS_SOURCE
#include "Globals.h"


// Globals
short leftMotorPort;
short leftEncoderPort;
short rightMotorPort;
short rightEncoderPort;
double controllerSpeed;
double maximumMotorValue;
short taskDelay;
short slewStep;



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

double GetMaximumMotor(){
	return maximumMotorValue;
}

#endif
