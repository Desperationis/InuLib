/** @file CameraRainboxFlex.h
 * @brief FLEX by making a vision sensor cycle through rainbox colors.
*/

#ifndef CAMERARAINBOWFLEX_H
#define CAMERARAINBOWFLEX_H

#include "inu/background/BackgroundTask.h"
#include "inu/Types.hpp"
#include "pros/colors.h"
#include <cstdint>
#include <vector>

#include <memory>


namespace inu {
	class VisionSensor;

	class CameraRainbowFlex : public BackgroundTask {
	public:
		CameraRainbowFlex(inu::port cameraPort);

		~CameraRainbowFlex();

		void _Update() override;

	private: 
		std::unique_ptr<VisionSensor> sensor;
		std::uint32_t timer;
		size_t currentIndex;
		std::vector<int>colors = {
			RGB2COLOR(100, 0, 0), // RED
			RGB2COLOR(10, 255, 0), // ORANGE
			RGB2COLOR(0, 255, 0), // GREEN
			RGB2COLOR(0, 255, 10), // CYAN
			RGB2COLOR(0, 0, 100), // BLUE
			RGB2COLOR(1, 1, 100), // PURPLE
			//RGB2COLOR(100, 0, 100), // PINk
		};
	};
}




#endif
