#include "WorldObjectFactory.hpp"

#include <iostream>

WorldObjectFactory::WorldObjectFactory(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;
}

WorldObjectFactory::~WorldObjectFactory()
{

}

Ball* WorldObjectFactory::createNewBall()
{
	return Ball::createNewBall(mSceneMgr, mPhysics);;
}

Room* WorldObjectFactory::createNewRoom()
{
	return new Room(mSceneMgr, mPhysics);
}

Penguin* WorldObjectFactory::createNewPenguin()
{
	return new Penguin(mSceneMgr, mPhysics);
}


Goal* WorldObjectFactory::createNewGoal()
{
	return new Goal(mSceneMgr, mPhysics);
}

Terrain* WorldObjectFactory::createNewTerrain()
{
	return new Terrain(mSceneMgr, mPhysics);
}