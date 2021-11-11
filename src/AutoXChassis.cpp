#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/background/PIDInertialMotor.h"
#include "pros/llemu.hpp"

using namespace inu;

void AutoXChassis::Copy(const AutoXChassis& chassis) {
	topleftMotor = new inu::Motor(chassis.topleftMotor->get_port());
	toprightMotor = new inu::Motor(chassis.toprightMotor->get_port());
	bottomleftMotor = new inu::Motor(chassis.bottomleftMotor->get_port());
	bottomrightMotor = new inu::Motor(chassis.bottomrightMotor->get_port());

	// Don't copy inertial motors; They are created from the ports of the above
}

AutoXChassis::AutoXChassis(const AutoXChassis& chassis) : AutoChassis(chassis) {
	Copy(chassis);
	topleft = nullptr;
	topright = nullptr;
	bottomleft = nullptr;
	bottomright = nullptr;
}

void AutoXChassis::operator=(const AutoXChassis& chassis) {
	AutoChassis::operator=(chassis);
	Copy(chassis);
	topleft = nullptr;
	topright = nullptr;
	bottomleft = nullptr;
	bottomright = nullptr;
}

AutoXChassis::AutoXChassis(const AutoXChassisBuilder* builder) : AutoChassis(builder) { 
	topleftMotor = builder->GetTopleft();
	toprightMotor = builder->GetTopright();
	bottomleftMotor = builder->GetBottomleft();
	bottomrightMotor = builder->GetBottomright();

	topleft = nullptr;
	topright = nullptr;
	bottomleft = nullptr;
	bottomright = nullptr;
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
}

void AutoXChassis::TurnAbsolute(double degrees) {
	if(!usesGyro)
		return;


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

	topleftMotor->move(0);
	toprightMotor->move(0);
	bottomleftMotor->move(0);
	bottomrightMotor->move(0);
}
