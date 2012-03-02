#include "OgreFramework.hpp"


#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
#include <SdkTrays.h>

#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>

#include <BulletCollision/CollisionShapes/btBox2dShape.h>

const double move_vel = 0.05;

class Ball
{
public:
	Ball(Ogre::SceneManager*);
	~Ball();

	btRigidBody* 		ballRigidBody;
	Ogre::SceneNode* 	_objSphereNode;

	Ogre::Vector3 getBallPosition();
	Ogre::Vector3 getBallDirectionVector();
	Ogre::Vector3 getBallUpVector();

	void update(double);

private:

	void createSphere(Ogre::SceneManager*, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::String);

	Ogre::Entity* 		_objSphereEntity;
	Ogre::Vector3 		sphere_TranslateVector;
	btDefaultMotionState* ballMotionState;

	btCollisionShape* 	ball_collision_shape;
};

class Room
{
public:
	Room(Ogre::SceneManager*);
	~Room();

	btRigidBody* frontRigidBody;
	btRigidBody* backRigidBody;
	btRigidBody* rightRigidBody;
	btRigidBody* leftRigidBody;
	btRigidBody* topRigidBody;
	btRigidBody* bottomRigidBody;

private:

	void createRoom(Ogre::SceneManager*, int, int);

	btCollisionShape* bottom;
	btCollisionShape* top;
	btCollisionShape* left;
	btCollisionShape* right;
	btCollisionShape* back;
	btCollisionShape* front;
};

class Paddle
{
public:

	Paddle(Ogre::SceneManager*);
	~Paddle();

	Ogre::SceneNode *paddleNode;
	btDefaultMotionState* paddleMotionState;
	btRigidBody* paddleRigidBody;

	btTransform* paddle_position;

	void update(double, MyController *);

	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);

	void moveForward(double);
	void moveBackward(double);

	void moveStop();

private:

	void createPaddle(Ogre::SceneManager*);

	btCollisionShape* paddle_collision_shape;
};