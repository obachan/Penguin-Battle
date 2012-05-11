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
	terrain = worldObjectFactory->createNewTerrain(); 			// Create Terrain
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
	// ball->update(timeSinceLastFrame);
	// ball2->update(timeSinceLastFrame);

	for(int i=0; i<balls.size(); ++i){
		balls[i]->update(timeSinceLastFrame);
	}
}


/* Callback Function */
bool World::CallbackAddBall(void *Param)
{
	balls.push_back(worldObjectFactory->createNewBall(0, 6, 0));
	return true;
}
