#ifndef SLEW_HEADER
#define SLEW_HEADER

task Slew();                                                                         // Slew all motors
void SetMotorSlew(tMotor port, byte speed);
void InitSlew();
void AllowSlew(tMotor port);
bool CanSlew(tMotor port);

#endif
