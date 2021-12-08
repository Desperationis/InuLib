/** @file ColorFollower.h
 * @brief Rotates chassis to follow an object.
 *
 * Rotates an AutoChassis to follow an object on a vision sensor.
*/ 


#ifndef COLORFOLLOWER_H
#define COLORFOLLOWER_H

#include "pros/vision.h"
#include <vector>
#include <memory>

namespace inu {
	class AutoChassis;
	class ColorFollowerBuilder;
	class VisionSensor;

	class ColorFollower {
	public:
		ColorFollower(const ColorFollowerBuilder& builder);

		bool ObjectDetected();

		void Follow(unsigned int error);

		void Stop();

		bool AtTarget(unsigned int error);
	private:
		std::vector<inu::VisionSensor> sensors;
		std::shared_ptr<AutoChassis> chassis;
		float sensitivity;
	};
}
#endif
