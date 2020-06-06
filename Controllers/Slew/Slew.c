#pragma systemFile
#ifndef SLEW_SOURCE
#define SLEW_SOURCE
#include "Slew.h"
#include "../../Globals/Globals.h"
#include "../../Helpers/Helpers.h"


short slewMotor[10];
bool slewWhitelist[10];
ubyte slewStep;


void InitSlew() {
	for(short i = 0; i < 10; i++) {
		slewMotor[i] = 0;
		slewWhitelist[i] = false;
	}
	slewStep = 0;
}


task Slew() {
	while(true) {
		for(short i = 0; i < 10; i++) {
			if(CanSlew(i)) {
				motor[i] = Clamp(SlewStep(motor[i], GetSlewStep(), slewMotor[i] * GetMaxSpeed()));
			}
		}
		delay(GetDelay());
	}
}


void SetSlewStep(ubyte step) {
	slewStep = step;
}


ubyte GetSlewStep() {
	return slewStep;
}


void SetMotorSlew(tMotor port, byte speed) {
	// Only slew motor if it is enabled.
	if(CanSlew(port)){
		slewMotor[port] = speed;
	}
	else {
		motor[port] = speed;
	}
}


void AllowSlew(tMotor port, bool active) {
	slewWhitelist[port] = active;
}


bool CanSlew(tMotor port) {
	return slewWhitelist[port];
}
#endif
