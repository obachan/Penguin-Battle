//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_ROOM_HPP
#define WORLD_OBJECTS_ROOM_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"

class Room
{
public:
	Room(Ogre::SceneManager*, PhysicsWrapper*);
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

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||