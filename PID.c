#pragma systemFile
#ifndef PID_SOURCE
#define PID_SOURCE


#ifndef TASK_DELAY
	#define TASK_DELAY 20
#endif

typedef struct {
	float kP;
	float kI;
	float kD;
	short proportion;
	short integral;
	short derivative;
	short past_error;
	short target;
	tMotor motor_port;
	tSensors encoder_port;
	bool encoder_reversed;
	bool active;
} pid_info_t;



/**
 * Array of PIDInfos responsible for retaining
 * PID information.
*/
pid_info_t pid_motor[10];


/**
 * Links a motor to an encoder, therefore allowing it to be controlled by PID;
 * Multiple motors can be connected to a single encoder.  By default, the PID
 * constants kP, kI, and kD are all set to 0.0.
*/
void pid_link(tMotor motor_port, tSensors encoder_port, bool encoder_reversed = false) {
	pid_info_t* info = pid_motor[motor_port];

	info->motor_port = motor_port;
	info->encoder_port = encoder_port;
	info->encoder_reversed = encoder_reversed;
	info->active = true;
}


/**
 * Changes the kP, kI, and kD constants of a LINKED motor.
*/
void pid_set_constants(tMotor motor_port, float kP, float kI, float kD) {
	pid_motor[motor_port].kP = kP;
	pid_motor[motor_port].kI = kI;
	pid_motor[motor_port].kD = kD;
}


/**
 * Set the target value for an encoder from a LINKED motor.
 */
void pid_set_motor(tMotor motor_port, short target) {
	pid_motor[motor_port].target = target;
}


/**
 * Updates PID in a single tick.
*/
short pid_update(pid_info_t* info) {
	short encoderValue = SensorValue[info->encoder_port] * (info->encoder_reversed ? -1 : 1);
	short target = info->target;

	// Calculate motor speed with PID info.
	info->proportion = target - encoderValue;

	info->integral += info->proportion;
	info->derivative = info->proportion - info->past_error;

	info->past_error = info->proportion;

	if(abs(info->proportion) < 5) {
		info->integral = 0;
	}

	if(abs(info->proportion) > 12000) {
		// Needs to be tuned
		//info->integral = 0;
	}

	return motor_clamp((info->proportion * info->kP) + (info->integral * info->kI) + (info->derivative * info->kD));
}


/**
 * Start the PID task. By default, motors are NOT controlled by PID unless
 * explicitly said so. Changes will only take into effect after this starts.
*/
task pid_task() {
	for(short i = 0; i < 10; i++) {
		pid_info_t* info = pid_motor[i];

		info->active = false;
		info->kP = 0;
		info->kI = 0;
		info->kD = 0;
		info->proportion = 0;
		info->integral = 0;
		info->derivative = 0;
		info->past_error = 0;
		info->target = 0;
	}

	while(true) {

		for(int i = 0; i< 10; i++) {
			if(pid_motor[i].active) {
				slew_set_motor(pid_motor[i].motor_port, pid_update(pid_motor[i]));
			}
		}

		delay(TASK_DELAY);
	}
}

#endif
