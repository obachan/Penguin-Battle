#include "Physics.hpp"

PhysicsWrapper::PhysicsWrapper()
{
	initializeWorld();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
PhysicsWrapper::~PhysicsWrapper()
{ 
        delete dynamicsWorld;
        delete solver;
        delete collisionConfiguration;
        delete dispatcher;
        delete broadphase;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void PhysicsWrapper::initializeWorld()
{
	broadphase = new btDbvtBroadphase();
 
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
        solver = new btSequentialImpulseConstraintSolver;
 
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
 
        dynamicsWorld->setGravity(btVector3(0,-9.8f,0));
}

void PhysicsWrapper::add_object_to_dynamicWorld(btRigidBody* rigid_body){
	dynamicsWorld->addRigidBody(rigid_body);
}

void PhysicsWrapper::stepPhysics(int timestep, int maxsubsteps)
{
	dynamicsWorld->stepSimulation(timestep, maxsubsteps);
}


