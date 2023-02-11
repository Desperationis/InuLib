#include "inu/wrapper/Motor.h"
#include "inu/InuException.hpp"
#include "pros/motors.h"
#include "pros/apix.h"
#include <algorithm>
#include <cstdint>

using namespace inu;
using pros::c::v5_device_e_t::E_DEVICE_MOTOR;

Motor::Motor(inu::port port) : motor(port) {
	if(port < 1 || port > 20)
		throw InuException("Motor.h: Port must be between 1-20.");

	if(pros::c::registry_get_plugged_type(port - 1) != E_DEVICE_MOTOR) {
		char sport[10];
		itoa(port, sport, 10);
		std::string s(sport);
		throw InuException("Motor.h: Port " + s + " is not a motor.");
	}

	tare = 0;
}

int Motor::CapVoltage(int voltage) const {
   return std::clamp<int>(voltage, -127, 127);
}   

int Motor::CapVelocity(int velocity) const {
	pros::motor_gearset_e_t gearing = motor.get_gearing();

	if(gearing == pros::E_MOTOR_GEARSET_36)
		return std::clamp<int>(velocity, -100, 100);

	else if(gearing == pros::E_MOTOR_GEARSET_18)
		return std::clamp<int>(velocity, -200, 200);

	return std::clamp<int>(velocity, -600, 600);
}

void Motor::Move(int voltage) const {
	voltage = CapVoltage(voltage);
	motor.move(voltage);
}

void Motor::MoveRelative(const double position, int velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_relative(position, velocity);
}

void Motor::MoveAbsolute(const double position, int velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_absolute(position + tare, velocity);
}

void Motor::MoveVelocity(int velocity) const {
	velocity = CapVelocity(velocity);
	motor.move_velocity(velocity);
}

void Motor::SetBrakeMode(pros::motor_brake_mode_e_t mode) const {
	motor.set_brake_mode(mode);
}

void Motor::SetCurrentLimit(const int limit) const {
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
	return motor.get_position() + tare;
}

double Motor::GetTargetPosition() const {
	return motor.get_target_position();
}

inu::port Motor::GetPort() const {
	return motor.get_port();
}

void Motor::TarePosition() {
	tare = -motor.get_position();
}

int Motor::GetVoltage() const {
	return (motor.get_voltage() / 12000.0) * 127;
}

int Motor::GetActualVelocity() const {
	return motor.get_actual_velocity();
}

int Motor::GetTargetVelocity() const {
	return motor.get_target_velocity();
}

bool Motor::IsSettled(int error) const {
	double currentPosition = motor.get_position();
	double targetPosition = motor.get_target_position();

	return currentPosition > targetPosition - error &&
		currentPosition < targetPosition + error;
}
