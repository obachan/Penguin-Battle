//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_PENGUIN_HPP
#define WORLD_OBJECTS_PENGUIN_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectAbstract.hpp"
#include "Callback.h"

class Penguin : public WorldObjectAbstract
{
public:


	Penguin(Ogre::SceneManager*, PhysicsWrapper*);
	Penguin(Ogre::SceneManager*, PhysicsWrapper*, cCallback*);
	~Penguin();

	btDefaultMotionState* 	penguinMotionState;
	Ogre::Entity* 			penguinEntity;
	Ogre::AnimationState*	mAnimationState;

	/* Callback */
	cCallback* mCallbackAddBall;

	void update(double, MyController*, Ogre::Camera*);
	void updateCamera(Ogre::Camera*);

	Ogre::Vector3 			getPenguinDirection();


	//don't know how else to fire a snow ball yet...quick dumb hack cuz I'm tired of sitting around thinking about it
	
	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void update(double);

protected:
	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void createSceneNode(Ogre::SceneManager*);
	void createRigidBody(PhysicsWrapper*);	

private:
	btTransform* 			penguin_position;
	Ogre::Vector3 			penguin_velocity;
	Ogre::Vector3 			penguin_direction;
	Ogre::Vector3 			previous_direction;

	btCollisionShape* 		penguin_collision_shape;

	void createPenguin(Ogre::SceneManager*);

	void processController(double, MyController*, Ogre::Vector3*);
	void handleGravity(double, Ogre::Vector3*);
	void handleCollisions(Ogre::Vector3*);
	void animate(double, MyController*);
	void fireWeapon();
	
	static int 				scene_node_counter;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
