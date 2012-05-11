#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;

	worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics);	// World Object Factory

	ball = worldObjectFactory->createNewBall(0, 100, 0); 		// Create Ball
	ball2 = worldObjectFactory->createNewBall(0, 200, 0); 		// Create Ball
	room = worldObjectFactory->createNewRoom(); 				// Create Room
	penguin =  worldObjectFactory->createNewPenguin(); 			// Create Penguin
	goal = worldObjectFactory->createNewGoal(); 				// Create Goal
	terrain = worldObjectFactory->createNewTerrain(); 			// Create Terrain

	balls.push_back(worldObjectFactory->createNewBall(0, 300, 0));
	balls.push_back(worldObjectFactory->createNewBall(0, 400, 0));

	i_CallbackTest.SetCallback(this, &World::CallbackTest);
	penguin->testFireWeapon(&i_CallbackTest);
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

	/* Update World Objects */
	ball->update(timeSinceLastFrame);
	ball2->update(timeSinceLastFrame);

	for(int i=0; i<balls.size(); ++i){
		balls[i]->update(timeSinceLastFrame);
	}
}


/* Callback Function */
bool World::CallbackTest(void *Param)
{
	std::cout << "World::CallbackTest() WORKS" << std::endl;
	std::cout << "World::CallbackTest() WORKS" << std::endl;
	std::cout << "World::CallbackTest() WORKS" << std::endl;
	return true;
}
