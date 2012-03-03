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

#include <cmath>

const double world_grav = -0.98f;

const float room_width = 100.0f; // represents width/height or room
const float room_length = 300.0f; // represents the length of the prism

const double max_fall_vel = -0.5f;
const double move_vel = 1.5f;
const double jump_vel = 5.0f;
const float penguin_length = 10.0f;

const float paddle_length = 10.0f;

const float ball_radius = 2.0f;

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

class Penguin
{
public:

	Penguin(Ogre::SceneManager*);
	~Penguin();

	Ogre::SceneNode *penguinNode;
	btDefaultMotionState* penguinMotionState;
	btRigidBody* penguinRigidBody;
	Ogre::Entity* penguinEntity;

	btTransform* penguin_position;

	Ogre::Vector3 penguin_velocity;
	Ogre::AnimationState *mAnimationState;

	void update(double, MyController *);

	bool in_air;
private:

	void createPenguin(Ogre::SceneManager*);

	btCollisionShape* penguin_collision_shape;
};

/*
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
	Ogre::AnimationState *mAnimationState;

	void update(double, MyController *);

	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);

	void moveForward(double);
	void moveBackward(double);

	void moveStop(double);

	bool in_air;
private:

	void createPaddle(Ogre::SceneManager*);

	btCollisionShape* paddle_collision_shape;
};
*/