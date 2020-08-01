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
	short encoderReversed;
	bool active;
} PIDInfo;

PIDInfo PIDmotor[10];

bool canPID;

void InitPID(tMotor motorPort, tSensors encoderPort, short encoderReversed) {

	PIDInfo& info = PIDmotor[motorPort];

	info.kP = 0;
	info.kI = 0;
	info.kD = 0;
	info.proportion = 0;
	info.integral = 0;
	info.derivative = 0;
	info.pastError = 0;
	info.target = 0;
	info.motorPort = motorPort;
	info.encoderPort = encoderPort;
	info.encoderReversed = encoderReversed;
	info.active = true;
}

void SetPIDConstants(tMotor motorPort, float kP, float kI, float kD) {
	PIDmotor[motorPort].kP = kP;
	PIDmotor[motorPort].kI = kI;
	PIDmotor[motorPort].kD = kD;
}

void SetPIDTarget(tMotor motorPort, short target) {
	PIDmotor[motorPort].target = target;
}

short PIDCalculate(PIDInfo& info ) {
	short encoderValue = SensorValue[info.encoderPort] * sgn(info.encoderReversed);
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

task PID() {
	while(true) {

		for(int i = 0; i< 10; i++) {
			if(PIDmotor[i].active) {
				SetSlewMotor(PIDmotor[i].motorPort, PIDCalculate(PIDmotor[i]));
			}
		}

		delay(TASK_DELAY);
	}
}

#endif
