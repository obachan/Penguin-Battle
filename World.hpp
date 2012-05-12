
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
	World(Ogre::SceneManager*, PhysicsWrapper*, MyController*, int);
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
	Icecube*							icecube;
	Penguin*							penguin;
	Goal*								goal;
	Terrain*							terrain;

	Ogre::ParticleSystem* pSys4;
	Ogre::SceneNode* rNode;

	vector<WorldObjectAbstract*> 		world_objects;
	vector<Penguin*> 		clientPenguins;
	vector<MyController*>		client_controllers;
	int clientNum;

	/* Callback Function */
	TCallback<World> i_callbackAddBall;
	bool CallbackAddBall(void *Param);

	TCallback<World> i_callbackRightClick;
	bool CallbackRightClick(void *Param);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
