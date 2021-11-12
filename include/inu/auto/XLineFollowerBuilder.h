/** @file XLineFollowerBuilder.h
 * @brief Build a XLineFollower instance.
 *
 * Build a XLineFollower instance.
*/ 

#ifndef XLINEFOLLOWERBUILDER_H
#define XLINEFOLLOWERBUILDER_H

#include "main.h"

namespace inu {
	class AutoXChassis;
	class XLineFollower;

	class XLineFollowerBuilder {
	public:
		XLineFollowerBuilder();

		void Reset();

		void SetChassis(AutoXChassis* chassis);

		void SetSensors(unsigned int left, unsigned int center, unsigned int right);

		void SetSensorError(int left, int center, int right);

		void SetLightThreshold(unsigned int threshold);

		// Whether or not we will detect a reading if the tape is dark (high
		// value). If not, it will activate when the tape is white (low value)
		void ActivateOnDark(bool active);

		AutoXChassis* GetChassis() const;

		unsigned int GetLeftSensor() const;

		unsigned int GetCenterSensor() const;

		unsigned int GetRightSensor() const;

		int GetLeftSensorError() const;

		int GetCenterSensorError() const;

		int GetRightSensorError() const;

		unsigned int GetLightThreshold() const;

		bool IsActiveOnDark() const;

		XLineFollower* Build();

	private:
		AutoXChassis* chassis;
		XLineFollower* follower;
		
		unsigned int leftPort, centerPort, rightPort;
		int leftError, centerError, rightError;
		bool sensorsSet;

		unsigned int lightThreshold;
		bool activeOnDark;
	};
}

#endif
