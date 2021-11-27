#include "inu/motor/background/BackgroundMotorSystem.h"
#include "inu/auto/ArmAssemblyBuilder.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/motor/background/BackgroundMotorSystem.h"
#include "inu/wrapper/ADIMotor.h"
#include "inu/motor/background/PIDMotor.h"
#include "pros/rtos.hpp"

using namespace inu;

ArmAssembly::ArmAssembly(const ArmAssemblyBuilder& builder) {
	claw = builder.GetClawMotor();
	arm = builder.GetArmMotor();
	button = builder.GetButton();
}

void ArmAssembly::MoveArm(int target) {
	arm->Set(arm->GetPosition() + target);
}

void ArmAssembly::Grab() {
	claw->Set(-127);
	pros::delay(800);
	claw->Set(0);
}

void ArmAssembly::Release() {
	claw->Set(127);
	pros::delay(800);
	claw->Set(0);
}

void ArmAssembly::Retract() {
	inu::Motor normalArm(arm->GetPort());
	BackgroundMotorSystem::Instance()->RemoveMotor(arm.get());
	normalArm.MoveVelocity(-90);

	while(button->get_value() != 1) {
		pros::delay(20);
	}

	normalArm.TarePosition();
	arm->Set(arm->GetPosition());
	BackgroundMotorSystem::Instance()->EnrollMotor(arm.get());
}

bool ArmAssembly::AtTarget(int error) {
	return arm->AtTarget(error);
}

double ArmAssembly::GetTarget() const {
	return arm->GetTarget();
}

double ArmAssembly::GetArmPosition() const {
	return arm->GetPosition();
}
