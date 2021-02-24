#pragma systemFile
#ifndef PID_SOURCE
#define PID_SOURCE


typedef struct {
	float kP;
	float kI;
	float kD;
	short proportion;
	short integral;
	short derivative;
	short pastError;
	short target;
	tMotor motorPort;
	tSensors encoderPort;
	bool encoderReversed;
	bool active;
} PIDInfo;



/**
 * Array of PIDInfos responsible for retaining
 * PID information.
*/
PIDInfo PIDmotor[10];


/**
 * Links a motor to an encoder, therefore allowing
 * it to be controlled by PID. By default, the PID constants
 * kP, kI, and kD are all set to 0.0 . This can be changed via
 * SetPIDConstants(motorPort, kP, kI, kD).
*/
void LinkPID(tMotor motorPort, tSensors encoderPort, bool encoderReversed = false) {
	PIDInfo& info = PIDmotor[motorPort];

	info.motorPort = motorPort;
	info.encoderPort = encoderPort;
	info.encoderReversed = encoderReversed;
	info.active = true;
}


/**
 * Changes the kP, kI, and kD constants of a motor.
 * Will have no effect if either StartPIDTask() or
 * LinkPID(motorPort, sensorPort, reversed) are not called.
*/
void SetPIDConstants(tMotor motorPort, float kP, float kI, float kD) {
	PIDmotor[motorPort].kP = kP;
	PIDmotor[motorPort].kI = kI;
	PIDmotor[motorPort].kD = kD;
}


/**
 * Set the encoder's target for a motor controlled by
 * PID. Will have no effect if either StartPIDTask() or
 * LinkPID(motorPort, sensorPort, reversed) are not called.
 */
void SetPIDTarget(tMotor motorPort, short target) {
	PIDmotor[motorPort].target = target;
}


/**
 * Given a reference to a PIDInfo, calculate its
 * internal variables and spit out the resulting
 * motor speed.
*/
short PIDCalculate(PIDInfo& info ) {
	short encoderValue = SensorValue[info.encoderPort] * (info.encoderReversed ? -1 : 1);
	short target = info.target;

	// Calculate motor speed with PID info.
	info.proportion = target - encoderValue;

	info.integral += info.proportion;
	info.derivative = info.proportion - info.pastError;

	info.pastError = info.proportion;

	if(abs(info.proportion) < 5) {
		info.integral = 0;
	}

	if(abs(info.proportion) > 12000) {
		// Needs to be tuned
		//info->integral = 0;
	}

	return MotorClamp((info.proportion * info.kP) + (info.integral * info.kI) + (info.derivative * info.kD));
}


/**
 * The task responsible for controlling motors via PID.
 * It is recommended to start this via StartPIDTask().
*/
task PID() {
	while(true) {

		for(int i = 0; i< 10; i++) {
			if(PIDmotor[i].active) {
				slew_set_motor(PIDmotor[i].motorPort, PIDCalculate(PIDmotor[i]));
			}
		}

		delay(TASK_DELAY);
	}
}


/**
 * Starts up the PID() task while resetting internal variables.
 * Motors will not be slewed until an encoder is assigned to it
 * via LinkPID(motorPort, sensorPort, reversed).
*/
void StartPIDTask() {
	for(short i = 0; i < 10; i++) {
		PIDInfo& info = PIDmotor[i];

		info.active = false;
		info.kP = 0;
		info.kI = 0;
		info.kD = 0;
		info.proportion = 0;
		info.integral = 0;
		info.derivative = 0;
		info.pastError = 0;
		info.target = 0;
	}
	startTask(PID);
}

#endif
