#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/motor/PIDProfile.hpp"

using namespace inu;


AutoXChassis::AutoXChassis(int topleft, int topright, int bottomleft, int bottomright, int gyroPort) : 
	topleftMotor(topleft), toprightMotor(topright), bottomleftMotor(bottomleft), 
bottomrightMotor(bottomright), gyro(gyroPort)  {

}


void AutoXChassis::TurnA(double degrees) {
	// Turn left or right depending on angle position.
	double angle = gyro.get_rotation();

}

void AutoXChassis::Turn(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(ticks, maxVelocity);
}

void AutoXChassis::Forward(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(-ticks, maxVelocity);
	bottomleftMotor.move_relative(ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void AutoXChassis::Backward(double ticks) {
	Forward(-ticks);
}


void AutoXChassis::StrafeRight(double ticks) {
	topleftMotor.move_relative(ticks, maxVelocity);
	toprightMotor.move_relative(ticks, maxVelocity);
	bottomleftMotor.move_relative(-ticks, maxVelocity);
	bottomrightMotor.move_relative(-ticks, maxVelocity);
}

void AutoXChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool AutoXChassis::IsSettled() {
	return topleftMotor.Settled(maxError) &&
		toprightMotor.Settled(maxError) &&
		bottomleftMotor.Settled(maxError) && 
		bottomrightMotor.Settled(maxError);
}
