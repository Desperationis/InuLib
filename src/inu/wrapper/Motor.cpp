#include "inu/wrapper/Motor.h"
#include "pros/motors.h"

using namespace inu;

Motor::Motor(unsigned int port) : motor(port) {
}

void Motor::Move(std::int32_t voltage) const {
	motor.move(voltage);
}

void Motor::MoveRelative(const double position, const std::int32_t velocity) const {
	motor.move_relative(position, velocity);
}

void Motor::MoveAbsolute(const double position, const std::int32_t velocity) const {
	motor.move_absolute(position, velocity);
}

void Motor::SetBrakeMode(pros::motor_brake_mode_e_t mode) const {
	motor.set_brake_mode(mode);
}

void Motor::SetCurrentLimit(const std::int32_t limit) const {
	motor.set_current_limit(limit);
}

void Motor::SetEncoderUnits(pros::motor_encoder_units_e_t units) const {
	motor.set_encoder_units(units);
}

void Motor::SetReversed(bool reversed) const {
	motor.set_reversed(reversed);
}

bool Motor::IsReversed() const {
	return motor.is_reversed();
}

double Motor::GetPosition() const {
	return motor.get_position();
}

std::uint8_t Motor::GetPort() const {
	return motor.get_port();
}

void Motor::TarePosition() const {
	motor.tare_position();
}

std::int32_t Motor::GetValue() const {
	return (motor.get_voltage() / 12000.0) * 127;
}

bool Motor::IsSettled(int error) const {
	double currentPosition = motor.get_position();
	double targetPosition = motor.get_target_position();

	return currentPosition > targetPosition - error &&
		currentPosition < targetPosition + error;
}
