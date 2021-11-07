/** @file AutoChassis.h
 * @brief Class for moving a chassis autonomously.
 *
 * Abstract class used to move a chassis autonomously.
*/

#ifndef CHASSIS_H
#define CHASSIS_H

#include <cstdint>

namespace inu {
	/**
	 * Abstract class used for all future chassis that move autonomously.
	*/
	class AutoChassis {
	protected:
		AutoChassis() {
			maxError = 10;
			maxVelocity = 127;
		}

	public:
		virtual void TurnA(double degrees) = 0;

		virtual void Turn(double ticks) = 0;

		virtual void Forward(double ticks) = 0;

		virtual void Backward(double ticks) = 0;

		virtual bool IsSettled() = 0;

		virtual void SetMaxVelocity(std::int32_t velocity) {
			maxVelocity = velocity;
		}

		virtual void SetMaxError(std::int32_t error) {
			maxError = error;
		}	


	protected:
		std::int32_t maxVelocity, maxError;
	};
}


#endif
