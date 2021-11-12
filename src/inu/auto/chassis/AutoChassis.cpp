#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.hpp"

using namespace inu;

void AutoChassis::Copy(const AutoChassis& chassis) {
	maxEncoderError = chassis.maxEncoderError;
	maxAngleError = chassis.maxAngleError;
	maxVelocity = chassis.maxVelocity;
	currentLimit = chassis.currentLimit;
	timeoutLimit = chassis.timeoutLimit;
	timeoutAlignLimit = chassis.timeoutAlignLimit;

	usesGyro = chassis.usesGyro;
	if(usesGyro) {
		gyro = new pros::Imu(chassis.gyroPort);
		gyroPort = chassis.gyroPort;
	}
		
	isStalling = chassis.isStalling;

	encoderUnits = chassis.encoderUnits;
	gyroPID = chassis.gyroPID;
}

AutoChassis::AutoChassis(const AutoChassisBuilder* builder) {
	maxAngleError = builder->GetMaxAngleError();
	maxEncoderError = builder->GetMaxEncoderError();
	maxVelocity = builder->GetMaxVelocity();
	currentLimit = builder->GetCurrentLimit();
	timeoutLimit = builder->GetTimeout();
	isStalling = builder->IsStalling();
	timeoutAlignLimit = builder->GetTimeoutAlignLimit();

	usesGyro = builder->UsesGyro();
	gyro = nullptr;

	if(usesGyro) {
		gyro = new pros::Imu(builder->GetGyro());
		gyroPID = builder->GetGyroPID();
		gyroPort = builder->GetGyro();
	}

	encoderUnits = builder->GetEncoderUnits();
}


AutoChassis::AutoChassis(const AutoChassis& chassis) {
	Copy(chassis);
}

AutoChassis::~AutoChassis() {
	if(gyro != nullptr) {
		delete gyro;
		gyro = nullptr;
	}
};




