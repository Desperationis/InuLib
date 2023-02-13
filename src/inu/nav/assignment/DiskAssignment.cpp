#include "inu/nav/assignment/DiskAssignment.h"
#include "inu/terminal/Color.h"

using namespace inu;


DiskAssignment::DiskAssignment(inu::VisionSensor sensor) : sensor(sensor) {

}

void DiskAssignment::Run() {
	pros::vision_object_s_t arr[5];
	int count = sensor.GetObjectsBySize(3, arr);

	std::cout<<"There are " << Color::FG_RED << count << Color::FG_DEFAULT << " objects detected:" << std::endl;
	for(int i = 0; i < count; i++) {
		std::cout<<"\t";

		auto object = arr[i];
		int x = sensor.GetCenterOffsetX(object);
		int y = sensor.GetCenterOffsetY(object);
		double angle = object.angle / 10.0;

		std::cout << "X: ";
		std::cout << Color::FG_BLUE << x << Color::FG_RED;

		std::cout << " Y: ";
		std::cout << Color::FG_BLUE << y << Color::FG_RED;
		
		std::cout << " Angle: ";
		std::cout << Color::FG_BLUE << angle << Color::FG_RED;

		std::cout<<std::endl;
	}


}
