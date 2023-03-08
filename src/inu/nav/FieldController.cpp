#include "inu/nav/FieldController.h"
#include "inu/util/PID.hpp"
#include "inu/util/PIDProfile.hpp"
#include "inu/util/TrigMath.hpp"
#include "inu/util/VectorMath.hpp"
#include "inu/util/FieldPoint.h"
#include "inu/util/MathPoint.h"

#include "inu/terminal/Color.h"
#include "inu/util/Stopwatch.hpp"
#include "inu/util/Vector.hpp"

using namespace inu;

FieldController::FieldController(std::shared_ptr<inu::XChassis> chassis, inu::GPS gps) : gps(gps) {

	this->chassis = chassis;
}


void FieldController::LookAt(double x, double y) {
	auto info = gps.GetInfo();

	// Make a vector that points towards the target in field
	// coordinates. Then convert to math coordinates for later.
	double diffX = x - info.x;
	double diffY = y - info.y;
	auto diffVector = Vector<FieldPoint>(diffX, diffY).ConvertTo<MathPoint>();

	// Calculate the relative amount of degrees the robot needs to
	// turn to face towards the point. `degrees` is negative of
	// `diffVector` degrees as the field's coordinate system
	// increases angle the opposite direction than the math
	// coordinate field.
	double degrees = -diffVector.Degrees();

	TurnTo(degrees);
}

void FieldController::TurnTo(double degrees) {
	bool inZone = false;
	Stopwatch zoneTimer;
	zoneTimer.Mark();
	Stopwatch timeoutTimer;
	timeoutTimer.Mark();

	while(timeoutTimer.GetElapsed() < 5000) {
		double heading = gps.GetHeading();
		auto info = gps.GetInfo();

		double vol = CalcTurnVol(degrees, PIDProfile(2.0, 0.5));
		chassis->RawSwerve(0, 0, vol);

		// Break loop if chassis in zone for a duration of time
		double currHeading = TrigMath::Wrap180(gps.GetHeading());
		if (fabs(TrigMath::EfficientTurn(currHeading, degrees)) < 5) {
			if (!inZone) {
				inZone = true;
				zoneTimer.Mark();
			}
			else if (inZone && zoneTimer.GetElapsed() > 1000) {
				break;
			}
		}
		else {
			inZone = false;
		}


		pros::delay(20);
	}

}


void FieldController::LinearTo(double x, double y, bool align) {
	Stopwatch timeoutTimer;
	timeoutTimer.Mark();
	while(timeoutTimer.GetElapsed() < 5000) {
		double heading = gps.GetHeading();
		auto info = gps.GetInfo();

		// Create unit vector representing robot orientation in the math
		// coordinate plane. `heading` is negative as field's direction
		// of angle is opposite that of the math coordinate plane.
		Vector<MathPoint> robotVector = VectorMath::FromDegrees(-heading, 1);

		// Create vector that points to the direction the robot should
		// go in the global math plane.
		double diffX = x - info.x;
		double diffY = y - info.y;
		auto diffVector = Vector<FieldPoint>(diffX, diffY).ConvertTo<MathPoint>();

		// Calculate turn voltage in real-time. It is important that
		// `diffVector` is in the MathPoint state, as otherwise
		// `Degrees` wouldn't return the accurate result.
		double vol = 0;
		double mag = diffVector.Magnitude() * 127;
		if(align) {
			vol = CalcTurnVol(-diffVector.Degrees(), PIDProfile(1.0));
			mag -= vol;
		}

		chassis->VectorPush(mag, vol, robotVector, diffVector);

		// Break if somewhere near the goal
		if(std::fabs(diffX) < 0.2 && std::fabs(diffY) < 0.2)
			break;

		pros::delay(20);

	}

	chassis->Stop();
}

double FieldController::CalcTurnVol(double heading, PIDProfile profile) {
	PID pid(-127, 127, profile);
	heading = TrigMath::Wrap180(heading);
	double currHeading = TrigMath::Wrap180(gps.GetHeading());
	pid.SetTarget(0);
	
	return pid.Update(-TrigMath::EfficientTurn(currHeading, heading));	
}


std::ostream& inu::operator<<(std::ostream& os, const inu::FieldController& fc) {

	double heading = fc.gps.GetHeading();
	auto info = fc.gps.GetInfo();

	os << "Robot is at X: ";
	os << info.x;
	os << " Y: ";
	os << info.y;
	os << " with heading of ";
	os << heading;
	os << " degrees";

	return os;
}
