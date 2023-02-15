/** @file PIDProfile.hpp
 * @brief Data structure that holds PID profile.
 *
 * Data structure that holds P, I, and D variables for a PIDMotor.
 */

#ifndef PIDPROFILE_H
#define PIDPROFILE_H


namespace inu {
	/**
	 * Data structure that holds P, I, and D variables used for PID control.
	*/ 
	struct PIDProfile {
		float p;
		float i;
		float d;

		/**
		 * The absolute maximum value a integral can have.
		 */ 
		float integralWindupLimit = 12000;

		/**
		 * If the absolute difference between the target and the input is lower
		 * than or equal to this amount, the integral will be set to 0.
		 */ 
		float integralLevelingError = 0;

		PIDProfile() {
			p = i = d = 0;
		}

		PIDProfile(float p) : p(p), i(0.0), d(0.0) {}
		PIDProfile(float p, float i) : p(p), i(i), d(0.0) {}
		PIDProfile(float p, float i, float d) : p(p), i(i), d(d) {}
	};
}



#endif
