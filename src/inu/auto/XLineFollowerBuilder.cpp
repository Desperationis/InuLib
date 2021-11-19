#include "inu/auto/XLineFollowerBuilder.h"
#include "inu/auto/XLineFollower.h"
#include <memory>

using namespace inu;

XLineFollowerBuilder::XLineFollowerBuilder() { 
	Reset();
}

void XLineFollowerBuilder::Reset() {
	sensorsSet = false;
	activeOnDark = false;

	lightThreshold = 1000;
	chassis.reset();
	follower.reset();

	for(std::size_t i = 0; i < sensors.max_size(); i++) {
		sensors[i] = 0;
	}

	for(std::size_t i = 0; i < sensorError.max_size(); i++) {
		sensorError[i] = 0;
	}
}

void XLineFollowerBuilder::SetChassis(std::weak_ptr<AutoXChassis> chassis) {
	this->chassis = chassis;
}

void XLineFollowerBuilder::SetSensors(const std::array<std::uint8_t, 5>& lightSensors) {
	sensors = lightSensors;
	sensorsSet = true;
}

void XLineFollowerBuilder::SetSensorError(const std::array<int, 5>& errors) {
	sensorError = errors;
}

void XLineFollowerBuilder::SetLightThreshold(int threshold) {
	lightThreshold = threshold;
}

// Whether or not we will detect a reading if the tape is dark (high
// value). If not, it will activate when the tape is white (low value)
void XLineFollowerBuilder::ActivateOnDark(bool active) {
	activeOnDark = active;
}

std::weak_ptr<AutoXChassis> XLineFollowerBuilder::GetChassis() const {
	return chassis;
}

const std::array<std::uint8_t, 5> XLineFollowerBuilder::GetSensors() const {
	return sensors;
}

const std::array<int, 5> XLineFollowerBuilder::GetSensorErrors() const {
	return sensorError;
}

int XLineFollowerBuilder::GetLightThreshold() const {
	return lightThreshold;
}

bool XLineFollowerBuilder::IsActiveOnDark() const {
	return activeOnDark;
}

std::shared_ptr<XLineFollower> XLineFollowerBuilder::Build() {
	if(!sensorsSet) 
		return nullptr;

	return std::shared_ptr<XLineFollower>(new XLineFollower(*this));
}
