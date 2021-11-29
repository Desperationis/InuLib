#include "ArmAssemblyBuilder.h"
#include "ArmAssembly.h"
#include "inu/motor/background/PIDMotor.h"
#include "pros/adi.hpp"
#include "inu/InuException.hpp"
#include "pros/motors.h"
#include <cstdint>
#include <memory>

using namespace inu;

ArmAssemblyBuilder::ArmAssemblyBuilder() {
	Reset();
}

void ArmAssemblyBuilder::Reset() {
	clawMotor.reset();
	armMotor.reset();
}

void ArmAssemblyBuilder::SetArmMotor(inu::port port, const PIDProfile& profile) {
	if(port < 0 || port > 20) 
		throw InuException("ArmAssemblyBuilder.h: Arm port must be between 1-20.");

	armMotor.reset(new inu::PIDMotor(port, profile));
	armMotor->SetBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void ArmAssemblyBuilder::SetClawMotor(inu::port port) {
	if(port < 0 || port > 20) 
		throw InuException("ArmAssemblyBuilder.h: Claw port must be between 1-20.");
	clawMotor.reset(new inu::Motor(port));
}

void ArmAssemblyBuilder::SetArmMaximumVelocity(std::uint32_t velocity) {
	armMotor->SetMaximumVelocity(static_cast<int>(velocity));
}

void ArmAssemblyBuilder::SetButton(inu::port port) {
	button.reset(new pros::ADIButton(port));
}

std::shared_ptr<inu::Motor> ArmAssemblyBuilder::GetClawMotor() const {
	return clawMotor;
}

std::shared_ptr<inu::PIDMotor> ArmAssemblyBuilder::GetArmMotor() const {
	return armMotor;
}

std::shared_ptr<pros::ADIButton> ArmAssemblyBuilder::GetButton() const {
	return button;
}

std::shared_ptr<ArmAssembly> ArmAssemblyBuilder::Build() {
	if(clawMotor == nullptr || armMotor == nullptr || button == nullptr)
		throw InuException("ArmAssemblyBuilder.h: Arm, claw, or button wasn't set.");

	return std::shared_ptr<ArmAssembly>(new ArmAssembly(*this));
}
