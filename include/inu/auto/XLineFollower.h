/** @file XLineFollower.h
 * @brief Bot for following a line using XAutoChassis.
 *
 * Bot for following a line using line sensors while using the flexibility of
 * XAutoChassis.
*/

#ifndef XLINEFOLLOWER_H
#define XLINEFOLLOWER_H

#include "inu/wrapper/ADIMotor.h"
#include "main.h"
#include "inu/wrapper/LineSensor.h"
#include <memory>
#include <array>

namespace inu {
	class AutoXChassis;
	class XLineFollowerBuilder;

	class XLineFollower {
	public:
		XLineFollower(const XLineFollowerBuilder& builder);

		/**
		 * @returns Whether or not a single line sensor can detect a line according to 
		 * the threshold.
		*/ 
		bool LineDetected();

		/**
		 * If a line is detected on the sensors follow it as best as possible
		 * until the line is no longer detected.
		 *
		 * Note that this is a halting process until the chassis does not
		 * detect the line anymore.
		 *
		 * @param velocity The velocity at which to follow.
		*/
		void FollowLine(unsigned int velocity);

		/**
		 * If a line is detected on the sensors follow it as best as possible
		 * for a certain distance.
		 *
		 * Note that this is a halting process until the chassis reaches the
		 * desired distance.
		 *
		 * @param distance The distance to travel.
		 * @param velocity The velocity at which to follow.
		*/
		void FollowLine(unsigned int distance, unsigned int velocity);

		/** 
		 * Get the recommended threshold value used for line following by
		 * calculating the midpoint between the highest and lowest light
		 * readings.  This assumes that at least one sensor is hitting the line
		 * and at least one is hitting the background; Two sensors can be
		 * outside or inside the line.
		 *
		 * @returns The recommended threshold.
		*/
		std::int32_t RecommendThreshold();

		/**
		 * Stop moving the chassis completely.
		 */ 
		void Stop();

	private:
		std::shared_ptr<AutoXChassis> chassis;
		int lightThreshold;
		bool activeOnDark;

		std::array<std::unique_ptr<inu::LineSensor>, 5> lightSensors;
	};
}



#endif
