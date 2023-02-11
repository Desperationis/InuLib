#include "inu/chassis/XChassis.h"
#include "inu/InuException.hpp"
#include <cstdint>

using namespace inu;

XChassis::XChassis(const XChassis& chassis) : topleft(chassis.topleft), topright(chassis.topright), bottomleft(chassis.bottomleft), bottomright(chassis.bottomright) {

}

void XChassis::operator=(const XChassis& chassis) {
	topleft = chassis.topleft;
	topright = chassis.topright;
	bottomleft = chassis.bottomleft;
	bottomright = chassis.bottomright;
}

XChassis::XChassis(inu::port tl, inu::port tr, inu::port bl, inu::port br) : topleft(tl), topright(tr), bottomleft(bl), bottomright(br) {

}

XChassis::~XChassis() {
	topleft.Shutdown();
	topright.Shutdown();
	bottomleft.Shutdown();
	bottomright.Shutdown();
}

void XChassis::Swerve(std::int8_t forward, std::int8_t right, std::int8_t turn) {
	auto maxVelocity = chassisOptions.maxVelocity;

	forward = std::clamp<std::int8_t>(forward, -maxVelocity, maxVelocity);
	right = std::clamp<std::int8_t>(right, -maxVelocity, maxVelocity);
	turn = std::clamp<std::int8_t>(turn, -maxVelocity, maxVelocity);

	auto tl = std::clamp<std::int8_t>(forward + turn + right, -maxVelocity, maxVelocity);
	auto bl = std::clamp<std::int8_t>(forward + turn - right, -maxVelocity, maxVelocity);
	auto tr = std::clamp<std::int8_t>(-forward + turn + right, -maxVelocity, maxVelocity);
	auto br = std::clamp<std::int8_t>(-forward + turn - right, -maxVelocity, maxVelocity);

	topleft->MoveVelocity(tl);
	topright->MoveVelocity(tr);
	bottomleft->MoveVelocity(bl);
	bottomright->MoveVelocity(br);
}

void XChassis::RawSwerve(std::int8_t forward, std::int8_t right, std::int8_t turn) {
	forward = std::clamp<std::int8_t>(forward, -127, 127);
	right = std::clamp<std::int8_t>(right, -127, 127);
	turn = std::clamp<std::int8_t>(turn, -127, 127);

	auto tl = std::clamp<std::int16_t>(forward + turn + right, -127, 127);
	auto bl = std::clamp<std::int16_t>(forward + turn - right, -127, 127);
	auto tr = std::clamp<std::int16_t>(-forward + turn + right, -127, 127);
	auto br = std::clamp<std::int16_t>(-forward + turn - right, -127, 127);

	topleft->Move(tl);
	topright->Move(tr);
	bottomleft->Move(bl);
	bottomright->Move(br);
}

