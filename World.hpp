
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_HPP
#define WORLD_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectFactory.hpp"
#include "Controller.hpp"
#include "OgreBillboardParticleRenderer.h"

#include "Callback.h"

class World
{
public:
	World(Ogre::SceneManager*, PhysicsWrapper*, MyController*);
	~World();

	void update(double, MyController*, Ogre::Camera*);

	Ogre::SceneManager*		mSceneMgr;
	PhysicsWrapper*			mPhysics;

	// ===============================
	// World Object
	// ===============================

	WorldObjectFactory* 				worldObjectFactory;

	Ball*								ball;
	Ball*								ball2;
	Room*								room;
	Paddle*								paddle;
	Penguin*							penguin;
	Goal*								goal;
	Terrain*							terrain;

	Ogre::ParticleSystem* pSys4;
	Ogre::SceneNode* rNode;

	vector<WorldObjectAbstract*> 		world_objects;

	/* Callback Function */
	TCallback<World> i_callbackAddBall;
	bool CallbackAddBall(void *Param);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
