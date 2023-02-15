#include "inu/util/MathPoint.h"
#include "inu/util/FieldPoint.h"

using namespace inu;

MathPoint::MathPoint() {
	this->x = 0;
	this->y = 0;
}

MathPoint::MathPoint(double x, double y) {
	this->x = x;
	this->y = y;
}

MathPoint::MathPoint(FieldPoint point) {
	MathPoint converted = point.toMath();
	x = converted.x;
	y = converted.y;
}

FieldPoint MathPoint::toField() {
	// Math frame is rotated 90 degrees clockwise, so this rotates it
	// back.
	return FieldPoint(-x, y);
}
