#include "XChassis.h"
#include "PIDProfile.hpp"

XChassis::XChassis(int topleft, int topright, int bottomleft, int bottomright) : 
	topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft), 
bottomrightMotor(bottomright) 
	
{
}


void XChassis::turnA(double degrees) {
	// Implement this once the gryoscope comes

}

void XChassis::turn(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void XChassis::forward(double ticks) {
	// FIX THIS
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void XChassis::backward(double ticks) {
	forward(-ticks);
}


void XChassis::strafeRight(double ticks) {
	// FIX THIS
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void XChassis::strafeLeft(double ticks) {
	strafeRight(-ticks);
}

bool XChassis::isSettled() {
	// FIX THIS
	return true;
}

void XChassis::MaxVelocity(std::int32_t velocity) {
	maxVelocity = velocity;
}