void XChassis::TurnAbsolute(double degrees) {
	if(!usesGyro)
		throw InuException("XChassis.h: Cannot TurnAbsolute() as gyro has not been defined.");

	FreeBackgroundMotors();
	if(!CreateBackgroundMotors())
		throw InuException("XChassis.h: Cannot TurnAbsolute() as background motors were unable to be created.");

	// Turn left or right depending on angle position.
	double angle = gyro->GetRotation();

	inertialTopright->Set(degrees);
	inertialTopleft->Set(degrees);
	inertialBottomleft->Set(degrees);
	inertialBottomright->Set(degrees);

	auto isStalling = chassisOptions.stalls;
	auto timeoutLimit = chassisOptions.timeoutLimit;
	auto timeoutAlignLimit = chassisOptions.timeoutAlignLimit;
	auto maxAngleError = gyroOptions.steadyStateAngleError;

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


void XChassis::TurnA(double degrees) {
	XChassis::TurnAbsolute(gyro->GetRotation() + degrees);
}

void XChassis::Turn(double ticks) {
	FreeBackgroundMotors();

	auto maxVelocity = chassisOptions.maxVelocity;
	auto timeoutLimit = chassisOptions.timeoutLimit;
	auto isStalling = chassisOptions.stalls;

	topleft->MoveRelative(ticks, maxVelocity);
	topright->MoveRelative(ticks, maxVelocity);
	bottomleft->MoveRelative(ticks, maxVelocity);
	bottomright->MoveRelative(ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void XChassis::Forward(double ticks) {
	FreeBackgroundMotors();
	Stop();

	auto maxVelocity = chassisOptions.maxVelocity;
	auto timeoutLimit = chassisOptions.timeoutLimit;
	auto isStalling = chassisOptions.stalls;

	topleft->MoveRelative(ticks, maxVelocity);
	topright->MoveRelative(-ticks, maxVelocity);
	bottomleft->MoveRelative(ticks, maxVelocity);
	bottomright->MoveRelative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void XChassis::Backward(double ticks) {
	Forward(-ticks);
}


void XChassis::StrafeRight(double ticks) {
	FreeBackgroundMotors();

	auto maxVelocity = chassisOptions.maxVelocity;
	auto timeoutLimit = chassisOptions.timeoutLimit;
	auto isStalling = chassisOptions.stalls;

	topleft->MoveRelative(ticks, maxVelocity);
	topright->MoveRelative(ticks, maxVelocity);
	bottomleft->MoveRelative(-ticks, maxVelocity);
	bottomright->MoveRelative(-ticks, maxVelocity);

	if(isStalling) {
		StallUntilSettled(timeoutLimit);
		Stop();
	}
}

void XChassis::StrafeLeft(double ticks) {
	StrafeRight(-ticks);
}

bool XChassis::IsSettled() {
	auto maxEncoderError = chassisOptions.steadyStateEncoderError;

	return topleft->IsSettled(maxEncoderError) &&
		topright->IsSettled(maxEncoderError) &&
		bottomleft->IsSettled(maxEncoderError) && 
		bottomright->IsSettled(maxEncoderError);
}

void XChassis::StallUntilSettled(double timeout) {
	double secElapsed = 0;
	double secElapsedTarget = 0;
	auto timeoutAlignLimit = chassisOptions.timeoutAlignLimit;

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


void XChassis::Stop() {
	FreeBackgroundMotors();

	topleft->MoveVelocity(0);
	topright->MoveVelocity(0);
	bottomleft->MoveVelocity(0);
	bottomright->MoveVelocity(0);
}

void XChassis::TareDistance() {
	topleft->TarePosition();
	topright->TarePosition();
	bottomleft->TarePosition();
	bottomright->TarePosition();
}

double XChassis::GetDistance() {
	double tl = std::abs(topleft->GetPosition());
	double tr = std::abs(topright->GetPosition());
	double bl = std::abs(bottomleft->GetPosition());
	double br = std::abs(bottomright->GetPosition());

	return (tl + tr + bl + br) / 4;
}

double XChassis::GetAbsoluteRotation() {
	return gyro->GetRotation();
}

void XChassis::FreeBackgroundMotors() {
	inertialTopleft.reset();
	inertialTopright.reset();
	inertialBottomleft.reset();
	inertialBottomright.reset();
}

bool XChassis::CreateBackgroundMotors() {
	int tl = topleft->GetPort();
	int tr = topright->GetPort();
	int bl = bottomleft->GetPort();
	int br = bottomright->GetPort();

	auto system = BackgroundSystem::Instance();

	if(system->TaskExists(tl))
		return false;

	if(system->TaskExists(tr))
		return false;

	if(system->TaskExists(bl))
		return false;

	if(system->TaskExists(br)) 
		return false;

	auto gyroPID = gyroOptions.gyroPID;
	auto maxVelocity = chassisOptions.maxVelocity;


	// exceptions pls
	inertialTopleft.reset(new PIDInertialMotor(tl, gyroPort, gyroPID));
	inertialTopright.reset(new PIDInertialMotor(tr, gyroPort, gyroPID));
	inertialBottomleft.reset(new PIDInertialMotor(bl, gyroPort, gyroPID));
	inertialBottomright.reset(new PIDInertialMotor(br, gyroPort, gyroPID));

	inertialTopright->SetPID(gyroPID);
	inertialTopleft->SetPID(gyroPID);
	inertialBottomleft->SetPID(gyroPID);
	inertialBottomright->SetPID(gyroPID);

	inertialTopright->SetMaximumVelocity(maxVelocity);
	inertialTopleft->SetMaximumVelocity(maxVelocity);
	inertialBottomleft->SetMaximumVelocity(maxVelocity);
	inertialBottomright->SetMaximumVelocity(maxVelocity);

	return true;
}

