
#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>
 
class MyController 
{
public:
	MyController();
	~MyController();

	bool		left_control_down;
	bool		right_control_down;

	bool		up_control_down; 
	bool		bottom_control_down;

	bool 		forward_control_down;
	bool 		backward_control_down;

	bool 		jump_control_down;

	bool 		boost_control_down;
};
