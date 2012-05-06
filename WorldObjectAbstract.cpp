#include "WorldObjectAbstract.hpp"

#include <iostream>

int WorldObjectAbstract::worldObject_id_counter = 0;

WorldObjectAbstract::WorldObjectAbstract()
{
	worldObject_id = worldObject_id_counter;
	worldObject_id_counter++;
	std::cout << worldObject_id << std::endl;
}

WorldObjectAbstract::~WorldObjectAbstract()
{
}

void WorldObjectAbstract::updateAsClient(Ogre::Vector3 pos)
{
	worldObjectSceneNode->setPosition(pos[0], pos[1], pos[2]);
}

void WorldObjectAbstract::updateAsClient(Ogre::Vector3 pos, Ogre::Quaternion rot)
{
	worldObjectSceneNode->setPosition(pos[0], pos[1], pos[2]);
	worldObjectSceneNode->setOrientation(rot[0], rot[1], rot[2], rot[3]);
}


Ogre::Vector3 WorldObjectAbstract::getVisualPosition()
{
	return worldObjectSceneNode->getPosition();
}

Ogre::Quaternion WorldObjectAbstract::getVisualOrientation()
{
	return worldObjectSceneNode->getOrientation();
}

Ogre::Vector3 WorldObjectAbstract::getPosition()
{
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	return Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

Ogre::Quaternion WorldObjectAbstract::getOrientation()
{
	btTransform trans;
	worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	btQuaternion rotation = trans.getRotation();
	return Ogre::Quaternion(float(rotation.w()),
							float(rotation.x()),
							float(rotation.y()),
							float(rotation.z()));
}

void WorldObjectAbstract::updateWorldObjectVisual()
{
	worldObjectSceneNode->setOrientation(getOrientation());
	worldObjectSceneNode->setPosition(getPosition());
}

