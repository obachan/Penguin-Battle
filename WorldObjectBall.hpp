
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECT_BALL_HPP
#define WORLD_OBJECT_BALL_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"
#include "WorldObjectGoal.hpp"


class Ball : public WorldObjectAbstract
{
public:
	Ball(Ogre::SceneManager*, PhysicsWrapper*, double start_pos_x = 0.0f, double start_pos_y = -(room_width/2) + ball_radius, double start_pos_z = 0.0f);
	~Ball();

	void update(double);
	bool inGoal(Goal*);
	void reset(PhysicsWrapper*);

	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void update(); // From abstract class AbstractWorldObject

private:

	void createSphere(Ogre::SceneManager*, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::String);
	void attachToDynamicWorld(PhysicsWrapper*);

	static int 				scene_node_counter;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||

