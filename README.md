# InuLib
A PROS library for the V5 system specifically tailored to fight against NLMUSD district competitions. 

## File structure
```
    include/inu AND src/inu
    │
    │── auto/ # Files related to autonomous tasks
    │  └──chassis/ # Files related to controlling the chassis autonomously
    │    
    │── background/ # Files related for running background tasks
    │  
    │── motor/ # Files related to motor wrappers
    │  └──background/ # Motors that run in the background
    │    
    └── wrapper/ # Wrappers for PROS classes
```

## Rough Documentation
This is *extremely* rough documentation of the functions available in InuLib. While the example code doesn't compile, it is extremely close to the actual usage if you use the correct keywords.

Not all classes are documented as some are overly simple, or just interfaces. 

### inu/Color.hpp
Color modifiers for text

```cpp
std::cout << FG_RED << "text" << FG_DEFAULT << std::endl;
```

### inu/ControllerCallback.h
Allows you to assign functions as callbacks for controller buttons.

```cpp
auto c = ControllerCallback(MASTER_CONTROLLER_ID);
c.AsyncCallback(BUTTON_ID, function); // Non-halting and non-duplicating
c.SyncCallback(BUTTON_ID, function); // Halting

while(true) {
	c.PollController(); // Checks for controller events
	delay(10);
}
```

### inu/ControllerStream.h
Static methods to print text to the controller. Runs as a background task. It is important to note that this is **extremely buggy and may not work most of the time.**

```cpp
ControllerStream::Start(); // Starts background task
ControllerStream::Print(MASTER_CONTROLLER_ID, "hello, world!");
ControllerStream::Stop(); // Stop task
```

### inu/Logo.hpp
Helper tools to display the hard-coded image in `inu/logo.c` to the screen of the V5.

```cpp
Logo::Draw(); // Draws to the screen
```

### inu/auto/ArmAssembly.h
This is a class to control a specific type of assembly of the robot; An arm mounted on the robot with a claw at the end, and a button that limits the movement of the arm to a certain point. This assembly is meant to collect objects by tipping the arm until it hits the button, and releasing the object.

This is meant for autonomous purposes for precision. Arm is controlled via a PID loop to ensure extremely accurate positioning. This makes it clunky to use manually.

```cpp
ArmAssemblyBuilder builder;
builder.SetArmMotor(1, PIDProfile);
builder.SetClawMotor(2);
builder.SetButton("A"); // ADI Port

ArmAssembly assembly = builder.build();
assembly.Grab(); // Grabs with substantial force
assembly.Retract(); // Pull arm back until it hits the button.
assembly.Release(); // Release the claw
assembly.MoveArm(-200); // Encoder Position
assembly.LightlyGrab() ; // Grabs light enough to not crush a party cup
```


### inu/auto/ColorFollower.h
**Incomplete**

Class that controls an `AutoChassis` to point towards an object detected by a Color Sensor. Can use multiple color sensors in parallel to increase range, but will only point to the largest object detected.

In the sensor with the largest object, the robot turns left or right depending if the object is to the left or the right of the center. The center can be offset by a value. 


```cpp

ColorFollowerBuilder builder;
builder.SetChassis(AutoChassis);
builder.SetOptions(ColorFollowerOptions);
builder.PushSensor(8, 0, 0); // Pushes to a list of sensors
builder.PushSensor(9, -50, 0); 
builder.PushSignature(vision_signature); // Color Signature to detect for all cameras

ColorFollower follower = builder.build();

// Waits until an object is detected, then turns until it is + - 5 in vision
// camera units.
while (true) {
	if (follower.ObjectDetected()) {
		if (!follower.AtTarget(5)) {
			follower.Follow(5);
			break;
		}
	}

	delay(10);
}
```


### inu/auto/XLineFollower.h
Very specialized class for precise line following. It follows a line, whether white on black or black on white, at a certain speed and/or distance. It uses 5 side-to-side line sensors. 

This class also provides line-sensor calibration. During testing, all of our line sensors would read different, consistently spaced values even if placed at the same level reading the same surface. This class provides hard-coded offsets to fix that.

This class also provides a function to calculate the most optimal light level to use as the threshhold between deciding if there is a line or not. 

At the moment, it is implemented using `AutoXChassis`, but none of the striding movement is used, so `AutoChassis` can be used instead.

```cpp
XLineFollowerBuilder builder;
builder.SetChassis(AutoXChassis);
builder.SetSensors(std::array<inu::port, 5>>); // 2 left, 1 center, 2 right
builder.SetSensorError(std::array<int, 5>>); // Offsets
builder.ActivateOnDark(false); // Using white tape on black background
builder.ActivateOnDark(true); // Using black tape on white background
builder.SetLightThreadhold(700);

XLineFollower follower = builder.build();
if (follower.LineDetected()) {
	follower.FollowLine(60); // Follow line at constant speed 60
	follower.FollowLine(1000, 60); // Travel 1000 encoder units at constant speed 60
}

// Debug function to recommend the optimal light threshold. The robot must be
// placed on the line, and at least 1 sensor has to be able to read the floor. 
std::cout << follower.RecommendThreshold() << std::endl;;
```


