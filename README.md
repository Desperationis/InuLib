# InuLib
This library was meant for use with RobotC, and holds most of the functionality found in its PROS equivalent. It is kept alive for one and one reason only: it can run on the Cortex without a VEXnet controller.

## The Bug
In PROS, programs can ONLY be run if the Cortex has an active VEXnet controller connected. The moment that connection is severed, the program is halted until the controller is connected again. This simple bug is detrimental when controlling the Cortex using serial input, such as when using a PS4 controller, as it means that the superior range of a wifi-bluetooth controller setup compared to VEXnet cannot be utilized unless the VEXnet controller is always kept close to the robot. 

It is because of that bug this project is kept alive. 
