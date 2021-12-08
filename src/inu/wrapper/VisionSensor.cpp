#include "inu/wrapper/VisionSensor.h"
#include "inu/InuException.hpp"
#include "pros/apix.h"

using namespace inu;
using pros::c::v5_device_e_t::E_DEVICE_VISION;

VisionSensor::VisionSensor(inu::port port) : vision(port) {
	if(port < 1 || port > 20)
		throw InuException("VisionSensor.h: Port must be between 1-20.");
	if(pros::c::registry_get_plugged_type(port - 1) != E_DEVICE_VISION)
		throw InuException("VisionSensor.h: Port is not a vision sensor");

	minimumArea = 200;
	centerX = 0;
	centerY = 0;
}

void VisionSensor::SetWifiMode(const std::uint8_t enable) {
	vision.set_wifi_mode(enable);
}

void VisionSensor::SetSignature(const std::uint8_t signatureID, pros::vision_signature_s_t* signature) {
	vision.set_signature(signatureID, signature);
}

void VisionSensor::SetExposure(const std::uint8_t exposure) {
	vision.set_exposure(exposure);
}

void VisionSensor::SetZeroPoint(pros::vision_zero_e_t zeroPoint) {
	vision.set_zero_point(zeroPoint);
}

void VisionSensor::SetCenterPoint(int x, int y) {
	centerX = x;
	centerY = y;
}

int VisionSensor::GetCenterOffsetX(const pros::vision_object_s_t& object) const {
	return object.x_middle_coord - centerX;
}

int VisionSensor::GetCenterOffsetY(const pros::vision_object_s_t& object) const {
	return object.y_middle_coord - centerY;
}

void VisionSensor::SetMinimumArea(unsigned int minimumArea) {
	this->minimumArea = minimumArea;
}

std::unique_ptr<pros::vision_object_s_t> VisionSensor::GetLargestObject() const {
	if(vision.get_object_count() == 0)
		return nullptr;

	auto biggestObject = vision.get_by_size(0);
	if(biggestObject.height * biggestObject.width < minimumArea)
		return nullptr;

	auto pObject = std::make_unique<pros::vision_object_s_t>();
	*pObject = biggestObject;

	return pObject;
}

unsigned int VisionSensor::GetObjectCount() const {
	return vision.get_object_count();
}

void VisionSensor::SetLED(std::int32_t rgb) const {
	vision.set_led(rgb);
}
