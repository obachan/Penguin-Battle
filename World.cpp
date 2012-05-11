#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics, MyController* controller)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;
	i_callbackAddBall.SetCallback(this, &World::CallbackAddBall);

	worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics);

	// ball = worldObjectFactory->createNewBall(0, 100, 0);
	// ball2 = worldObjectFactory->createNewBall(0, 200, 0);
	room = worldObjectFactory->createNewRoom();
	penguin =  worldObjectFactory->createNewPenguin(controller, &i_callbackAddBall);
	goal = worldObjectFactory->createNewGoal();
	// terrain = worldObjectFactory->createNewTerrain();

	world_objects.push_back(worldObjectFactory->createNewBall(0, 10, 0));
}

World::~World()
{
	
}

void World::update(double timeSinceLastFrame, MyController* controller, Ogre::Camera* camera)
{
	/* Update Physics Engine */
	if (timeSinceLastFrame!=0){
		mPhysics->stepPhysics(timeSinceLastFrame, 5);
	}

	/* Update Players */
	penguin->update(timeSinceLastFrame, controller, camera);

	// /* Update World Objects */
	for(int i=0; i<world_objects.size(); ++i){
		world_objects[i]->update();
	}
}


/* Callback Function */
bool World::CallbackAddBall(void *Param)
{
	world_objects.push_back(worldObjectFactory->createNewBall(penguin));
	return true;
}
