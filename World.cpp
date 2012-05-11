#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;

    worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics);	// World Object Factory
	
	ball = worldObjectFactory->createNewBall(); 		// Create Ball
	room = worldObjectFactory->createNewRoom(); 		// Create Room
	penguin =  worldObjectFactory->createNewPenguin(); 	// Create Penguin
	goal = worldObjectFactory->createNewGoal(); 		// Create Goal
	terrain = worldObjectFactory->createNewTerrain(); 	// Create Terrain


	
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


	for(vector<WorldObjectAbstract*>::iterator i = objectList.begin(); i != objectList.end(); ++i) {

		(*i)->update();
	}

	/* Check Events */
	bool scored = false;
	if(ball->inGoal(goal)){
		scored = true;
		ball->reset(mPhysics);
	}
	
}
