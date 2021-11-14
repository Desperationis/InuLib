#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"
#include "inu/auto/chassis/AutoXChassisBuilder.hpp"
#include "inu/motor/PIDProfile.hpp"
#include "inu/motor/background/PIDInertialMotor.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include "pros/llemu.hpp"

using namespace inu;

void AutoXChassis::Copy(const AutoXChassis& chassis) { 
	topleft = chassis.topleft->Clone();
	topright = chassis.topright->Clone();
	bottomleft = chassis.bottomleft->Clone();
	bottomright = chassis.bottomright->Clone();

	FreeBackgroundMotors();
}

AutoXChassis::AutoXChassis(const AutoXChassis& chassis) : AutoChassis(chassis) {
	Copy(chassis);
	FreeBackgroundMotors();
}

void AutoXChassis::operator=(const AutoXChassis& chassis) {
	AutoChassis::operator=(chassis);
	Copy(chassis);
	FreeBackgroundMotors();
}

AutoXChassis::AutoXChassis(const AutoXChassisBuilder* builder) : AutoChassis(builder) { 
	topleft = builder->GetTopleft();
	topright = builder->GetTopright();
	bottomleft = builder->GetBottomleft();
	bottomright = builder->GetBottomright();

	FreeBackgroundMotors();
}

AutoXChassis::~AutoXChassis() {
	delete topleft;
	delete topright;
	delete bottomleft;
	delete bottomright;

	topleft = nullptr;
	topright = nullptr;
	bottomleft = nullptr;
	bottomright = nullptr;

	FreeBackgroundMotors();
}

void AutoXChassis::Swerve(std::int8_t y, std::int8_t x) {
	y = std::clamp<std::int8_t>(y, -maxVelocity, maxVelocity);
	x = std::clamp<std::int8_t>(x, -maxVelocity, maxVelocity);

	std::int8_t leftSide = std::clamp<std::int8_t>(y + x, -maxVelocity, maxVelocity);
	std::int8_t rightSide = std::clamp<std::int8_t>(-y + x, -maxVelocity, maxVelocity);

	topleft->move(leftSide);
	topright->move(rightSide);
	bottomleft->move(leftSide);
	bottomright->move(rightSide);
}


void AutoXChassis::TurnAbsolute(double degrees) {
	if(!usesGyro)
		return;

	FreeBackgroundMotors();
	if(!CreateBackgroundMotors())
		return;

	// Turn left or right depending on angle position.
	double angle = gyro->get_rotation();


	inertialTopright->SetPID(gyroPID);
	inertialTopleft->SetPID(gyroPID);
	inertialBottomleft->SetPID(gyroPID);
	inertialBottomright->SetPID(gyroPID);

	inertialTopright->SetMaximumVelocity(maxVelocity);
	inertialTopleft->SetMaximumVelocity(maxVelocity);
	inertialBottomleft->SetMaximumVelocity(maxVelocity);
	inertialBottomright->SetMaximumVelocity(maxVelocity);

	inertialTopright->Set(degrees);
	inertialTopleft->Set(degrees);
	inertialBottomleft->Set(degrees);
	inertialBottomright->Set(degrees);

	if(isStalling) {
		double secElapsed = 0;
		double secElapsedTarget = 0; // Within margin of error
		while(secElapsed < timeoutLimit && secElapsedTarget <= timeoutAlignLimit) {
			if(inertialTopleft->AtTarget(maxAngleError) &&
					inertialTopright->AtTarget(maxAngleError) &&
					inertialBottomleft->AtTarget(maxAngleError) &&
					inertialBottomright->AtTarget(maxAngleError)) {

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
	FreeBackgroundMotors();

	topleft->move_relative(ticks, maxVelocity);
	topright->move_relative(ticks, maxVelocity);
	bottomleft->move_relative(ticks, maxVelocity);
	bottomright->move_relative(ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void AutoXChassis::Forward(double ticks) {
	FreeBackgroundMotors();

	topleft->move_relative(ticks, maxVelocity);
	topright->move_relative(-ticks, maxVelocity);
	bottomleft->move_relative(ticks, maxVelocity);
	bottomright->move_relative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void AutoXChassis::Backward(double ticks) {
	Forward(-ticks);
}


void AutoXChassis::StrafeRight(double ticks) {
	FreeBackgroundMotors();

	topleft->move_relative(ticks, maxVelocity);
	topright->move_relative(ticks, maxVelocity);
	bottomleft->move_relative(-ticks, maxVelocity);
	bottomright->move_relative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void AutoXChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool AutoXChassis::IsSettled() {
	return topleft->IsSettled(maxEncoderError) &&
		topright->IsSettled(maxEncoderError) &&
		bottomleft->IsSettled(maxEncoderError) && 
		bottomright->IsSettled(maxEncoderError);
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
	FreeBackgroundMotors();

	topleft->move(0);
	topright->move(0);
	bottomleft->move(0);
	bottomright->move(0);
}

void AutoXChassis::TareDistance() {
	topleft->tare_position();
	topright->tare_position();
	bottomleft->tare_position();
	bottomright->tare_position();
}

double AutoXChassis::GetDistance() {
	double tl = std::abs(topleft->get_position());
	double tr = std::abs(topright->get_position());
	double bl = std::abs(bottomleft->get_position());
	double br = std::abs(bottomright->get_position());

	return (tl + tr + bl + br) / 4;
}


void AutoXChassis::FreeBackgroundMotors() {
	if(inertialTopleft != nullptr) {
		delete inertialTopleft;
		inertialTopleft = nullptr;
	}

	if(inertialTopright != nullptr) {
		delete inertialTopright;
		inertialTopright = nullptr;
	}

	if(inertialBottomleft != nullptr) {
		delete inertialBottomleft;
		inertialBottomleft = nullptr;
	}

	if(inertialBottomright != nullptr) {
		delete inertialBottomright;
		inertialBottomright = nullptr;
	}
}

bool AutoXChassis::CreateBackgroundMotors() {
	int tl = topleft->get_port();
	int tr = topright->get_port();
	int bl = bottomleft->get_port();
	int br = bottomright->get_port();

	auto system = BackgroundMotorSystem::Instance();

	if(system->MotorExists(tl))
		return false;

	if(system->MotorExists(tr))
		return false;

	if(system->MotorExists(bl))
		return false;

	if(system->MotorExists(br)) 
		return false;

	inertialTopleft = new PIDInertialMotor(tl, gyroPort);
	inertialTopright = new PIDInertialMotor(tr, gyroPort);
	inertialBottomleft = new PIDInertialMotor(bl, gyroPort);
	inertialBottomright = new PIDInertialMotor(br, gyroPort);

	return true;
}
