/** @file ArmAssemblyBuilder.h
 * @brief Build a ArmAssembly instance.
 *
 * Build a ArmAssembly instance.
*/ 

#ifndef ARMASSEMBLYBUILDER_HPP
#define ARMASSEMBLYBUILDER_HPP


#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "inu/motor/background/PIDMotor.h"
#include "inu/wrapper/Motor.h"
#include "inu/motor/PIDProfile.hpp"
#include "inu/Types.hpp"
#include <memory>

namespace inu {
	class ArmAssembly;

	class ArmAssemblyBuilder {
	public:
		ArmAssemblyBuilder();

		/**
		 * Resets the builder.
		*/ 
		void Reset();

		/**
		 * @param port Port in [1-20]
		 * @param profile PIDProfile that will be used for the arm.
		*/ 
		void SetArmMotor(inu::port port, const PIDProfile& profile);

		/**
		 * @param adiPort Port from [1-20]
		*/ 	
		void SetClawMotor(inu::port port);

		/**
		 * @param port Port from 1-20, 'a'-'z', or 'A'-'Z'.
		*/ 
		void SetButton(inu::port adiPort);

		/**
		 * @param velocity Max velocity of the arm; clamped based on gearing.
		*/ 
		void SetArmMaximumVelocity(std::uint32_t velocity);

		/**
		 * @returns shared_ptr to the claw motor.
		*/ 
		std::shared_ptr<inu::Motor> GetClawMotor() const;

		/**
		 * @returns shared_ptr to the arm motor.
		*/ 
		std::shared_ptr<inu::PIDMotor> GetArmMotor() const;

		/**
		 * @returns shared_ptr to the button.
		*/ 
		std::shared_ptr<pros::ADIButton> GetButton() const;

		/**
		 * @returns shared_ptr to a build ArmAssembly. If something wasn't
		 * configured, InuException will be thrown.
		*/ 
		std::shared_ptr<ArmAssembly> Build();

	private:
		std::shared_ptr<inu::Motor> clawMotor;
		std::shared_ptr<inu::PIDMotor> armMotor;
		std::shared_ptr<pros::ADIButton> button;
	};
}
#endif
