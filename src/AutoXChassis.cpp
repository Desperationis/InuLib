#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/background/PIDInertialMotor.h"
#include "pros/llemu.hpp"

using namespace inu;

AutoXChassis::AutoXChassis(const AutoXChassisBuilder* builder) : AutoChassis(builder) { 
	topleftMotor = builder->GetTopleft();
	toprightMotor = builder->GetTopright();
	bottomleftMotor = builder->GetBottomleft();
	bottomrightMotor = builder->GetBottomright();
}

AutoXChassis::~AutoXChassis() {
	delete topleftMotor;
	delete toprightMotor;
	delete bottomleftMotor;
	delete bottomrightMotor;

	topleftMotor = nullptr;
	toprightMotor = nullptr;
	bottomleftMotor = nullptr;
	bottomrightMotor = nullptr;
}

void AutoXChassis::TurnAbsolute(double degrees) {
	// Turn left or right depending on angle position.
	double angle = gyro->get_rotation();

	topleft = new PIDInertialMotor(topleftMotor->get_port(), gyroPort);
	topright = new PIDInertialMotor(toprightMotor->get_port(), gyroPort);
	bottomleft = new PIDInertialMotor(bottomleftMotor->get_port(), gyroPort);
	bottomright = new PIDInertialMotor(bottomrightMotor->get_port(), gyroPort);

	topright->SetPID(gyroPID);
	topleft->SetPID(gyroPID);
	bottomleft->SetPID(gyroPID);
	bottomright->SetPID(gyroPID);

	topright->SetMaximumVelocity(maxVelocity);
	topleft->SetMaximumVelocity(maxVelocity);
	bottomleft->SetMaximumVelocity(maxVelocity);
	bottomright->SetMaximumVelocity(maxVelocity);

	topright->Set(degrees);
	topleft->Set(degrees);
	bottomleft->Set(degrees);
	bottomright->Set(degrees);

	if(isStalling) {
		double secElapsed = 0;
		double secElapsedTarget = 0; // Within margin of error
		while(secElapsed < timeoutLimit && secElapsedTarget <= timeoutAlignLimit) {
			if(topleft->AtTarget(maxAngleError) &&
					topright->AtTarget(maxAngleError) &&
					bottomleft->AtTarget(maxAngleError) &&
					bottomright->AtTarget(maxAngleError)) {

				secElapsedTarget += 0.010;
			}

			else {
				secElapsedTarget = 0;
			}

			pros::delay(10);

			secElapsed += 0.010;
		}
	}

	if(isStalling) {
		Stop();
	}

}


void AutoXChassis::TurnA(double degrees) {
	AutoXChassis::TurnAbsolute(gyro->get_rotation() + degrees);
}

void AutoXChassis::Turn(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void AutoXChassis::Forward(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(-ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void AutoXChassis::Backward(double ticks) {
	Forward(-ticks);
}


void AutoXChassis::StrafeRight(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(-ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
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

void AutoXChassis::StallUntilSettled(double timeout) {
	double secElapsed = 0;
	double secElapsedTarget = 0;
	while(secElapsed < timeout && secElapsedTarget < timeoutAlignLimit) {
		pros::delay(10);
		secElapsed += 0.010;

		if(IsSettled()) {
			secElapsedTarget += 0.010;
		}
		else {
			secElapsedTarget = 0;
		}
	}
}


void AutoXChassis::Stop() {
	if(topleft != nullptr) {
		delete topleft;
		topleft = nullptr;
	}

	if(topright != nullptr) {
		delete topright;
		topright = nullptr;
	}

	if(bottomleft != nullptr) {
		delete bottomleft;
		bottomleft = nullptr;
	}

	if(bottomright != nullptr) {
		delete bottomright;
		bottomright = nullptr;
	}

	inu::Motor topleft(topleftMotor->get_port());
	inu::Motor topright(toprightMotor->get_port());
	inu::Motor bottomleft(bottomleftMotor->get_port());
	inu::Motor bottomright(bottomrightMotor->get_port());

	topleft.move(0);
	topright.move(0);
	bottomleft.move(0);
	bottomright.move(0);
}
