#include "inu/auto/chassis/XAutoChassis.h"
#include "inu/motor/PIDProfile.hpp"

using namespace inu;


XAutoChassis::XAutoChassis(int topleft, int topright, int bottomleft, int bottomright, int gyroPort) : 
	topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft), 
bottomrightMotor(bottomright), gyro(gyroPort)  {

}


void XAutoChassis::TurnA(double degrees) {
	// Turn left or right depending on angle position.
	double angle = gyro.get_rotation();

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
	return topleftMotor.Settled(maxError) &&
		toprightMotor.Settled(maxError) &&
		bottomleftMotor.Settled(maxError) && 
		bottomrightMotor.Settled(maxError);
}
