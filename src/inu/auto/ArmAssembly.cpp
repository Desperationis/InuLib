#include "inu/auto/ArmAssemblyBuilder.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/wrapper/ADIMotor.h"
#include "inu/motor/background/PIDMotor.h"
#include "pros/rtos.hpp"

using namespace inu;

ArmAssembly::ArmAssembly(const ArmAssemblyBuilder& builder) {
	claw = builder.GetClawMotor();
	arm = builder.GetArmMotor();
}

void ArmAssembly::SetArm(int target) {
	arm->Set(target);
}

void ArmAssembly::Grab() {
	claw->Set(-90);
	pros::delay(1000);
	claw->Set(0);
}

void ArmAssembly::Release() {
	claw->Set(90);
	pros::delay(1000);
	claw->Set(0);
}

bool ArmAssembly::AtTarget(int error) {
	return arm->AtTarget(error);
}

double ArmAssembly::GetTarget() const {
	return arm->GetTarget();
}

double ArmAssembly::GetRotation() const {
	return arm->GetPosition();
}
