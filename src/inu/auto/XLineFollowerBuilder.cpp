#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/auto/XLineFollower.h"

using namespace inu;

XLineFollowerBuilder::XLineFollowerBuilder() { 
	Reset();
}

void XLineFollowerBuilder::Reset() {
	sensorsSet = false;
	activeOnDark = false;

	lightThreshold = 1000;
	chassis = nullptr;
	follower = nullptr;

	leftError = 0;
	centerError = 0;
	rightError = 0;
}

void XLineFollowerBuilder::SetChassis(AutoXChassis* chassis) {
	this->chassis = chassis;
}

void XLineFollowerBuilder::SetSensors(unsigned int left, unsigned int center, unsigned int right) {
	leftPort = left;
	centerPort = center;
	rightPort = right;
	sensorsSet = true;
}

void XLineFollowerBuilder::SetSensorError(int left, int center, int right) {
	leftError = left;
	centerError = center;
	rightError = right;
}

void XLineFollowerBuilder::SetLightThreshold(unsigned int threshold) {
	lightThreshold = threshold;
}

// Whether or not we will detect a reading if the tape is dark (high
// value). If not, it will activate when the tape is white (low value)
void XLineFollowerBuilder::ActivateOnDark(bool active) {
	activeOnDark = active;
}

AutoXChassis* XLineFollowerBuilder::GetChassis() const {
	return chassis;
}

unsigned int XLineFollowerBuilder::GetLeftSensor() const {
	return leftPort;
}

unsigned int XLineFollowerBuilder::GetCenterSensor() const {
	return centerPort;
}

unsigned int XLineFollowerBuilder::GetRightSensor() const {
	return rightPort;
}

int XLineFollowerBuilder::GetLeftSensorError() const {
	return leftError;
}

int XLineFollowerBuilder::GetCenterSensorError() const {
	return centerError;
}

int XLineFollowerBuilder::GetRightSensorError() const {
	return rightError;
}

unsigned int XLineFollowerBuilder::GetLightThreshold() const {
	return lightThreshold;
}

bool XLineFollowerBuilder::IsActiveOnDark() const {
	return activeOnDark;
}

XLineFollower* XLineFollowerBuilder::Build() {
	if(!sensorsSet) 
		return nullptr;

	return new XLineFollower(this);
}
