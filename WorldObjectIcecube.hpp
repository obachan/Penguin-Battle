//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECTS_ICECUBE_HPP
#define WORLD_OBJECTS_ICECUBE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "WorldObjectAbstract.hpp"
#include "WorldObjectPenguin.hpp"

class Icecube : public WorldObjectAbstract
{
public:
	Icecube();
	~Icecube();

	static Icecube* createNewIcecube(Ogre::SceneManager*, PhysicsWrapper*, Ogre::Vector3);
	static Icecube* createNewIcecube(Ogre::SceneManager*, PhysicsWrapper*, Penguin*);

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
