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

Ball* WorldObjectFactory::createNewBallClient(){
	return Ball::createNewBall(mSceneMgr, NULL, Ogre::Vector3(0, 0, 0));
}

Room* WorldObjectFactory::createNewRoom(){
	return new Room(mSceneMgr, mPhysics);
}

Room* WorldObjectFactory::createNewRoomClient(){
	return new Room(mSceneMgr, NULL);
}

// Penguin* WorldObjectFactory::createNewPenguin(){
// 	return new Penguin(mSceneMgr, mPhysics, mCallbackAddBall);
// }

Penguin* WorldObjectFactory::createNewPenguin(MyController* controller, cCallback* callbackAddBall){
	return Penguin::createNewPenguin(mSceneMgr, mPhysics, controller, callbackAddBall);
}

Goal* WorldObjectFactory::createNewGoal(){
	return new Goal(mSceneMgr, mPhysics);
}

Goal* WorldObjectFactory::createNewGoalClient(){
	return new Goal(mSceneMgr, NULL);
}

Terrain* WorldObjectFactory::createNewTerrain(){
	return new Terrain(mSceneMgr, mPhysics);
}
