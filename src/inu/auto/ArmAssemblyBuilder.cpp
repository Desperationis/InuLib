#include "ArmAssemblyBuilder.h"
#include "ArmAssembly.h"
#include "inu/motor/background/PIDMotor.h"
#include "pros/adi.hpp"
#include <memory>

using namespace inu;

ArmAssemblyBuilder::ArmAssemblyBuilder() {
	Reset();
}

void ArmAssemblyBuilder::Reset() {
	armMaximumVelocity = 0;
	clawMotor.reset();
	armMotor.reset();
	pidProfile.reset();
}

void ArmAssemblyBuilder::SetArmMotor(unsigned int port, bool reversed) {
	armMotor.reset(new inu::PIDMotor(port));
	armMotor->SetReversed(reversed);
}

void ArmAssemblyBuilder::SetClawMotor(unsigned int port, bool reversed) {
	clawMotor.reset(new inu::ADIMotor(port));
	clawMotor->SetReversed(reversed);
}

void ArmAssemblyBuilder::SetArmMaximumVelocity(unsigned int velocity) {
	armMotor->SetMaximumVelocity(velocity);
}

void ArmAssemblyBuilder::SetArmPIDProfile(PIDProfile profile) {
	pidProfile.reset(new PIDProfile(profile));
}

std::shared_ptr<inu::ADIMotor> ArmAssemblyBuilder::GetClawMotor() const {
	return clawMotor;
}

std::shared_ptr<inu::PIDMotor> ArmAssemblyBuilder::GetArmMotor() const {
	return armMotor;
}

std::shared_ptr<ArmAssembly> ArmAssemblyBuilder::Build() {
	if(clawMotor == nullptr || armMotor == nullptr || pidProfile == nullptr)
		return nullptr;

	armMotor->SetPID(*pidProfile);

	return std::shared_ptr<ArmAssembly>(new ArmAssembly(*this));
}
