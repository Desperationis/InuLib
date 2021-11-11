/** @file XLineFollower.h
 * @brief Bot for following a line using XAutoChassis.
 *
 * Bot for following a line using line sensors while using the flexibility of
 * XAutoChassis.
*/

#ifndef XLINEFOLLOWER_H
#define XLINEFOLLOWER_H

#include "main.h"
#include "pros/adi.hpp"

namespace inu {
	class AutoXChassis;
	class XLineFollowerBuilder;

	class XLineFollower {
	public:
		XLineFollower(XLineFollowerBuilder* builder);
		~XLineFollower() = default; // Do not free anything

		// If the line is detected on one of the line sensors,
		// try to make it the center; Blocking with timeout
		void Recenter();

		// Whether or not the line is detected on one of the sensors.
		bool LineDetected();

		// Whether or not a given light value means that the line is 
		// underneath it.
		bool IsLine(std::int32_t light);

		// Folows line; non blokcing
		void FollowLine();

		// Returns the recommended light threshold given that the center
		// sensor is on the line and the left and right are on the background
		std::int32_t DebugCalibrate();

		// Stop Following the line completely
		void Stop();

	private:
		AutoXChassis* chassis;
		unsigned int lightThreshold;
		bool activeOnDark;

		pros::ADILineSensor left, center,right;
		int leftError, centerError, rightError;
	};
}



#endif
