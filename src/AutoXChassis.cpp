#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/background/PIDMotor.h"
#include "inu/motor/DoubleVariant.hpp"
#include "pros/llemu.hpp"

using namespace inu;

AutoXChassis::AutoXChassis(const AutoXChassisBuilder* builder) : AutoChassis(builder) { 
	topleftMotor = builder->GetTopleft();
	toprightMotor = builder->GetTopright();
	bottomleftMotor = builder->GetBottomleft();
	bottomrightMotor = builder->GetBottomright();
}


void AutoXChassis::TurnA(double degrees) {
	// Turn left or right depending on angle position.
	gyro->tare_rotation();
	double angle = gyro->get_rotation();

	inu::PIDMotor* topleft = new PIDMotor(topleftMotor->get_port());
	inu::PIDMotor* topright = new PIDMotor(toprightMotor->get_port());
	inu::PIDMotor* bottomleft = new PIDMotor(bottomleftMotor->get_port());
	inu::PIDMotor* bottomright = new PIDMotor(bottomrightMotor->get_port());

	topright->SetPID(gyroPID);
	topleft->SetPID(gyroPID);
	bottomleft->SetPID(gyroPID);
	bottomright->SetPID(gyroPID);

	DoubleVariant* variant = new DoubleVariant(gyro);

	topright->UseVariant(variant);
	topleft->UseVariant(variant);
	bottomleft->UseVariant(variant);	
	bottomright->UseVariant(variant);

	topright->Set(degrees);
	topleft->Set(degrees);
	bottomleft->Set(degrees);
	bottomright->Set(degrees);

	double secElapsed = 0;
	while(secElapsed < timeoutLimit) {
		if(angle - maxAngleError < degrees && degrees < angle + maxAngleError)
			break;

		pros::delay(10);

		secElapsed += 0.010;
	}

	delete topleft;
	delete topright;
	delete bottomleft;
	delete bottomright;

	inu::Motor itopleft(topleftMotor->get_port());
	inu::Motor itopright(toprightMotor->get_port());
	inu::Motor ibottomleft(bottomleftMotor->get_port());
	inu::Motor ibottomright(bottomrightMotor->get_port());

	itopleft.move(0);
	itopright.move(0);
	ibottomleft.move(0);
	ibottomright.move(0);
}

void AutoXChassis::Turn(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(ticks, maxVelocity);

	StallUntilSettled(timeoutLimit);
}

void AutoXChassis::Forward(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(-ticks, maxVelocity);
	bottomleftMotor->move_relative(ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);

	StallUntilSettled(timeoutLimit);
}

void AutoXChassis::Backward(double ticks) {
	Forward(-ticks);
}


void AutoXChassis::StrafeRight(double ticks) {
	topleftMotor->move_relative(ticks, maxVelocity);
	toprightMotor->move_relative(ticks, maxVelocity);
	bottomleftMotor->move_relative(-ticks, maxVelocity);
	bottomrightMotor->move_relative(-ticks, maxVelocity);

	StallUntilSettled(timeoutLimit);
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
	while(!IsSettled() && secElapsed < timeout) {
		pros::delay(10);
		secElapsed += 0.010;
	}
}
