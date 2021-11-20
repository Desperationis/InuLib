/** @file AutoChassisBuilder.h
 * @brief Base class for AutoChassis builders
 *
 * Base class for AutoChassisBuilders
*/ 

#ifndef AUTOCHASSISBUILDER_H
#define AUTOCHASSISBUILDER_H

#include "inu/motor/PIDProfile.hpp"
#include "pros/motors.h"
#include "inu/Types.hpp"
#include <cstdint>

namespace inu {
	class AutoChassisBuilder {
	public:
		struct AutoChassisOptions {
			/** 
			 * The steady-state error in encoder value; if the difference
			 * between the actual and target encoder values is below this
			 * value, the chassis is considered to have reached steady-state.
			 *
			 * Note that this value should be slightly higher than the actual
			 * steady state error so that the chassis can align itself a bit
			 * closer whilst exiting a stalling function quicker.
			*/ 
			unsigned int steadyStateEncoderError = 10;

			/**
			 * The maximum velocity the chassis is allowed to go to. The
			 * absolute max is determined by the gearing of the motors and can
			 * go from 100, 200, and 600.  Standard out-of-the-box motors have
			 * a max velocity of 100.
			*/ 
			unsigned int maxVelocity = 100;

			/**
			 * The maximum current that the chassis is allowed to draw in terms
			 * of milliamps. 
			*/ 
			unsigned int currentLimit = 2500;

			/**
			 * The amount of time, in seconds, to wait until the chassis times out
			 * if it doesn't reach steady-state in time.
			*/ 
			double timeoutLimit = 5;

			/**
			 * The amount of time, in seconds, to wait for the chassis to try
			 * to align itself closer to the target value. The timer that uses
			 * this duration will start the moment the chassis determines that
			 * it is close to steady state (as defined by
			 * steadyStateEncoderError). Once that timer ends, the function
			 * will exit.
			 *
			 * Setting this value to 0 will make all the motors of the chassis
			 * stop being powered the moment they reach the target value within
			 * margin of error and most likely overshoot.
			*/ 
			double timeoutAlignLimit = 0;

			/**
			 * Whether or not the methods used to control the chassis will
			 * stall until it reaches steady state error in a reasonable amount
			 * of time. Turning this off would mean that you will have to
			 * timeout the chassis manually.
			 */ 
			bool stalls = true;

			/**
			 * The encoder units used on all motors.
			*/ 
			pros::motor_encoder_units_e_t encoderUnits = pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_COUNTS;
		};

		struct AutoChassisGyroOptions {
			/**
			 * The PIDProfile used when turning with the gyro.
			*/ 
			PIDProfile gyroPID;

			/**
			 * The steady-state error in the angle; if the difference between
			 * the actual and target angle is below this value, the chassis is
			 * considered to have reached steady-state.
			*/ 
			unsigned int steadyStateAngleError = 5;
		};

	public:
		AutoChassisBuilder();

		virtual ~AutoChassisBuilder() = default;

		virtual void Reset();

		/**
		 * OPTIONAL; Set the gyro used by the chassis for turning at a specific
		 * angle.  This will throw a InuException if the port is not within the
		 * specified range.
		 *
		 * @param port Port number between 1-20.
		 * @param gyroOptions Options for the gyro.
		*/ 
		virtual void SetGyro(inu::port port, const AutoChassisGyroOptions& gyroOptions);

		/**
		 * OPTIONAL; Set custom chassis options.
		 *
		 * @param options The custom chassis options.
		*/ 
		virtual void SetChassisOptions(const AutoChassisOptions& options);

		/**
		 * @returns The chassis options used.
		*/ 
		virtual AutoChassisOptions GetChassisOptions() const;

		/**
		 * @returns The gyro options used.
		*/ 
		virtual AutoChassisGyroOptions GetGyroOptions() const;

		/**
		 * @returns The port for the gyro.
		*/ 
		virtual inu::port GetGyroPort() const;

		/**
		 * @returns Whether or not the gyro is used and has been defined.
		*/ 
		virtual bool UsesGyro() const;

	private:
		AutoChassisOptions chassisOptions;

		AutoChassisGyroOptions gyroOptions;
		bool usesGyro;
		inu::port gyroPort;
	};
}


#endif
