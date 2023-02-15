#include "inu/util/FieldPoint.h"
#include "inu/util/MathPoint.h"

using namespace inu;


FieldPoint::FieldPoint() {
	this->x = 0;
	this->y = 0;
}

FieldPoint::FieldPoint(double x, double y) {
	this->x = x;
	this->y = y;
}

FieldPoint::FieldPoint(MathPoint point) {
	FieldPoint converted = point.toField();
	x = converted.x;
	y = converted.y;
}

MathPoint FieldPoint::toMath() {
	// Field is rotated 90 degrees counterclockwise, so this rotates it
	// back.

	return MathPoint(y, -x);
}
