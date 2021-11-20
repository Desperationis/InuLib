#include "inu/wrapper/Motor.h"
#include "inu/InuException.hpp"
#include "pros/motors.h"
#include <algorithm>
#include <cstdint>

using namespace inu;

Motor::Motor(inu::port port) : motor(port) {
	if(port < 1 || port > 20)
		throw InuException("Motor.h: Port must be between 1-20.");
}

std::int32_t Motor::CapVoltage(std::int32_t voltage) const {
   return std::clamp<std::int32_t>(voltage, -127, 127);
}   

std::int32_t Motor::CapVelocity(std::int32_t velocity) const {
	pros::motor_gearset_e_t gearing = motor.get_gearing();

	if(gearing == pros::E_MOTOR_GEARSET_36)
		return std::clamp<std::int32_t>(velocity, -100, 100);

	else if(gearing == pros::E_MOTOR_GEARSET_18)
		return std::clamp<std::int32_t>(velocity, -200, 200);

	return std::clamp<std::int32_t>(velocity, -600, 600);
}

void Motor::Move(std::int32_t voltage) const {
	voltage = CapVoltage(voltage);
	motor.move(voltage);
}

void Motor::MoveRelative(const double position, std::int32_t velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_relative(position, velocity);
}

void Motor::MoveAbsolute(const double position, std::int32_t velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_absolute(position, velocity);
}

void Motor::MoveVelocity(std::int32_t velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_velocity(velocity);
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

void Motor::SetReversed(bool reverse) const {
	motor.set_reversed(reverse);
}

bool Motor::IsReversed() const {
	return motor.is_reversed();
}

double Motor::GetPosition() const {
	return motor.get_position();
}

double Motor::GetTargetPosition() const {
	return motor.get_target_position();
}

inu::port Motor::GetPort() const {
	return motor.get_port();
}

void Motor::TarePosition() const {
	motor.tare_position();
}

std::int32_t Motor::GetVoltage() const {
	return (motor.get_voltage() / 12000.0) * 127;
}

std::int32_t Motor::GetActualVelocity() const {
	return motor.get_actual_velocity();
}

std::int32_t Motor::GetTargetVelocity() const {
	return motor.get_target_velocity();
}

bool Motor::IsSettled(int error) const {
	double currentPosition = motor.get_position();
	double targetPosition = motor.get_target_position();

	return currentPosition > targetPosition - error &&
		currentPosition < targetPosition + error;
}
