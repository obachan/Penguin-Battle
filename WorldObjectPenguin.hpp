//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_PENGUIN_HPP
#define WORLD_OBJECTS_PENGUIN_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectAbstract.hpp"

class Penguin
{
public:


	Penguin(Ogre::SceneManager*, PhysicsWrapper*);
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

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||