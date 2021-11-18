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
}

void ArmAssemblyBuilder::SetArmMotor(unsigned int port, const PIDProfile& profile) {
	armMotor.reset(new inu::PIDMotor(port, profile));
}

void ArmAssemblyBuilder::SetClawMotor(unsigned int port, bool reversed) {
	clawMotor.reset(new inu::ADIMotor(port));
	clawMotor->SetReversed(reversed);
}

void ArmAssemblyBuilder::SetArmMaximumVelocity(unsigned int velocity) {
	armMotor->SetMaximumVelocity(velocity);
}

std::shared_ptr<inu::ADIMotor> ArmAssemblyBuilder::GetClawMotor() const {
	return clawMotor;
}

std::shared_ptr<inu::PIDMotor> ArmAssemblyBuilder::GetArmMotor() const {
	return armMotor;
}

std::shared_ptr<ArmAssembly> ArmAssemblyBuilder::Build() {
	if(clawMotor == nullptr || armMotor == nullptr)
		return nullptr;

	return std::shared_ptr<ArmAssembly>(new ArmAssembly(*this));
}
