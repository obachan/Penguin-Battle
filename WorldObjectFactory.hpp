//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECT_FACTORY_HPP
#define WORLD_OBJECT_FACTORY_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectBall.hpp"
#include "WorldObjectGoal.hpp"
#include "WorldObjectPenguin.hpp"
#include "WorldObjectRoom.hpp"
#include "WorldObjectPaddle.hpp"
#include "WorldObjectTerrain.hpp"

class WorldObjectFactory {
public:
	WorldObjectFactory(Ogre::SceneManager*, PhysicsWrapper*);
	~WorldObjectFactory();

	Ball* createNewBall();
	Room* createNewRoom();
	Penguin* createNewPenguin();
	Goal* createNewGoal();
	Terrain* createNewTerrain();

private:
	Ogre::SceneManager*		mSceneMgr;
	PhysicsWrapper*			mPhysics;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||