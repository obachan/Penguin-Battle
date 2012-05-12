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


Ball* WorldObjectFactory::createNewBall(Penguin* penguin){
	return Ball::createNewBall(mSceneMgr, mPhysics, penguin);
}

Ball* WorldObjectFactory::createNewBall(float px, float py, float pz){
	return Ball::createNewBall(mSceneMgr, mPhysics, Ogre::Vector3(px, py, pz));
}

Icecube* WorldObjectFactory::createNewIcecube(){
	return Icecube::createNewIcecube(mSceneMgr, mPhysics, Ogre::Vector3(0, -95, 0));
}

Icecube* WorldObjectFactory::createNewIcecube(Penguin* penguin){
	return Icecube::createNewIcecube(mSceneMgr, mPhysics, penguin);
}


Igloo* WorldObjectFactory::createNewIgloo(){
	return Igloo::createNewIgloo(mSceneMgr, mPhysics, Ogre::Vector3(40, -room_width/2, 0));
}


Igloo* WorldObjectFactory::createNewIgloo(float px, float py, float pz){
	return Igloo::createNewIgloo(mSceneMgr, mPhysics, Ogre::Vector3(px, py, pz));
}

Room* WorldObjectFactory::createNewRoom(){
	return new Room(mSceneMgr, mPhysics);
}

Penguin* WorldObjectFactory::createNewPenguin(MyController* controller, cCallback* callbackAddBall){
	return Penguin::createNewPenguin(mSceneMgr, mPhysics, controller, callbackAddBall);
}

Penguin* WorldObjectFactory::createNewPenguin(MyController* controller, cCallback* callbackAddBall, cCallback* callbackRightClick){
	return Penguin::createNewPenguin(mSceneMgr, mPhysics, controller, callbackAddBall, callbackRightClick);
}

Goal* WorldObjectFactory::createNewGoal(){
	return new Goal(mSceneMgr, mPhysics);
}

Terrain* WorldObjectFactory::createNewTerrain(){
	return new Terrain(mSceneMgr, mPhysics);
}
