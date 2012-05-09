
#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>
 
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

	float	mouse_x_movement;
	float	mouse_y_movement;

	void 	toggleThirdPersonCamera();
	bool 	thirdPersonCameraOn();
	bool 	debugCameraOn();

private:
	bool 		third_person_camera;
};
