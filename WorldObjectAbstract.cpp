#include "WorldObjectAbstract.hpp"

#include <iostream>

int WorldObjectAbstract::worldObject_id_counter = 0;

WorldObjectAbstract::WorldObjectAbstract()
{
	// This gives every new WorldObjectAbstract a new ID
	worldObject_id = worldObject_id_counter;
	worldObject_id_counter++;
	std::cout << worldObject_id << std::endl;
}

WorldObjectAbstract::~WorldObjectAbstract()
{

}

// ======================
// Public Methods
// ======================

void WorldObjectAbstract::updateAsClient(Ogre::Vector3 pos, Ogre::Quaternion rot)
{
	worldObjectSceneNode->setPosition(pos[0], pos[1], pos[2]);
	worldObjectSceneNode->setOrientation(rot[0], rot[1], rot[2], rot[3]);
}

void WorldObjectAbstract::updateAsClient(double timeSinceLastFrame, Ogre::Vector3 pos, Ogre::Quaternion rot)
{
	worldObjectSceneNode->setPosition(pos[0], pos[1], pos[2]);
	worldObjectSceneNode->setOrientation(rot[0], rot[1], rot[2], rot[3]);
}

void WorldObjectAbstract::updateAsClient(double timeSinceLastFrame, Ogre::Vector3 pos, Ogre::Quaternion rot, Ogre::Camera*)
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

int WorldObjectAbstract::getUniqueId()
{
	return worldObject_id_counter;
}

// ======================
// Protected Methods
// ======================

void WorldObjectAbstract::resetPosition(Ogre::Vector3 new_pos)
{
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3(new_pos[0], new_pos[1], new_pos[2]));
	worldObjectRigidBody->setLinearVelocity(btVector3(0, 0, 0));

	//----------------------------------
	// Set new position and velocity
	//----------------------------------

	btMotionState *motionState = worldObjectRigidBody->getMotionState();
	motionState->setWorldTransform(trans);
	worldObjectRigidBody->setMotionState (motionState);
}

void WorldObjectAbstract::resetPosition(Ogre::Vector3 new_pos, Ogre::Quaternion new_quat)
{
	std::cout << new_quat[0] << " " << new_quat[1] << " " << new_quat[2] << " " << new_quat[3] << std::endl;

	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3(new_pos[0], new_pos[1], new_pos[2]));
	trans.setRotation(btQuaternion(new_quat[0], new_quat[1], new_quat[2], new_quat[3]));
	worldObjectRigidBody->setLinearVelocity(btVector3(0, 0, 0));

	//----------------------------------
	// Set new position and velocity
	//----------------------------------

	btMotionState *motionState = worldObjectRigidBody->getMotionState();
	motionState->setWorldTransform(trans);
	worldObjectRigidBody->setMotionState (motionState);
}

void WorldObjectAbstract::resetVelocity(Ogre::Vector3 dir, float vel)
{
	worldObjectRigidBody->setLinearVelocity(btVector3(vel * dir[0], vel * dir[1], vel * dir[2]));
}


void WorldObjectAbstract::updateWorldObjectVisual()
{
	worldObjectSceneNode->setOrientation(getRigidBodyOrientation());
	worldObjectSceneNode->setPosition(getRigidBodyPosition());
}

Ogre::Vector3 WorldObjectAbstract::getRigidBodyPosition()
{
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	return Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

Ogre::Quaternion WorldObjectAbstract::getRigidBodyOrientation()
{
	btTransform trans;
	worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	btQuaternion rotation = trans.getRotation();
	return Ogre::Quaternion(float(rotation.w()),
							float(rotation.x()),
							float(rotation.y()),
							float(rotation.z()));
}

// ======================
// Private Methods
// ======================

void WorldObjectAbstract::attachToDynamicWorld(PhysicsWrapper* physics)
{
	physics->add_object_to_dynamicWorld(worldObjectRigidBody);
}

// ========================================
// Abstract methods
// ========================================

void WorldObjectAbstract::update()
{
	updateWorldObjectVisual();
}

void WorldObjectAbstract::initWorldObject(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics)
{
	createRigidBody(physics);	
	createSceneNode(m_pSceneMgr);

	if(physics != NULL)
		attachToDynamicWorld(physics);
}

void WorldObjectAbstract::createRigidBody(PhysicsWrapper* physics)
{
	std::cout << "WorldObjectAbstract::createRigidBody()" << std::endl;
}

void WorldObjectAbstract::createSceneNode(Ogre::SceneManager* m_pSceneMgr)
{
	std::cout << "WorldObjectAbstract::createSceneNode()" << std::endl;
}