### inu/auto/chassis/AutoChassis.h
This is an abstract class that is an interface for all robot chassis meant for autonomous purposes. 

All mention of `AutoChassis` refers to an implementation of this class in a specific chassis, whether it be tank drive, swerve drive, kiwi drive, x-drive, mecanum drive, etc. All AutoChassis implementations supports these basic features:
* Move forward and backwards
* Turn left or right while stationary
* Turn left or right while moving forward or back (swerve)
* Move forward and backwards a certain distance
* Turn a certain distance
* Turn relative to a gyroscope, if attached
* Turn absolutely to a gyroscope, if attached
* Stop immediately on command
* Have the ability to completely modify any and all options while running

Each AutoChassis implementation is free to add any other features they wish that is specific to their drive.


```cpp
AutoChassis generic = dynamic_cast<AutoChassis>(AutoChassisImpl);
generic.Rebuild(builder); // Rebuilds the chassis with options
generic.Swerve(100, 10); // (100) forwards and (10) to the right

// Uses only the motor encoders
generic.Turn(1000); 
generic.Forward(100);
generic.Backward(100);
generic.GetDistance(); // Avg. ticks from all motors
generic.TareDistance(); // Set ticks of all motors to 0

// If gyro is attached
generic.TurnA(10); // 10 degrees relative to gyro
generic.TurnAbsolute(10); // 10 degrees absolute from gyro
generic.GetAbsoluteRotation();

// If async enabled from builder, use these to control time
generic.Stop(); // Stop all movement immediately, no matter what
generic.StallUntilSettled(10); // Stall max 10 seconds for motors to get into position
generic.IsSettled(); // Whether motors' encoder positions have reached their position
```




### inu/auto/chassis/AutoXChassis.h
Implementation of `AutoChassis` with an X-drive.

Due to how frequently this class is used, an exception is made to include voltage-based control for manual control.

```cpp
AutoXChassisBuilder builder;
builder.SetChassisOptions(AutoChassisOptions);
builder.SetGryo(port, gyroOptions); // Optional
builder.SetMotors(topleft, topright, bottomleft, bottomright);

AutoXChassis chassis = builder.build();

// Encoder Ticks
chassis.StrafeLeft(1000);
chassis.StrafeRight(1000);
chassis.Swerve(forward, right, turn); // Velocity-based
chassis.RawServe(forward, right, turn); // Voltage-based for manual control
```


### inu/background/BackgroundSystem.h
InuLib's background thread that runs the `BackgroundTask` of all classes that run in the background. 

It is my personal programming style for each class to enroll itself to the BackgroundSystem so that the user doesn't need to manually enroll something when they are going to use it.


```cpp
auto b = BackgroundSystem::Instance();
b.SetDelay(10); // ms to wait between every refresh
b.EnrollTask(task);
// At this point in the code, the task enrolled is running in the background
// automatically every 10ms. 

b.RemoveTask(task);
```


### inu/background/CameraRainbowFlex.h
Asserts dominance over other teams by forcibly cycling RGB colors on a Color Sensor's LED as a `BackgroundTask`. Only possible in PROS.

```cpp
// This is all that is needed. This automatically enrolls itself into the
// background.
CameraRainbowFlex c(port);
```



### inu/motor/background/PIDInertialMotor.h
Controls a motor using a PID loop in combination with an Inertial Sensor (only uses gyro). This is used to turn the robot to an exact angle.

```cpp
PIDInertialMotor motor(1, 2, PIDProfile); // 1 motor, 2 inertial
motor.Set(60); // In degrees
motor.SetMaximumVelocity(40); // While turning

// At this point onwards, the motor is trying to align the robot to 60 degrees
// in the background.

// Wait for motor to be in position
while(!motor.AtTarget(5)) {
	delay(10);
}
```



### inu/motor/background/PIDMotor.h
Controls a motor using a PID loop on the motor's built-in encoders.


```cpp
PIDMotor motor(1, PIDProfile); // 1 motor
motor.Set(600); // In encoder units
motor.SetMaximumVelocity(40); // While turning

// At this point onwards, the motor is trying to reach 600 encoder units in the
// background.

// Wait for motor to be in position
while(!motor.AtTarget(10)) {
	delay(10);
}
```




### inu/motor/background/PIDVisionMotor.h
**Incomplete**

Controls a motor using a PID loop in combination with two Vision Sensors. This is used to align the camera so that the object detected is in center.


```cpp
PIDVisionMotor motor(1, 2, 3); // 1 motor, other two vision sensors
motor.SetPID(PIDprofile);
motor.SetMaximumVelocity(80);
motor.Enable(); // Will start following 
```




### inu/motor/background/SlewMotor.h
Motor that is controlled using a slew algorithm. In summary, this allows you to "ramp" up to a speed and ramp "down" to a speed at a certain rate. The most common use of this motor is to prevent the user from breaking gears by rapidly changing direction.

```cpp
SlewMotor motor(5); // Port
motor.SetRate(5); // Pretty slow ramp up speed
motor.Set(100); // Target speed

// At this point, the motor is speeding up slowly to 100

motor.Set(-100); // Target speed

// At this point, the motor is slowing down to 0, then speeding up to -100
```













