//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_ICECUBE_HPP
#define WORLD_OBJECTS_ICECUBE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"

class Icecube : public WorldObjectAbstract
{
public:
	Icecube();
	~Icecube();

	static Icecube* createNewIcecube(Ogre::SceneManager*, PhysicsWrapper*, Ogre::Vector3);

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
