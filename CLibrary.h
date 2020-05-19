/*
 * CLibrary.h
 *
 * A list of declarations that are defined in CLibrary.c
 *
*/

// Structs
typedef struct {
	int leftMotorPort;
} SetUpInfo;

// Setters
void SetLeftMotor(int port);
void SetRightMotor(int port);
void SetLeftEncoder(int port);
void SetRightEncoder(int port);
void SetControllerSpeed(double speed);
void SetAverageDelay(int delayTime);

// Getters
int GetDelay();

// Functions
int Clamp(int value);

// Tasks
task LeftArcadeControl();
task RightArcadeControl();
task CustomTankControl();
task GamerControl();
void MoveForwardUntil(int encoderValue);
