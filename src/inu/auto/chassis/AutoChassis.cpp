#include "inu/auto/chassis/AutoXChassis.h"
#include "inu/auto/chassis/AutoChassisBuilder.h"
#include <memory>

using namespace inu;

void AutoChassis::Copy(const AutoChassis& chassis) {
	chassisOptions = chassis.chassisOptions;

	usesGyro = chassis.usesGyro;
	if(usesGyro) {
		gyroOptions = chassis.gyroOptions;
		gyro.reset(new InertialSensor(chassis.gyroPort));
		gyroPort = chassis.gyroPort;
	}
}

AutoChassis::AutoChassis(const AutoChassisBuilder& builder) {
	chassisOptions = builder.GetChassisOptions();

	usesGyro = builder.UsesGyro();
	gyro = nullptr;

	if(usesGyro) {
		gyro.reset(new InertialSensor(builder.GetGyroPort()));
		gyroOptions = builder.GetGyroOptions();
		gyroPort = builder.GetGyroPort();
	}
}


AutoChassis::AutoChassis(const AutoChassis& chassis) {
	Copy(chassis);
}

AutoChassis::~AutoChassis() {
	gyro.reset();
};
