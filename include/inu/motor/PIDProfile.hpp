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

		PIDProfile() {
			p = i = d = 0;
		}

		PIDProfile(float p) : p(p) {}
		PIDProfile(float p, float i) : p(p), i(i) {}
		PIDProfile(float p, float i, float d) : p(p), i(i), d(d) {}
	};
}



#endif
