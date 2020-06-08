# RobotCLibrary
A RobotC custom library meant for use with the VEX Cortex. Meant to integrate basic PID, Slew, and Driver control with any Cortex-Powered Vex Robot.

## Features
### Custom Drivers
This library provides 4 custom drive mode tasks. The max speed, slew rate, and task delay can be adjusted on each of them using global functions.

    /*
     * Arcade control with the left joystick. Supports slewing motors.
    */
    task LeftArcadeControl();


    /*
     * Arcade control with the right joystick. Supports slewing motors.
    */
    task RightArcadeControl();


    /*
     * Tank control with slewing support.
    */
    task CustomTankControl();


    /*
     * Control the chassis like a video game car! Supports slewing motors.
    */
    task GamerControl();

### Slew Controller
A basic slew controller is added into this library. Using an array as a buffer, this slew controller can slew all 10 motor ports attached to the Vex Cortex at the same time without issue.

    /*
     * Initialize slew controller variables. Called by InitCustomLibrary() automatically.
    */
    void InitSlew();


    /*
     * Passively slews motors. Needs to be started to take effect.
    */
    task Slew();


    /*
     * Slew step is the maximum difference in motor value allowed
     * before slewing.
     * This sets the slew step of the slew controller.
     * By default, slew step is set to 0.
     * Slewing affected by SetTaskDelay().
    */
    void SetSlewStep(ubyte step);


    /*
     * Get the slew step of the slew controller.
    */
    ubyte GetSlewStep();


    /*
     * Set the slew value of a motor. This value will be slowly
     * approached by the slew controller if enabled.
    */
    void SetMotorSlew(tMotor port, byte speed);


    /*
     * Allows a motor port to slew. By default, all motors
     * aren't slewed.
    */
    void AllowSlew(tMotor port, bool active);


    /*
     * Returns whether or not a motor is being slewed or not.
    */
    bool CanSlew(tMotor port);

### PID Controller
A specilized PID controller is included in this library. This controller is meant to provide accurate controlling of the chassis for autonomous driving.

    typedef struct {
      float kP;
      float kI;
      float kD;
      short proportion;
      short integral;
      short derivative;
      short pastError;
    } PIDInfo;


    /*
     * Resets PID. Called by InitCustomLibrary() automatically.
    */
    void InitPID();


    /*
     * Sets kP, kI, and kD. Used to tune the PID.
    */
    void SetK(float kP, float kI, float kD);


    /*
     * Passively PID's chassis motors. Needs to be started to take effect.
    */
    task PID();


    /*
     * Calculate the motor speed of a motor given its encoder and information.
    */
    short PIDCalculate(short encoderValue, short target, PIDInfo* info );


    /*
     * Sets the target value of the left and right motors used in PID.
    */
    void SetPIDTarget(MOTOR side, short targetValue);


    /*
     * Allows the chassis to be controlled by PID. Motors and encoders
     * most be defined beforehand in Setup. By default, the chassis
     * aren't controlled by PID.
    */
    void AllowPID(bool active);


    /*
     * Returns whether or not the chassis is being controlled by PID or not.
    */
    bool CanPID();



### RobotCSimulator / RobotCDocs Compatibility
This library is compatible with RobotCSimulator and RobotDocs. You can simulate `main.c` in RobotCSimulator, and make the code more easily accessible with RobotCDocs!
