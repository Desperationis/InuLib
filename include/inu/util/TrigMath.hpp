/** @file TrigMath.hpp
 * @brief Trig math
*/

#ifndef INU_TRIGMATH_HPP
#define INU_TRIGMATH_HPP

#include "main.h"


namespace inu {


class TrigMath {
public:
	/**
	 * @param degree Angle to wrap
	 * @return `degree` wrapped to [0, 360)
	 */
	static double Wrap360(double degree) {
		double wrapped = fmod(degree,360);
		if (wrapped < 0)
			wrapped += 360;

		return wrapped;
	}

	/**
	 * @param degree Angle to wrap
	 * @return `degree` wrapped to [-180, 180)
	 */
	static double Wrap180(double degree) {
		double wrapped = fmod(degree + 180,360);
		if (wrapped < 0)
			wrapped += 360;

		return wrapped - 180;
	}

	/**
	 * Returns the most efficient amount of degrees to turn to make current
	 * the same angle as target. Does not wrap. Positive means added
	 * clockwise, negative counterclockwise.
	 *
	 */
	static double EfficientTurn(double current, double target) {
		current = Wrap360(current);
		target = Wrap360(target);

		double counterDist = Wrap360(current - target);
		double clockDist = Wrap360(target - current);

		if (clockDist > counterDist) {
			return -counterDist;
		}

		return clockDist;
	}

};





} // namespace inu

#endif
