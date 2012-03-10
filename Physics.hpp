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

	void add_object_to_dynamicWorld(btRigidBody*);
	void remove_object_from_dynamicWorld(btRigidBody*);
	void stepPhysics(int, int);

	btDiscreteDynamicsWorld* dynamicsWorld;
 
private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;	
};


//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
