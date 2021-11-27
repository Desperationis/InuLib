/** @file ArmAssembly.h
 * @brief Controls a arm assembly.
 *
 * Controls a arm assembly that allows you to set the position of the arm 
 * and to grab things.
*/ 


#ifndef ARMASSEMBLY_H
#define ARMASSEMBLY_H


#include "main.h"
#include "inu/motor/PIDProfile.hpp"
#include "pros/adi.hpp"
#include <memory>


namespace inu {
	class ArmAssemblyBuilder;
	class PIDMotor;
	class ADIMotor;

	class ArmAssembly {
	public:
		ArmAssembly() = delete;

		ArmAssembly(const ArmAssemblyBuilder& builder);

		/**
		 * Move the arm relative to its position via encoder units.
		 *
		 * @param target Encoder value of the move. 
		*/ 
		void MoveArm(int target);

		/** 
		 * Does the grabbing action with the claw.
		*/ 
		void Grab();

		/**
		 * Tries to release whatever the claw was holding, if anything.
		 */ 
		void Release();

		/**
		 * Whether or not the arm is at the target it was set with plus or
		 * minus `error`.
		 *
		 * @param error The maximum absolute difference between the actual
		 * encoder reading and the target encoder reading.
		 *
		 * @returns whether ot nor the arm is at the target.
		*/ 
		bool AtTarget(int error);

		/**
		 * Stalls until the arm hits the button; Motor position is tared once
		 * the button is pressed.
		*/ 
		void Retract();

		double GetArmPosition() const;

		double GetTarget() const;

	private:
		std::shared_ptr<inu::PIDMotor> arm;
		std::shared_ptr<inu::ADIMotor> claw;
		std::shared_ptr<pros::ADIButton> button;
	};
}



#endif
