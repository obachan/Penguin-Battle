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
	Ball* createNewBall(Penguin* penguin);
	Ball* createNewBall(float, float, float);
	Ball* createNewBallClient();

	Room* createNewRoom();
	Room* createNewRoomClient();

	Penguin* createNewPenguin(MyController*, cCallback*);

	Goal* createNewGoal();
	Goal* createNewGoalClient();

	Terrain* createNewTerrain();

private:
	Ogre::SceneManager*		mSceneMgr;
	PhysicsWrapper*			mPhysics;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||