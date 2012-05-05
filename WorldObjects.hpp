//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_HPP
#define WORLD_OBJECTS_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectBall.hpp"
#include "WorldObjectGoal.hpp"
#include "WorldObjectPenguin.hpp"
#include "WorldObjectRoom.hpp"
#include "WorldObjectPaddle.hpp"

class Terrain 
{
public:

	Terrain(Ogre::SceneManager*);
	~Terrain();
	
	Ogre::SceneNode* 	terrainNode;
	Ogre::Entity* 		terrainEntity;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||