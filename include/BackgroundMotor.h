/** #file BackgroundMotor.h
 * @brief Abstract class for background-powered motors
 *
 * Abstract class for motors that have their speeds changed by background
 * tasks. For this library, PID and Slew are the main examples of this. The
 * background tasks are supposed to take the place of the firmware found on
 * your V5 motor that would normally do a default PID for you.
*/

#ifndef BACKGROUNDMOTOR_H
#define BACKGROUNDMOTOR_H

/**
 * Abstract class for motors that have their internal states updated by 
 * background tasks.
*/ 
class BackgroundMotor {
public:
	BackgroundMotor() = delete;

	virtual ~BackgroundMotor() = default;

	/**
	 * Creates a background motor at a specific port.
	*/ 
	BackgroundMotor(unsigned int port) {
		this->port = port;
	}

	/**
	 * Updates the internal state of the motor. This can range from a lot of
	 * things, but it usually changes the motors speed in relation to a sensor.
	*/ 
	virtual void _Update() = 0;


	/**
	 * @returns The port of this motor.
	*/ 
	virtual unsigned int GetPort() const {
		return port;
	}

protected:
	unsigned int port;
};

#endif
