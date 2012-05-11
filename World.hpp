
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_HPP
#define WORLD_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectFactory.hpp"
#include "Callback.h"

class World
{
public:
	World(Ogre::SceneManager*, PhysicsWrapper*);
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

	/* Callback Function */
	TCallback<World> i_callbackAddBall;
	bool CallbackAddBall(void *Param);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
