#include "XChassis.h"
#include "PIDProfile.hpp"

XChassis::XChassis(int topleft, int topright, int bottomleft, int bottomright) {
	PIDProfile profile;
	profile.p = 0.05;
	profile.i = 0.01;
	profile.d = 0.05;

	topleftMotor = new PIDMotor(topleft);
	toprightMotor = new PIDMotor(topright);
	bottomleftMotor = new PIDMotor(bottomleft);
	bottomrightMotor = new PIDMotor(bottomright);

	topleftMotor->SetPID(profile);
	toprightMotor->SetPID(profile);
	bottomleftMotor->SetPID(profile);
	bottomrightMotor->SetPID(profile);
}


void XChassis::turnA(double degrees) {
	// Implement this once the gryoscope comes

}

void XChassis::turn(double ticks) {
	topleftMotor->Set(ticks);
	toprightMotor->Set(ticks);
	bottomleftMotor->Set(ticks);
	bottomleftMotor->Set(ticks);
}

void XChassis::forward(double ticks) {
	topleftMotor->Set(ticks);
	toprightMotor->Set(-ticks);
	bottomleftMotor->Set(-ticks);
	bottomleftMotor->Set(ticks);
}

