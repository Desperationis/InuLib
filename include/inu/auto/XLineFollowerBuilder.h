/** @file XLineFollowerBuilder.h
 * @brief Build a XLineFollower instance.
 *
 * Build a XLineFollower instance.
*/ 

#ifndef XLINEFOLLOWERBUILDER_H
#define XLINEFOLLOWERBUILDER_H

#include "main.h"
#include "inu/auto/XLineFollower.h"

namespace inu {
	class AutoXChassis;
	class XLineFollower;

	class XLineFollowerBuilder {
	public:
		XLineFollowerBuilder() { 
			Reset();
		}

		void Reset() {
			sensorsSet = false;
			activeOnDark = false;

			lightThreshold = 1000;
			chassis = nullptr;
			follower = nullptr;

			leftError = 0;
			centerError = 0;
			rightError = 0;
		}

		void SetChassis(AutoXChassis* chassis) {
			this->chassis = chassis;
		}

		void SetSensors(unsigned int left, unsigned int center, unsigned int right) {
			leftPort = left;
			centerPort = center;
			rightPort = right;
			sensorsSet = true;
		}

		void SetSensorError(int left, int center, int right) {
			leftError = left;
			centerError = center;
			rightError = right;
		}

		void SetLightThreshold(unsigned int threshold) {
			lightThreshold = threshold;
		}

		// Whether or not we will detect a reading if the tape is dark (high
		// value). If not, it will activate when the tape is white (low value)
		void ActivateOnDark(bool active) {
			activeOnDark = active;
		}

		AutoXChassis* GetChassis() const {
			return chassis;
		}

		unsigned int GetLeftSensor() const {
			return leftPort;
		}

		unsigned int GetCenterSensor() const {
			return centerPort;
		}

		unsigned int GetRightSensor() const {
			return rightPort;
		}

		int GetLeftSensorError() const {
			return leftError;
		}

		int GetCenterSensorError() const {
			return centerError;
		}

		int GetRightSensorError() const {
			return rightError;
		}

		unsigned int GetLightThreshold() const {
			return lightThreshold;
		}

		bool IsActiveOnDark() const {
			return activeOnDark;
		}

		XLineFollower* Build() {
			if(!sensorsSet) 
				return nullptr;

			return new XLineFollower(this);
		}


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
