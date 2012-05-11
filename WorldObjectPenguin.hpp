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

	vector<WorldObjectAbstract*>* mBalls;
	void registerBallsList(vector<WorldObjectAbstract*>*); // This is here so that penguins can populate the list in world

	//don't know how else to fire a snow ball yet...quick dumb hack cuz I'm tired of sitting around thinking about it
	Ogre::SceneManager* mgr;
	PhysicsWrapper* phyWrap;


	/* Callback */
	void testFireWeapon(cCallback*);



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
