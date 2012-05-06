//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_PENGUIN_HPP
#define WORLD_OBJECTS_PENGUIN_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectAbstract.hpp"

class Penguin : public WorldObjectAbstract
{
public:


	Penguin(Ogre::SceneManager*, PhysicsWrapper*);
	~Penguin();

	btDefaultMotionState* 	penguinMotionState;
	Ogre::Entity* 			penguinEntity;
	Ogre::AnimationState*	mAnimationState;

	btTransform* 			penguin_position;
	Ogre::Vector3 			penguin_velocity;
	Ogre::Vector3 			penguin_direction;
	Ogre::Vector3 			previous_direction;

	bool 					in_air;

	void update(double, MyController*, Ogre::Camera*);
	void updateCamera(Ogre::Camera*);

	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void update();
private:
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