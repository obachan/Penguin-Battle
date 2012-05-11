#include "World.hpp"

World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;

    worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics);	// World Object Factory

	ball = worldObjectFactory->createNewBall(0, 100, 0); 		// Create Ball
	ball2 = worldObjectFactory->createNewBall(0, 200, 0); 		// Create Ball
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
	ball2->update(timeSinceLastFrame);


	Ogre::Vector3 ball_pos = ball->getVisualPosition();
	Ogre::Vector3 ball2_pos = ball2->getVisualPosition();
	std::cout << ball_pos[0] << " " << ball_pos[1] << " " << ball_pos[2] << "\t\t" << 
				ball2_pos[0] << " " << ball2_pos[1] << " " << ball2_pos[2] << 
				std::endl;

	/* Check Events */
	// bool scored = false;
	// if(ball->inGoal(goal)){
	// 	scored = true;
	// 	ball->reset(mPhysics);
	// }
	
}