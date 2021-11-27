#include "inu/auto/ColorFollower.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/auto/chassis/AutoChassis.h"
#include "inu/auto/ColorFollowerBuilder.h"
#include "pros/vision.h"
#include <memory>

using namespace inu;

ColorFollower::ColorFollower(const ColorFollowerBuilder& builder) {
	chassis = builder.GetChassis().lock();
	sensors = builder.GetSensors();
	sensitivity = builder.GetSensitivity();
}

bool ColorFollower::ObjectDetected() {
	for(auto sensor : sensors) {
		if(sensor.GetLargestObject() != nullptr)
			return true;
	}

	return false;
}

void ColorFollower::Follow(unsigned int error) {
	while(ObjectDetected()) {
		std::unique_ptr<pros::vision_object_s_t> largestObject;
		int currentSensor = -1;

		for(size_t i = 0; i < sensors.size(); i++) {
			auto sensor = sensors[i];
			auto obj = sensor.GetLargestObject();
			if(obj != nullptr) {
				largestObject = std::move(obj);
				currentSensor = i;
				break;
			}
		}

		if(largestObject == nullptr)
			break;

		if(AtTarget(error))
			break;

		for(size_t i = 0; i < sensors.size(); i++) {
			auto sensor = sensors[i];
			if(i != currentSensor) 
				sensor.SetLED(RGB2COLOR(0,0,0));
		}
		sensors[currentSensor].SetLED(RGB2COLOR(0,0,255));

		int speed = sensors[currentSensor].GetCenterOffsetX(*largestObject) * sensitivity;
		chassis->Swerve(0, speed);

		pros::delay(20);
	}

	for(auto sensor : sensors)
		sensor.SetLED(RGB2COLOR(0,0,0));
	chassis->Swerve(0, 0);
}

bool ColorFollower::AtTarget(unsigned int error) {
	if(!ObjectDetected())
		return false;

	std::unique_ptr<pros::vision_object_s_t> largestObject;
	inu::VisionSensor* currentSensor = nullptr;
	for(auto sensor : sensors) {
		auto obj = sensor.GetLargestObject();
		if(obj != nullptr) {
			largestObject = std::move(obj);
			currentSensor = &sensor;
			break;
		}
	}

	return std::abs(currentSensor->GetCenterOffsetX(*largestObject)) < error;
}
