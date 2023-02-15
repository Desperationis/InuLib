/** @file VectorMath.hpp
 * @brief Math for Vectors
*/

#ifndef INU_VECTORMATH_HPP
#define INU_VECTORMATH_HPP

#include "main.h"
#include "inu/util/Vector.hpp"
#include "inu/util/MathPoint.h"


namespace inu {

class VectorMath {
public:
	/**
	* Given two vectors A and B defined in a coordinate plane C, transform
	* B such that the new coordinate plane is in terms of A.
	*
	* @return Vector where 0 theta is A. Magnitude of Vector is B. 
	*/
	template<typename T>
	static Vector<T> RelativeVector(Vector<T> a, Vector<T> b) {
		double aRad = a.Radians();
		double bRad = b.Radians();
		double bLength = b.Magnitude();
		double difference = bRad - aRad;

		Vector<MathPoint> vector = FromRad(difference, bLength);

		return vector.ConvertTo<T>();
	}

	static Vector<MathPoint> FromRad(double radians, double magnitude) {
		Vector<MathPoint> tmp;
		tmp.point.x = std::cos(radians) * magnitude;
		tmp.point.y = std::sin(radians) * magnitude;

		return tmp;
	}

	static Vector<MathPoint> FromDegrees(double degrees, double magnitude) {
		double rad = degrees * (M_PI / 180.0);
		return FromRad(rad, magnitude);
	}


	/**
	* Rotate a vector (defined in any coordinate space) by `radians`.
	*
	* @param radians Radians to rotate.
	*/ 
	template<typename T>
	static Vector<T> RotateRad(Vector<T> vector, double radians) {
		// This is why is hate C++
		Vector<MathPoint> converted = vector.template ConvertTo<MathPoint>();

		double newRad = radians + converted.Radians();
		double length = vector.Magnitude();

		Vector<MathPoint> rotated = FromRad(newRad, length);

		return rotated.ConvertTo<T>();
	}

	template<typename T>
	static Vector<T> RotateDegrees(Vector<T> vector, double degrees) {
		double rad = degrees * (M_PI / 180.0);
		return RotateRad(vector, rad);
	}

};





} // namespace inu

#endif
