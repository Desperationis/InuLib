/** @file XLineFollower.h
 * @brief Bot for following a line using XAutoChassis.
 *
 * Bot for following a line using line sensors while using the flexibility of
 * XAutoChassis.
*/

#ifndef XLINEFOLLOWER_H
#define XLINEFOLLOWER_H

#include "inu/auto/chassis/AutoXChassis.h"
#include "main.h"

namespace inu {
	class XLineFollower {
	public:
		XLineFollower();
		~XLineFollower();

		// If the line is detected on one of the line sensors,
		// try to make it the center; Blocking with timeout
		void Recenter();

		// Whether or not the line is detected on one of the sensors.
		bool LineDetected();

		// Set the threshold for when a white line is detected on a 
		// dark surface
		void SetLightThreshold(unsigned int threshold);

		// Folows line; non blokcing
		void FollowLine();

		// Stop Following the line completely
		void Stop();

	private:
		unsigned int lightThreshold;


	};
}



#endif
