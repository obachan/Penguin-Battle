#include "Controller.hpp"

MyController::MyController()
{
	left_mouse_button_down = false;
	right_mouse_button_down = false;

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

bool MyController::thirdPersonCameraOn()
{
	return third_person_camera;
}

bool MyController::debugCameraOn()
{
	return !third_person_camera;
}

bool MyController::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	// Key Presses to Modify Controller
	//if(keyEventRef.key == OIS::KC_A)			left_control_down =true;
	if(keyEventRef.key == OIS::KC_LEFT)			left_control_down = true;
	//if(keyEventRef.key == OIS::KC_D)		right_control_down = true;
	if(keyEventRef.key == OIS::KC_RIGHT)		right_control_down = true;
	if(keyEventRef.key == OIS::KC_W)			forward_control_down = true;
	if(keyEventRef.key == OIS::KC_UP)			forward_control_down = true;
	if(keyEventRef.key == OIS::KC_S)			backward_control_down = true;
	if(keyEventRef.key == OIS::KC_DOWN)			backward_control_down = true;
	if(keyEventRef.key == OIS::KC_P)			up_control_down = true;
	if(keyEventRef.key == OIS::KC_SEMICOLON)	bottom_control_down = true;
	if(keyEventRef.key == OIS::KC_SPACE)		jump_control_down = true;
	if(keyEventRef.key == OIS::KC_Z)			boost_control_down = true;
	if(keyEventRef.key == OIS::KC_Q)			toggleThirdPersonCamera();

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool MyController::keyReleased(const OIS::KeyEvent &keyEventRef){
	// Key Presses to Modify Controller
	if(keyEventRef.key == OIS::KC_LEFT)			left_control_down = false;
	if(keyEventRef.key == OIS::KC_RIGHT)		right_control_down = false;
	if(keyEventRef.key == OIS::KC_W)			forward_control_down = false;	
	if(keyEventRef.key == OIS::KC_UP)			forward_control_down = false;
	if(keyEventRef.key == OIS::KC_S)			backward_control_down = false;	
	if(keyEventRef.key == OIS::KC_DOWN)			backward_control_down = false;	
	if(keyEventRef.key == OIS::KC_P)			up_control_down = false;
	if(keyEventRef.key == OIS::KC_SEMICOLON)	bottom_control_down = false;
	if(keyEventRef.key == OIS::KC_Z)			boost_control_down = false;
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool MyController::mouseMoved(const OIS::MouseEvent &evt)
{
	// Controller holds the last mouse position
	mouse_x_movement = -evt.state.X.rel;
	mouse_y_movement = -evt.state.Y.rel;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool MyController::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

	if(id == OIS::MB_Left) 	left_mouse_button_down = true;
	if(id == OIS::MB_Right) right_mouse_button_down = true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool MyController::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left) 	left_mouse_button_down = false;
	if(id == OIS::MB_Right) right_mouse_button_down = false;
    return true;
}

