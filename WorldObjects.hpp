//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_HPP
#define WORLD_OBJECTS_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectBall.hpp"
#include "WorldObjectGoal.hpp"

const double world_grav = -0.98f;

const float remove_room_width = 200.0f; // represents width/height or room
const float remove_room_length = 400.0f; // represents the length of the prism

const double max_fall_vel = -0.5f;
const double move_vel = 1.5f;
const double jump_vel = 7.0f;

const double rotation_speed = 5.0f;
const float penguin_length = 10.0f;

const float paddle_length = 10.0f;

const float remove_ball_radius = 10.0f;
const float remove_ball_mass = 40.0f;

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