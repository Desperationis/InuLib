/** @file XLineFollower.h
 * @brief Bot for following a line using XAutoChassis.
 *
 * Bot for following a line using line sensors while using the flexibility of
 * XAutoChassis.
*/

#ifndef XLINEFOLLOWER_H
#define XLINEFOLLOWER_H

#include "main.h"
#include "inu/auto/LineSensor.h"
#include <memory>

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
		 * If a line is detected on the sensors follow it as best as possible.
		 * Note that this is a halting process until the chassis does not
		 * detect the line anymore, in which case it stops.
		*/
		void FollowLine();

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
		unsigned int lightThreshold;
		bool activeOnDark;

		inu::LineSensor left, center, right;
	};
}



#endif
