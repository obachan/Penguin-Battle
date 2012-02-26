#include "Physics.hpp"

btRigidBody* ballRigidBody;
btDiscreteDynamicsWorld* dynamicsWorld;

PhysicsWrapper::PhysicsWrapper()
{
	initializeWorld();
	initializeObjects();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
PhysicsWrapper::~PhysicsWrapper()
{
	dynamicsWorld->removeRigidBody(ballRigidBody);
        delete ballRigidBody->getMotionState();
        delete ballRigidBody;
 
        dynamicsWorld->removeRigidBody(bottomRigidBody);
        delete bottomRigidBody->getMotionState();
        delete bottomRigidBody;
	dynamicsWorld->removeRigidBody(topRigidBody);
        delete topRigidBody->getMotionState();
        delete topRigidBody;
	dynamicsWorld->removeRigidBody(leftRigidBody);
        delete leftRigidBody->getMotionState();
        delete leftRigidBody;
	dynamicsWorld->removeRigidBody(rightRigidBody);
        delete rightRigidBody->getMotionState();
        delete rightRigidBody;
	dynamicsWorld->removeRigidBody(backRigidBody);
        delete backRigidBody->getMotionState();
        delete backRigidBody;
	dynamicsWorld->removeRigidBody(frontRigidBody);
        delete frontRigidBody->getMotionState();
        delete frontRigidBody;
 
 
        delete ball;
 
        delete bottom;
	delete top;
	delete left;
	delete right;
	delete back;
	delete front;
 
 
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
 
void PhysicsWrapper::initializeObjects()
{
	bottom = new btStaticPlaneShape(btVector3(0,1,0),-50);
	top = new btStaticPlaneShape(btVector3(0,-1,0),-50);
	left = new btStaticPlaneShape(btVector3(-1,0,0),-50);
	right = new btStaticPlaneShape(btVector3(1,0,0),-50);
	back = new btStaticPlaneShape(btVector3(0,0,-1),-50);
	front = new btStaticPlaneShape(btVector3(0,0,1),-50);
 
        ball = new btSphereShape(10);
 
 
        btDefaultMotionState* bottomMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        btRigidBody::btRigidBodyConstructionInfo
                bottomRigidBodyCI(0,bottomMotionState,bottom,btVector3(0,0,0));
	bottomRigidBodyCI.m_restitution = 1;
        bottomRigidBody = new btRigidBody(bottomRigidBodyCI);
        dynamicsWorld->addRigidBody(bottomRigidBody);

	btDefaultMotionState* topMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));	
	btRigidBody::btRigidBodyConstructionInfo
                topRigidBodyCI(0,topMotionState,top,btVector3(0,0,0));
	topRigidBody = new btRigidBody(topRigidBodyCI);
        dynamicsWorld->addRigidBody(topRigidBody);

	btDefaultMotionState* leftMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                leftRigidBodyCI(0,leftMotionState,left,btVector3(0,0,0));
	leftRigidBody = new btRigidBody(leftRigidBodyCI);
        dynamicsWorld->addRigidBody(leftRigidBody);

	btDefaultMotionState* rightMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                rightRigidBodyCI(0,rightMotionState,right,btVector3(0,0,0));
	rightRigidBody = new btRigidBody(rightRigidBodyCI);
        dynamicsWorld->addRigidBody(rightRigidBody);

	btDefaultMotionState* backMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                backRigidBodyCI(0,backMotionState,back,btVector3(0,0,0));
	backRigidBody = new btRigidBody(backRigidBodyCI);
        dynamicsWorld->addRigidBody(backRigidBody);

	btDefaultMotionState* frontMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                frontRigidBodyCI(0,frontMotionState,front,btVector3(0,0,0));
	frontRigidBody = new btRigidBody(frontRigidBodyCI);
        dynamicsWorld->addRigidBody(frontRigidBody);
 
        btDefaultMotionState* ballMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(3.5f,10.0f,-25.0f)));
        btScalar mass = 1;
        btVector3 ballInertia(0,0,0);
        ball->calculateLocalInertia(mass,ballInertia);
        btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass,ballMotionState,ball,ballInertia);
	ballRigidBodyCI.m_restitution = 2;
        ballRigidBody = new btRigidBody(ballRigidBodyCI);
        dynamicsWorld->addRigidBody(ballRigidBody);
}

Ogre::Vector3 PhysicsWrapper::getBallPosition()
{
	btTransform trans;
        ballRigidBody->getMotionState()->getWorldTransform(trans);
	return Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

void PhysicsWrapper::stepPhysics(int timestep, int maxsubsteps)
{
	dynamicsWorld->stepSimulation(timestep, maxsubsteps);
}
