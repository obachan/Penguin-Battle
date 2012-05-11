
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_SERVER_HPP
#define WORLD_SERVER_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectFactory.hpp"
#include "Callback.h"

class WorldServer
{
public:
	WorldServer(Ogre::SceneManager*, PhysicsWrapper*);
	~WorldServer();

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
	vector<Penguin*>			 		penguin_clients;

	/* Callback Function */
	TCallback<WorldServer> i_callbackAddBall;
	bool CallbackAddBall(void *Param);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
