#include "WorldObjectFactory.hpp"

#include <iostream>

WorldObjectFactory::WorldObjectFactory(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics){
	mSceneMgr = sceneMgr;
	mPhysics = physics;
}

WorldObjectFactory::~WorldObjectFactory(){

}

Ball* WorldObjectFactory::createNewBall(){
	return Ball::createNewBall(mSceneMgr, mPhysics, Ogre::Vector3(0, 5, 0));
}

Ball* WorldObjectFactory::createNewBall(float px, float py, float pz){
	return Ball::createNewBall(mSceneMgr, mPhysics, Ogre::Vector3(px, py, pz));
}

Room* WorldObjectFactory::createNewRoom(){
	return new Room(mSceneMgr, mPhysics);
}

Penguin* WorldObjectFactory::createNewPenguin(){
	return new Penguin(mSceneMgr, mPhysics);
}


Goal* WorldObjectFactory::createNewGoal(){
	return new Goal(mSceneMgr, mPhysics);
}

Terrain* WorldObjectFactory::createNewTerrain(){
	return new Terrain(mSceneMgr, mPhysics);
}
