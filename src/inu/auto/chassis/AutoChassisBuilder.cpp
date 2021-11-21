#include "inu/auto/chassis/AutoChassisBuilder.h"
#include "inu/InuException.hpp"

using namespace inu;

AutoChassisBuilder::AutoChassisBuilder() {
	Reset();
}

void AutoChassisBuilder::Reset() {
	chassisOptions = AutoChassisOptions();
	gyroOptions = AutoChassisGyroOptions();
	usesGyro = false;
	gyroPort = 0;
}


void AutoChassisBuilder::SetGyro(inu::port port, const AutoChassisGyroOptions& gyroOptions) {
	if(port < 1 || port > 20)
		throw InuException("AutoChassisBuilder.h: The port must be between 1-20.");

	this->gyroPort = port;
	this->gyroOptions = gyroOptions;
	this->usesGyro = true;
}

void AutoChassisBuilder::SetChassisOptions(const AutoChassisOptions& options) {
	if(options.timeoutLimit < 0)
		throw InuException("AutoChassisBuilder.h: Timeout Limit must be positive.");

	if(options.timeoutAlignLimit < 0) 
		throw InuException("AutoChassisBuilder.h: Timeout Align Limit must be positive.");

	this->chassisOptions = options;
}

AutoChassisBuilder::AutoChassisOptions AutoChassisBuilder::GetChassisOptions() const {
	return chassisOptions;
}

AutoChassisBuilder::AutoChassisGyroOptions AutoChassisBuilder::GetGyroOptions() const {
	return gyroOptions;
}

inu::port AutoChassisBuilder::GetGyroPort() const {
	return gyroPort;
}

bool AutoChassisBuilder::UsesGyro() const {
	return usesGyro;
}
