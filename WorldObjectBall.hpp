
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECT_BALL_HPP
#define WORLD_OBJECT_BALL_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"
#include "WorldObjectGoal.hpp"
#include "WorldObjectPenguin.hpp"


class Ball : public WorldObjectAbstract
{
public:
	Ball();
	Ball(Ogre::SceneManager*, PhysicsWrapper*, double start_pos_x = 0.0f, double start_pos_y = -(room_width/2) + ball_radius, double start_pos_z = 0.0f);
	~Ball();

	bool inGoal(Goal*);
	void reset(PhysicsWrapper*);

	static Ball* createNewBall(Ogre::SceneManager*, PhysicsWrapper*, Ogre::Vector3);
	static Ball* createNewBall(Ogre::SceneManager*, PhysicsWrapper*, Penguin*);

protected:
	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void createSceneNode(Ogre::SceneManager*);
	void createRigidBody(PhysicsWrapper*);	

private:

	void createSphere(Ogre::SceneManager*, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real);
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||

