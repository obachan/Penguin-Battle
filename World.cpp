#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics, MyController* controller, int numberOfClients)
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
	
	clientNum = numberOfClients;

	for (int i = 0;i<clientNum; i++)
	{
		client_controllers.push_back(new MyController());
    		clientPenguins.push_back(worldObjectFactory->createNewPenguin(client_controllers[i], &i_callbackAddBall));	// Create Player 2's Penguin
		
	}
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
	for (int i = 0;i<clientNum; i++)
	{
		clientPenguins[i]->update(timeSinceLastFrame, client_controllers[i], NULL);
	}

	// /* Update World Objects */
	for(int i=0; i<world_objects.size(); ++i){
		world_objects[i]->update();
	}
}


/* Callback Function */
bool World::CallbackAddBall(void *Param)
{
	Penguin* pen = static_cast<Penguin*>(Param);
	world_objects.push_back(worldObjectFactory->createNewBall(pen));
	return true;
}
