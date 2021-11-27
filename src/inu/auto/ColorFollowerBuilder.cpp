#include "inu/auto/ColorFollowerBuilder.h"
#include "inu/auto/chassis/AutoChassis.h"
#include "inu/auto/ColorFollower.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/InuException.hpp"
#include "pros/vision.h"
#include <memory>

using namespace inu;

ColorFollowerBuilder::ColorFollowerBuilder() {

}

void ColorFollowerBuilder::Reset() {
	signatures.clear();
	sensors.clear();
}


void ColorFollowerBuilder::SetChassis(std::weak_ptr<AutoChassis> chassis) {
	this->chassis = chassis;
}

void ColorFollowerBuilder::SetOptions(const ColorFollowerOptions& options) {
	this->options.reset(new ColorFollowerOptions(options));
}

void ColorFollowerBuilder::PushSensor(inu::port port, int centerX, int centerY) {
	inu::VisionSensor vision(port);
	vision.SetCenterPoint(centerX, centerY);
	sensors.push_back(vision);
}

void ColorFollowerBuilder::PushSignature(pros::vision_signature signature) {
	signatures.push_back(signature);
}

std::shared_ptr<ColorFollower> ColorFollowerBuilder::Build() {
	if(signatures.size() == 0) 
		throw InuException("ColorFollowerBuilder.h: Must set at least 1 signature.");

	if(sensors.size() == 0)
		throw InuException("ColorFollowerBuilder.h: Must set at least 1 vision sensor.");

	if(chassis.lock() == nullptr)
		throw InuException("ColorFollowerBuilder.h: Chassis not set.");

	if(options == nullptr)
		throw InuException("ColorFollowerBuilder.h: ColorFollowerOptions not set.");

	for(auto sensor : sensors) {
		for(size_t i = 0; i < signatures.size(); i++)
			sensor.SetSignature(i + 1, &signatures[i]);

		sensor.SetExposure(options->exposure);
		sensor.SetMinimumArea(options->minimumArea);
		sensor.SetZeroPoint(options->zeroPoint);
	}

	return std::shared_ptr<ColorFollower>(new ColorFollower(*this));
}

std::weak_ptr<AutoChassis> ColorFollowerBuilder::GetChassis() const {
	return chassis;
}

const std::vector<inu::VisionSensor> ColorFollowerBuilder::GetSensors() const {
	return sensors;
}

float ColorFollowerBuilder::GetSensitivity() const {
	return options->sensitivity;
}
