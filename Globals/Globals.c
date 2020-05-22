#ifndef GLOBALS_SOURCE
#pragma systemFile
#define GLOBALS_SOURCE
#include "Globals.h"


// Globals
tMotor leftMotorPort;
tSensors leftEncoderPort;
tMotor rightMotorPort;
tSensors rightEncoderPort;

ubyte taskDelay;
ubyte slewStep;
double controllerSpeed;


// Setters
void SetLeftMotor(tMotor port) {
	leftMotorPort = port;
}

void SetRightMotor(tMotor port) {
	rightMotorPort = port;
}

void SetLeftEncoder(tSensors port) {
	leftEncoderPort = port;
}

void SetRightEncoder(tSensors port) {
	rightEncoderPort = port;
}

void SetControllerSpeed(double speed) {
	if(speed <= 1) {
		controllerSpeed = speed;
	}
}

void SetAverageDelay(ubyte delayTime) {
	taskDelay = delayTime;
}

void SetSlewStep(ubyte step) {
	slewStep = step;
}

// Getters
tMotor GetLeftMotor(){
	return leftMotorPort;
}

tMotor GetRightMotor(){
	return rightMotorPort;
}

tSensors GetLeftEncoder(){
	return leftEncoderPort;
}

tSensors GetRightEncoder(){
	return rightEncoderPort;
}

ubyte GetDelay() {
	return taskDelay;
}

ubyte GetSlewStep() {
	return slewStep;
}

double GetControllerSpeed(){
	return controllerSpeed;
}

#endif
