#include "inu/motor/Motor.h"

using namespace inu;

Motor::Motor(unsigned int port) : pros::Motor(port) {

}

bool Motor::IsSettled(unsigned int error) const {
	double currentPosition = get_position();
	double targetPosition = get_target_position();

	return currentPosition > targetPosition - error &&
		currentPosition < targetPosition + error;
}

Motor* Motor::Clone() const {
	return new Motor(*this);
}
