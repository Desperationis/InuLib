#include "inu/background/BackgroundSystem.h"
#include "inu/auto/ArmAssemblyBuilder.h"
#include "inu/auto/ArmAssembly.h"
#include "inu/wrapper/ADIMotor.h"
#include "inu/motor/background/PIDMotor.h"
#include "inu/wrapper/Motor.h"
#include "pros/motors.h"
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
	claw->MoveVelocity(-100);
	pros::delay(800);
	claw->Move(0);
	claw->MoveVelocity(-20);
}

void ArmAssembly::LightlyGrab() {
	claw->MoveVelocity(-60);
	pros::delay(600);
	claw->Move(-20);
}

void ArmAssembly::Release() {
	claw->MoveVelocity(100);
	pros::delay(800);
	claw->Move(0);
}

void ArmAssembly::Retract() {
	inu::Motor normalArm(arm->GetPort());
	BackgroundSystem::Instance()->RemoveTask(arm.get());
	normalArm.MoveVelocity(-90);

	while(button->get_value() != 1) {
		pros::delay(20);
	}

	normalArm.TarePosition();
	arm->Set(arm->GetPosition());
	BackgroundSystem::Instance()->EnrollTask(arm.get());
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
