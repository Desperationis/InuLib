/** @file Vector.hpp
 * @brief Records time elapsed on the cortex.
*/

#ifndef INU_VECTOR_HPP
#define INU_VECTOR_HPP

#include <cmath>


namespace inu {


struct Vector {
	double x = 0;
	double y = 0;

	Vector() {
		this->x = 0;
		this->y = 0;
	}

	Vector(double x, double y) {
		this->x = x;
		this->y = y;
	}

	constexpr double SquareMagnitude() const {
		return (x * x) + (y*y);
	}
	
	double Magnitude() const {
		return std::sqrt(SquareMagnitude());
	}

	double Radians() const {
		return std::atan2(y, x);
	}


	/**
	* Return new Vector such that angle is preserved, but magnitude is 1.
	*/ 
	Vector Normalize() {
		Vector tmp;
		tmp.x = x / Magnitude();
		tmp.y = y / Magnitude();

		return tmp;
	}


	/**
	* @param radians Positive moves counterclockwise.
	*/
	Vector Rotate(double radians) {
		double length = Magnitude();
		double newRad = radians + Radians();

		return FromAngle(newRad, length);
	}


	static Vector FromAngle(double radians, double magnitude) {
		Vector tmp;
		tmp.x = std::cos(radians) * magnitude;
		tmp.y = std::sin(radians) * magnitude;

		return tmp;
	}
};





} // namespace inu

#endif
