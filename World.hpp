
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_HPP
#define WORLD_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectFactory.hpp"
#include "Controller.hpp"

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
	Paddle*								paddle;
	Penguin*							penguin;
	Goal*								goal;
	Terrain*							terrain;

	vector<WorldObjectAbstract*> 		world_objects;
	vector<Penguin*> 		clientPenguins;
	vector<MyController*>		client_controllers;
	int clientNum;

	/* Callback Function */
	TCallback<World> i_callbackAddBall;
	bool CallbackAddBall(void *Param);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
