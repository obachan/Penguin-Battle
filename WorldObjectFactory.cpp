#include "WorldObjectFactory.hpp"

#include <iostream>

WorldObjectFactory::WorldObjectFactory(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics, cCallback* callbackAddBall){
	mSceneMgr = sceneMgr;
	mPhysics = physics;
	mCallbackAddBall = callbackAddBall;
}

WorldObjectFactory::~WorldObjectFactory(){

}

Ball* WorldObjectFactory::createNewBall(){
	return Ball::createNewBall(mSceneMgr, mPhysics, Ogre::Vector3(0, 5, 0));
}


Ball* WorldObjectFactory::createNewBall(Penguin* penguin){
	Ogre::Vector3 penguin_pos = penguin->getVisualPosition();
	Ogre::Vector3 penguin_dir = penguin->getPenguinDirection();

	Ogre::Vector3 ball_start_pos = penguin_pos + 8*penguin_dir;
	//ball_start_pos[1] = ball_start_pos[1] + 10;

	Ball* ball = Ball::createNewBall(mSceneMgr, mPhysics, ball_start_pos, penguin_dir);
	return ball;
}

Ball* WorldObjectFactory::createNewBall(float px, float py, float pz){
	return Ball::createNewBall(mSceneMgr, mPhysics, Ogre::Vector3(px, py, pz));
}

Room* WorldObjectFactory::createNewRoom(){
	return new Room(mSceneMgr, mPhysics);
}

Penguin* WorldObjectFactory::createNewPenguin(){
	return new Penguin(mSceneMgr, mPhysics, mCallbackAddBall);
}


Goal* WorldObjectFactory::createNewGoal(){
	return new Goal(mSceneMgr, mPhysics);
}

Terrain* WorldObjectFactory::createNewTerrain(){
	return new Terrain(mSceneMgr, mPhysics);
}
