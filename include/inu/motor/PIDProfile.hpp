/** @file PIDProfile.hpp
 * @brief Data structure that holds PID profile.
 *
 * Data structure that holds P, I, and D variables for a PIDMotor.
 */

#ifndef PIDPROFILE_H
#define PIDPROFILE_H


namespace inu {
	/**
	 * Data structure that holds P, I, and D variables. This is used in PIDMotor.
	*/ 
	struct PIDProfile {
		float p = 0.0f;
		float i = 0.0f;
		float d = 0.0f;
	};
}



#endif
