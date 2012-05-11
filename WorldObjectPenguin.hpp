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
	~Penguin();

	btDefaultMotionState* 	penguinMotionState;
	Ogre::Entity* 			penguinEntity;
	Ogre::AnimationState*	mAnimationState;

	void update(double, Ogre::Camera*);
	void updateAsClient(Ogre::Vector3, Ogre::Quaternion, Ogre::Camera*);

	Ogre::Vector3 getPenguinDirection();

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

	void syncPenguin(Ogre::Vector3);		
	void updateCamera(Ogre::Camera*);

	void processController(double, Ogre::Vector3*);
	void handleGravity(double, Ogre::Vector3*);
	void handleCollisions(Ogre::Vector3*);
	void animate(double);
	void fireWeapon();

	void createPenguin(Ogre::SceneManager*); // To Be Deleted
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
