#include "inu/wrapper/VisionSensor.h"
#include "pros/vision.h"

using namespace inu;

VisionSensor::VisionSensor(unsigned int port) : vision(port) {
	minimumArea = 200;
	centerX = 0;
	centerY = 0;
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
