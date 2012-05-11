#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;
	i_callbackAddBall.SetCallback(this, &World::CallbackAddBall);

	worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics, &i_callbackAddBall);	// World Object Factory

	// ball = worldObjectFactory->createNewBall(0, 100, 0); 		// Create Ball
	// ball2 = worldObjectFactory->createNewBall(0, 200, 0); 		// Create Ball
	room = worldObjectFactory->createNewRoom(); 				// Create Room
	penguin =  worldObjectFactory->createNewPenguin(); 			// Create Penguin
	goal = worldObjectFactory->createNewGoal(); 				// Create Goal
	// terrain = worldObjectFactory->createNewTerrain(); 			// Create Terrain

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
