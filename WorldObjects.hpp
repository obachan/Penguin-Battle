//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_HPP
#define WORLD_OBJECTS_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectBall.hpp"
#include "WorldObjectGoal.hpp"
#include "WorldObjectPenguin.hpp"

const float paddle_length = 10.0f;

class Room
{
public:
	Room(Ogre::SceneManager*, PhysicsWrapper*, bool do_physics = true);
	~Room();

	btRigidBody* frontRigidBody;
	btRigidBody* backRigidBody;
	btRigidBody* rightRigidBody;
	btRigidBody* leftRigidBody;
	btRigidBody* topRigidBody;
	btRigidBody* bottomRigidBody;

private:

	void createRoom(Ogre::SceneManager*, int, int);
	void attachToDynamicWorld(PhysicsWrapper*);

	btCollisionShape* bottom;
	btCollisionShape* top;
	btCollisionShape* left;
	btCollisionShape* right;
	btCollisionShape* back;
	btCollisionShape* front;
};


class Paddle : public WorldObjectAbstract
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



class Terrain 
{
public:

	Terrain(Ogre::SceneManager*);
	~Terrain();
	
	Ogre::SceneNode* 	terrainNode;
	Ogre::Entity* 		terrainEntity;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||