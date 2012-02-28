//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef PHYSICS_HPP
#define PHYSICS_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>
 
class PhysicsWrapper 
{
public:
	PhysicsWrapper();
	~PhysicsWrapper();
 
	void initializeWorld();
	void initializeObjects();

	void add_object_to_dynamicWorld(btRigidBody*);

	Ogre::Vector3 getBallPosition();
	void stepPhysics(int, int);

	btDiscreteDynamicsWorld* dynamicsWorld;
 
private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionShape* bottom;
	btCollisionShape* top;
	btCollisionShape* left;
	btCollisionShape* right;
	btCollisionShape* back;
	btCollisionShape* front;
	btCollisionShape* ball;
	btRigidBody* frontRigidBody;
	btRigidBody* backRigidBody;
	btRigidBody* rightRigidBody;
	btRigidBody* leftRigidBody;
	btRigidBody* topRigidBody;
	btRigidBody* bottomRigidBody;
	
};


//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
