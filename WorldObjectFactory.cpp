#include "WorldObjectFactory.hpp"

#include <iostream>



Ball* WorldObjectFactory::createNewBall(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics)
{
	return new Ball(m_pSceneMgr, physics);
}