//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_IGLOO_HPP
#define WORLD_OBJECTS_IGLOO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"

class Igloo : public WorldObjectAbstract
{
public:
	Igloo();
	~Igloo();

	static Igloo* createNewIgloo(Ogre::SceneManager*, PhysicsWrapper*, Ogre::Vector3);

protected:
	// ==========================
	// From Parent Class, WorldObjectAbstract
	// ==========================
	void createSceneNode(Ogre::SceneManager*);
	void createRigidBody(PhysicsWrapper*);	
};


//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
