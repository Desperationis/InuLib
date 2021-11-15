/** @file ArmAssemblyBuilder.h
 * @brief Build a ArmAssembly instance.
 *
 * Build a ArmAssembly instance.
*/ 

#ifndef ARMASSEMBLYBUILDER_HPP
#define ARMASSEMBLYBUILDER_HPP


#include "main.h"
#include "pros/adi.hpp"
#include "inu/motor/background/PIDMotor.h"
#include "inu/wrapper/ADIMotor.h"
#include "inu/motor/PIDProfile.hpp"
#include <memory>

namespace inu {
	class ArmAssembly;

	class ArmAssemblyBuilder {
	public:
		ArmAssemblyBuilder();

		void Reset();

		void SetArmMotor(unsigned int port, bool reversed = false);

		void SetClawMotor(unsigned int adiPort, bool reversed = false);

		void SetArmMaximumVelocity(unsigned int velocity);

		void SetArmPIDProfile(PIDProfile profile);

		std::shared_ptr<inu::ADIMotor> GetClawMotor() const;

		std::shared_ptr<inu::PIDMotor> GetArmMotor() const;

		std::shared_ptr<ArmAssembly> Build();

	private:
		unsigned int armMaximumVelocity;
		std::shared_ptr<PIDProfile> pidProfile;
		std::shared_ptr<inu::ADIMotor> clawMotor;
		std::shared_ptr<inu::PIDMotor> armMotor;
	};
}
#endif
