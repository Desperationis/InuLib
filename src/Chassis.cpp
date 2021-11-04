#include "Chassis.h"
#include "PIDProfile.hpp"

Chassis::Chassis(int topleft, int topright, int bottomleft, int bottomright)
	: topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft),
	bottomrightMotor(bottomright) {

	PIDProfile profile;
	profile.p = 0.05;
	profile.i = 0.01;
	profile.d = 0.05;

	topleftMotor.SetPID(profile);
	toprightMotor.SetPID(profile);
	bottomleftMotor.SetPID(profile);
	bottomrightMotor.SetPID(profile);
}


void Chassis::turnA(double degrees) {

}

void Chassis::turn(double ticks) {
	topleftMotor.Set(ticks);
	toprightMotor.Set(ticks);
	bottomleftMotor.Set(ticks);
	bottomleftMotor.Set(ticks);
}

void Chassis::forward(double ticks) {

}

