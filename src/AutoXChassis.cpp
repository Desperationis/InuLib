#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/motor/PIDProfile.hpp"

using namespace inu;


AutoXChassis::AutoXChassis(const AutoXChassisBuilder* builder) : AutoChassis(builder) { 
	topleftMotor = builder->GetTopleft();
	toprightMotor = builder->GetTopright();
	bottomleftMotor = builder->GetBottomleft();
	bottomrightMotor = builder->GetBottomright();
}


void AutoXChassis::TurnA(double degrees) {
	// Turn left or right depending on angle position.
	//double angle = gyro.get_rotation();

}

void AutoXChassis::Turn(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(ticks, maxVelocity);
}

void AutoXChassis::Forward(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(-ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);
}

void AutoXChassis::Backward(double ticks) {
	Forward(-ticks);
}


void AutoXChassis::StrafeRight(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(-ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);
}

void AutoXChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool AutoXChassis::IsSettled() {
	return topleftMotor->IsSettled(maxEncoderError) &&
		toprightMotor->IsSettled(maxEncoderError) &&
		bottomleftMotor->IsSettled(maxEncoderError) && 
		bottomrightMotor->IsSettled(maxEncoderError);
}
