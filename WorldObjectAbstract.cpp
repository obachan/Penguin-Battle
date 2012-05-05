#include "WorldObjectAbstract.hpp"

WorldObjectAbstract::WorldObjectAbstract()
{

}

WorldObjectAbstract::~WorldObjectAbstract()
{

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

}

