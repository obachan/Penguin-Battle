//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_PENGUIN_HPP
#define WORLD_OBJECTS_PENGUIN_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectAbstract.hpp"
#include "Controller.hpp"

#include "Callback.h"

class Penguin : public WorldObjectAbstract
{
public:

	Penguin(MyController*, cCallback*);

	Penguin(Ogre::SceneManager*, PhysicsWrapper*, MyController*);				// To be deleted
	Penguin(Ogre::SceneManager*, PhysicsWrapper*);				// To be deleted
	~Penguin();

	btDefaultMotionState* 	penguinMotionState;
	Ogre::Entity* 			penguinEntity;
	Ogre::AnimationState*	mAnimationState;

	void update(double, MyController*, Ogre::Camera*);
	void updateCamera(Ogre::Camera*);

	Ogre::Vector3 			getPenguinDirection();


	static Penguin* createNewPenguin(Ogre::SceneManager*, PhysicsWrapper*, MyController*, cCallback*);
protected:
	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void createSceneNode(Ogre::SceneManager*);
	void createRigidBody(PhysicsWrapper*);	

private:
	MyController*			mController;
	cCallback* 				mCallbackAddBall;

	btTransform* 			penguin_position;
	Ogre::Vector3 			penguin_velocity;
	Ogre::Vector3 			penguin_direction;
	Ogre::Vector3 			previous_direction;

	btCollisionShape* 		penguin_collision_shape;

	void createPenguin(Ogre::SceneManager*);

	void processController(double, Ogre::Vector3*);
	void handleGravity(double, Ogre::Vector3*);
	void handleCollisions(Ogre::Vector3*);
	void animate(double);
	void fireWeapon();
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
