#include "WorldObjectAbstract.hpp"

class Terrain 
{
public:

	Terrain(Ogre::SceneManager*);
	~Terrain();
	
	Ogre::SceneNode* 	terrainNode;
	Ogre::Entity* 		terrainEntity;
};