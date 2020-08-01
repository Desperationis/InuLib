# RobotCLibrary
This library was meant for use with RobotC, and can be converted with RobotCConverter with no issue. It provides a task-based PID controller, Slew controller, general helper functions, and more.

## Features
### PID Controller
This library's PID controller runs in the background of a program, and is found in `PID.h`. Here is a rundown of its commands:

* `StartPIDTask()` - Runs the PID() task safely by resetting its internal variables. Should be called before anything else.
* `LinkPID(motorPort, encoderPort, encoderReversed = false)` - Links a motor and encoder together to be controlled by the PID. k constants are all equal to 0.
* `SetPIDConstants(motorPort, kP, kI, kD)` - Once linked, the constants of a motor can be defined this way.
* `SetPIDTarget(motorPort, target)` - Set the target encoder value for a motor. By convention, positive values mean the value is forwards.

### Slew Controller
Like all the other tasks defined in this library, this library's slew controller runs in the background of a program, and is found in `Slew.h`. Here is a rundown of its commands:

* `StartSlewTask()` - Runs the Slew() task safely by resetting its internal variables. Should be called before anything else.
* `SetSlewMotor(port, speed)` - Tries to set the target value of a particular slewed motor. If Slew() hasn't started, it will immediantly set motor[] equal to the target.
* `DisableSlew(port)` - By default, all motors are slewed. This can be disabled by using this function at startup.
* `CanSlew(port)` - Returns whether or not a motor can slew.

### Helper Functions
RobotC doesn't seem to include these, so I've implemented them myself in `Helper.h`.

* `Min(a, b)` - Returns the minimum of two values.
* `Max(a, b)` - Returns the maximum of two values.
* `Clamp(value, min, max)` - Constraints a value into a range.
* `MotorClamp(value)` - Constraints a value to the motor's speed limits (-127, 127).
* `Step(original, step, target)` - Linearly interpolated between two values by a maximum amount.
* `HasReached(original, target, range)` - Returns whether or not a value is near a target value by a certain range.

### Chassis Controllers
Due to RobotCLibrary's custom slew controller, some basic chassis controllers needed to be re-implemented in `Controllers.h` to retain slewed motors and be multi-tasked. These tasks control the robot's left and right chassis motors (defined in `Setup.h`), and will break if more than one is run. Here they are:

* `LeftArcadeControl()` - Slewed Arcade Control on the left joystick.
* `RightArcadeControl()` - Slewed Arcade Control on the right joystick.
* `CustomTankControl()` - Slewed tank control.
* `GamerControl()` - Controls the robot like a racecar. Left axis moves the robot up and down while the right axis makes it turn.

## RobotCSimulator Compatible
You can run RobotCConverter on this directory and see the results in RobotCSimulator!
