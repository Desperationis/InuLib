/** @file ColorFollowerBuilder.h
 * @brief Build a ColorFollowerInstance.
*/



#ifndef COLORFOLLOWERBUILDER_H
#define COLORFOLLOWERBUILDER_H

#include "main.h"
#include "inu/Types.hpp"
#include "pros/vision.h"
#include <memory>
#include <cstdint>
#include <vector>

namespace inu {
	class AutoChassis;
	class VisionSensor;
	class ColorFollower;

	class ColorFollowerBuilder {
	public:
		enum LIGHTMODE {DEBUG, NONE};

		struct ColorFollowerOptions {
			std::uint8_t exposure = 70;
			pros::vision_zero zeroPoint = pros::E_VISION_ZERO_CENTER;
			float sensitivity = 0.3f; 
			unsigned int minimumArea = 200;
			LIGHTMODE mode = DEBUG;
		};

	public:
		ColorFollowerBuilder();

		void Reset();

		void SetChassis(std::weak_ptr<AutoChassis> chassis);

		void SetOptions(const ColorFollowerOptions& options);

		void PushSensor(inu::port port, int centerX, int centerY);

		void PushSignature(pros::vision_signature signature);

		std::shared_ptr<ColorFollower> Build();

		std::weak_ptr<AutoChassis> GetChassis() const;

		const std::vector<inu::VisionSensor> GetSensors() const;
		
		float GetSensitivity() const;

	private:
		std::vector<pros::vision_signature> signatures;
		std::vector<inu::VisionSensor> sensors;
		std::weak_ptr<AutoChassis> chassis;
		std::shared_ptr<ColorFollowerOptions> options;
	};
}

#endif
