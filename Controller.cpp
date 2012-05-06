#include "Controller.hpp"

MyController::MyController()
{
	left_control_down = false;
	right_control_down = false;

	up_control_down = false;
	bottom_control_down = false;

	forward_control_down = false;
	backward_control_down = false;

	jump_control_down = false;

	boost_control_down = false;

	mouse_x_movement = 0.0;
	mouse_y_movement = 0.0;

	third_person_camera = true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
MyController::~MyController()
{ 

}
void MyController::toggleThirdPersonCamera()
{
	third_person_camera = !third_person_camera;
}

bool MyController::ThirdPersonCameraOn()
{
	return third_person_camera;
}
