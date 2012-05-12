//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
class MyController 
{
public:
	MyController();
	~MyController();


	bool	left_mouse_button_down;
	bool 	right_mouse_button_down;

	bool	left_control_down;
	bool	right_control_down;

	bool	up_control_down; 
	bool	bottom_control_down;

	bool 	forward_control_down;
	bool 	backward_control_down;

	bool 	jump_control_down;

	bool 	boost_control_down;

	int	mouse_x_movement;
	int	mouse_y_movement;

	void 	toggleThirdPersonCamera();
	bool 	thirdPersonCameraOn();
	bool 	debugCameraOn();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef); 
 
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

private:
	bool 		third_person_camera;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
