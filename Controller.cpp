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
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
MyController::~MyController()
{ 

}
 