#include "inu/XAutoChassis.h"
#include "inu/PIDProfile.hpp"

using namespace inu;


XAutoChassis::XAutoChassis(int topleft, int topright, int bottomleft, int bottomright) : 
	topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft), 
bottomrightMotor(bottomright)  {

}


void XAutoChassis::TurnA(double degrees) {
	// Implement this once the gryoscope comes

}

void XAutoChassis::Turn(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void XAutoChassis::Forward(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(-ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void XAutoChassis::Backward(double ticks) {
	Forward(-ticks);
}


void XAutoChassis::StrafeRight(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(-ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void XAutoChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool XAutoChassis::IsSettled() {
	return true;
}
