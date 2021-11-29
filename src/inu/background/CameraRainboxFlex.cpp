#include "inu/background/CameraRainbowFlex.h"
#include "inu/wrapper/VisionSensor.h"
#include "inu/background/BackgroundSystem.h"

using namespace inu;

CameraRainbowFlex::CameraRainbowFlex(inu::port port) : BackgroundTask(port) {
	sensor.reset(new VisionSensor(port));
	timer = 0;
	currentIndex = 0;
	this->port = port;

	BackgroundSystem::Instance()->EnrollTask(this);
}

CameraRainbowFlex::~CameraRainbowFlex() {
	BackgroundSystem::Instance()->RemoveTask(this);
}


void CameraRainbowFlex::_Update() {
	timer += BackgroundSystem::Instance()->GetDelay();

	if(timer > 125) {
		currentIndex += 1;
		if(currentIndex == colors.size())
			currentIndex = 0;

		timer = 0;
	}

	sensor->SetLED(colors[currentIndex]);
}
