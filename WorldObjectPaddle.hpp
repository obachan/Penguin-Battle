//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_PADDLE_HPP
#define WORLD_OBJECTS_PADDLE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"

class Paddle
{
public:

	Paddle(Ogre::SceneManager*);
	~Paddle();

	Ogre::SceneNode *paddleNode;
	btDefaultMotionState* paddleMotionState;
	btRigidBody* paddleRigidBody;
	Ogre::Entity* paddleEntity;

	btTransform* paddle_position;

	Ogre::Vector3 paddle_velocity;

	void update(double, MyController *);

	bool in_air;
private:

	void createPaddle(Ogre::SceneManager*);

	btCollisionShape* paddle_collision_shape;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
