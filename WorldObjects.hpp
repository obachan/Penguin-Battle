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
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>


const double world_grav = -0.98f;

const float room_width = 200.0f; // represents width/height or room
const float room_length = 400.0f; // represents the length of the prism

const double max_fall_vel = -0.5f;
const double move_vel = 1.5f;
const double jump_vel = 7.0f;

const double rotation_speed = 5.0f;
const float penguin_length = 10.0f;

const float paddle_length = 10.0f;

const float ball_radius = 9.0f;
const float ball_mass = 40.0f;

class Goal
{
public:
	Goal(Ogre::SceneManager*, PhysicsWrapper*, bool do_physics = true);
	~Goal();

	Ogre::SceneNode* 	goalLeftNode;
	Ogre::Entity* 		goalLeftEntity;
	btRigidBody* 		goalLeftBody;

	Ogre::SceneNode* 	goalRightNode;
	Ogre::Entity* 		goalRightEntity;
	btRigidBody* 		goalRightBody;

	Ogre::SceneNode* 	goalBackNode;
	Ogre::Entity* 		goalBackEntity;
	btRigidBody* 		goalBackBody;

	Ogre::SceneNode* 	goalTopNode;
	Ogre::Entity* 		goalTopEntity;
	btRigidBody* 		goalTopBody;

	// The front panel should be open
	Ogre::SceneNode* 	goalFrontNode;
	Ogre::Entity* 		goalFrontEntity;

private:
	void createGoal(Ogre::SceneManager*, double);
	void attachToDynamicWorld(PhysicsWrapper*);

	btCollisionShape* goalLeftShape;
	btCollisionShape* goalRightShape;
	btCollisionShape* goalBackShape;
	btCollisionShape* goalTopShape;

	static int 				scene_node_counter;
};

class Ball
{
public:
	Ball(Ogre::SceneManager*, PhysicsWrapper*, double start_pos_x = 0.0f, double start_pos_y = -(room_width/2) + ball_radius, double start_pos_z = 0.0f, bool do_physics = true);
	~Ball();

	btRigidBody* 		ballRigidBody;
	Ogre::SceneNode* 	objSphereNode;

	Ogre::Vector3 getBallPosition();
	Ogre::Quaternion getBallOrientation();

	void update(double);
	void updateAsClient(Ogre::Vector3);
	bool inGoal(Goal*);
	void reset(PhysicsWrapper*);

private:

	void createSphere(Ogre::SceneManager*, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::String);
	void attachToDynamicWorld(PhysicsWrapper*);

	Ogre::Entity* 			objSphereEntity;
	btDefaultMotionState* 	ballMotionState;
	btCollisionShape* 		ball_collision_shape;

	static int 				scene_node_counter;
};

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

class Penguin
{
public:


	Penguin(Ogre::SceneManager*, PhysicsWrapper*, bool do_physics = true);
	~Penguin();

	Ogre::SceneNode*		penguinNode;
	btDefaultMotionState* 	penguinMotionState;
	btRigidBody* 			penguinRigidBody;
	Ogre::Entity* 			penguinEntity;
	Ogre::AnimationState*	mAnimationState;

	btTransform* 			penguin_position;
	Ogre::Vector3 			penguin_velocity;
	Ogre::Vector3 			penguin_direction;
	Ogre::Vector3 			previous_direction;

	bool 					in_air;

	void update(double, MyController*, Ogre::Camera*);
	void updateAsClient(Ogre::Vector3, Ogre::Quaternion);
	Ogre::Vector3 getPenguinPosition();
	Ogre::Quaternion getPenguinOrientation();
	void updateCamera(Ogre::Camera*);
	void toggleThirdPersonCamera();
private:
	bool 					third_person_camera;
	btCollisionShape* 		penguin_collision_shape;

	void createPenguin(Ogre::SceneManager*);
	void attachToDynamicWorld(PhysicsWrapper*);

	void processController(double, MyController*, Ogre::Vector3*);
	void handleGravity(double, Ogre::Vector3*);
	void handleCollisions(Ogre::Vector3*);
	void animate(double, MyController*);

	static int 				scene_node_counter;
};


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
