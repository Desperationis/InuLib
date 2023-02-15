/** @file Vector.hpp
 * @brief Records time elapsed on the cortex.
*/

#ifndef INU_VECTOR_HPP
#define INU_VECTOR_HPP

#include <cmath>
#include "MathPoint.h"


namespace inu {


template<typename T>
struct Vector {
	T point;

	Vector() : point (0,0) {}

	Vector(double x, double y) : point(x, y) {}

	Vector(T point) : point(point) {}

	constexpr double SquareMagnitude() const {
		double x = point.x;
		double y = point.y;

		return (x * x) + (y * y);
	}
	
	double Magnitude() const {
		return std::sqrt(SquareMagnitude());
	}

	/**
	 * Radians of the Vector, measured from the standard unit circle origin.
	 */
	double Radians() const {
		double x = point.x;
		double y = point.y;

		return std::atan2(y, x);
	}

	/**
	 * Degrees of the Vector, measured from the standard unit circle origin.
	 */
	double Degrees() const {
		return Radians() * (180.0 / M_PI);
	}


	/**
	* Return new Vector such that angle is preserved, but magnitude is 1.
	*/ 
	Vector<T> Normalize() {
		double x = point.x;
		double y = point.y;

		Vector<T> tmp(x / Magnitude(), y / Magnitude());

		return tmp;
	}


	/**
	 * Converts the point of this vector into the point of another.
	 */

	template<typename A>
	Vector<A> ConvertTo() {	
		A newPoint(point);
		Vector<A> converted(newPoint);

		return converted;
	}
};





} // namespace inu

#endif
