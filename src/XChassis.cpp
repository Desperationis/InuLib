#include "XChassis.h"
#include "PIDProfile.hpp"

XChassis::XChassis(int topleft, int topright, int bottomleft, int bottomright) : 
	topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft), 
bottomrightMotor(bottomright)  {}


void XChassis::TurnA(double degrees) {
	// Implement this once the gryoscope comes

}

void XChassis::Turn(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void XChassis::Forward(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(-ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void XChassis::Backward(double ticks) {
	Forward(-ticks);
}


void XChassis::StrafeRight(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(-ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void XChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool XChassis::IsSettled() {
	// FIX THIS
	return true;
}
