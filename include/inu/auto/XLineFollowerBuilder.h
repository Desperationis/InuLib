/** @file XLineFollowerBuilder.h
 * @brief Build a XLineFollower instance.
 *
 * Build a XLineFollower instance.
*/ 

#ifndef XLINEFOLLOWERBUILDER_H
#define XLINEFOLLOWERBUILDER_H

#include "main.h"
#include <memory>
#include <array>

namespace inu {
	class AutoXChassis;
	class XLineFollower;

	class XLineFollowerBuilder {
	public:
		XLineFollowerBuilder();

		void Reset();

		void SetChassis(std::weak_ptr<AutoXChassis> chassis);

		// 2 left, 1 center, 2 right
		void SetSensors(const std::array<std::uint8_t, 5>& lightSensors);

		void SetSensorError(const std::array<int, 5>& errors);

		void SetLightThreshold(unsigned int threshold);

		// Whether or not we will detect a reading if the tape is dark (high
		// value). If not, it will activate when the tape is white (low value)
		void ActivateOnDark(bool active);

		std::weak_ptr<AutoXChassis> GetChassis() const;

		const std::array<uint8_t, 5> GetSensors() const;

		const std::array<int, 5> GetSensorErrors() const;

		unsigned int GetLightThreshold() const;

		bool IsActiveOnDark() const;

		std::shared_ptr<XLineFollower> Build();

	private:
		std::weak_ptr<AutoXChassis> chassis;
		std::shared_ptr<XLineFollower> follower;

		std::array<uint8_t, 5> sensors;
		std::array<int, 5> sensorError;
		bool sensorsSet;

		unsigned int lightThreshold;
		bool activeOnDark;
	};
}

#endif
