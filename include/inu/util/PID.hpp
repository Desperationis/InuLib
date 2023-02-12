/** PID.hpp
 * @brief General Algorithm to PID anything.
 *
 * General Algorithm to PID anything.
*/

#ifndef INUPID_H
#define INUPID_H

#include "inu/motor/PIDProfile.hpp"
#include "inu/InuException.hpp"
#include <algorithm>
#include "main.h"

namespace inu {
	class PID {
	public:
		/**
		 * @param min Minimum value possible this PID can output.
		 * @param max Maximum value possible this PID can output.
		 * @param profile The PID profile to use.
		*/ 
		PID(double min, double max, const PIDProfile& profile) : profile(profile) {
			SetRange(min, max);
			targetSet = false;
			proportion = 0;
			integral = 0;
			derivative = 0;
			pastError = 0;
			target = 0;
		}

		/**
		 * Sets the target value for this PID to reach.
		 *
		 * @param target Target value
		*/ 
		void SetTarget(double target) {
			this->target = target;
			targetSet = true;
		}

		/**
		 * Sets the range of outputs possible by this PID.
		 *
		 * @param min Minimum value possible this PID can output.
		 * @param max Maximum value possible this PID can output.
		*/ 
		void SetRange(double min, double max) {
			if (min >= max)
				throw inu::InuException("PID.hpp: Minimum cannot be greater than or equal to maximum.");

			this->min = min;
			this->max = max;
		}

		/**
		 * @param profile The PIDProfile of this system.
		*/ 
		void SetPID(const PIDProfile& profile) {
			this->profile = profile;
		}

		/**
		 * @returns The target value.
		*/ 
		double GetTarget() const {
			return target;
		}

		/**
		 * @returns A copy to the PIDProfile used.
		*/ 
		const PIDProfile GetPID() const {
			return profile;
		}

		/**
		 * @returns Whether or not the target has been set.
		*/ 
		bool TargetSet() const {
			return targetSet;
		}

		/**
		 * Whether or not the input value is close to the target by a degree of
		 * error.
		 *
		 * @param input Input value to be checked with target.
		 * @param error The maximum absolute difference between the input and
		 * the target value.
		 *
		 * @returns whether or not the given input is close to the target
		 * within a margin of error.
		 */ 
		bool WithinError(double input, double error) const {
			return input > target - error && input < target + error;
		}

		/**
		 * Updates the PID one time. This assumes that calls to this function
		 * are done in consistent, constant intervals of time.
		 *
		 * The target must be set at least once in order for this to run.
		 *
		 * @param input The input value that changes when given this output.
		*/ 
		double Update(double input) {
			if(!targetSet) 
				throw inu::InuException("PID.hpp: Target must be set.");

			proportion = GetTarget() - input; 
			integral += proportion; 
			derivative = proportion - pastError;
			pastError = proportion;

			if(std::abs(proportion) <= profile.integralLevelingError) {
				integral = 0;
			}

			integral = std::clamp<double>(integral, -profile.integralWindupLimit, profile.integralWindupLimit);

			double p = profile.p;
			double i = profile.i;
			double d = profile.d;

			double output = (proportion * p) + (integral * i) + (derivative * d);
			output = std::clamp(output, min, max);

			return output;
		}

	private:
		PIDProfile profile;
		bool targetSet;
		double target;
		double min, max;
	
		double proportion, integral, derivative;
		double pastError;
	};
}


#endif
