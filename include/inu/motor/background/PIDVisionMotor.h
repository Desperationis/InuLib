/** @file PIDVisionMotor.h
 */

#ifndef PIDVISION_MOTOR_H
#define PIDVISION_MOTOR_H

#include "inu/motor/background/BackgroundMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/wrapper/Motor.h"
#include "main.h"
#include "pros/vision.h"
#include <algorithm>
#include <memory>

namespace inu {
	class VisionSensor;

	class PIDVisionMotor : public BackgroundMotor {
	public:
		PIDVisionMotor(unsigned int motorPort, std::shared_ptr<VisionSensor> sensor1, std::shared_ptr<VisionSensor> sensor2);

		virtual ~PIDVisionMotor();
		
		bool AtTarget(unsigned int error) const;

		void Enable(); // On; default off

		void Disable();

		void SetPID(PIDProfile pidProfile);

		void SetReversed(bool reversed);

		void SetMaximumVelocity(unsigned int velocity);

		const PIDProfile GetPID() const;

		bool IsReversed() const;

		void _Update();

	private:
		unsigned int maxVelocity;
		inu::Motor motor;
		std::shared_ptr<VisionSensor> vision1, vision2;

		PIDProfile pidProfile;
		float proportion;
		float integral;
		float derivative;
		float pastError;

		bool enabled;
	};

}


#endif
