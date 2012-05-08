#include "WorldObjectAbstract.hpp"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

class Terrain 
{
public:

	Terrain(Ogre::SceneManager*,PhysicsWrapper* physics);
	~Terrain();
	
	Ogre::SceneNode* 	terrainNode;
	Ogre::Entity* 		terrainEntity;

	btHeightfieldTerrainShape* terrainShape;
	float heightdata [256*256];
	btRigidBody*		terrainRigidBody;
	void attachToDynamicWorld(PhysicsWrapper* physics);
};
