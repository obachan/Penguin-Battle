//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECT_ABSTRACT_HPP
#define WORLD_OBJECT_ABSTRACT_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "OgreFramework.hpp"


#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
#include <SdkTrays.h>

#include <btBulletDynamicsCommon.h>
#include <OgreVector3.h>

#include <BulletCollision/CollisionShapes/btBox2dShape.h>

#include <cmath>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

// ==========================
// Parameters for WorldObjectRoom
// ==========================

const float room_width = 200.0f; // represents width/height or room
const float room_length = 400.0f; // represents the length of the prism

// ==========================
// Parameters for WorldObjectBall
// ==========================

const float ball_radius = 2.0f;
const float ball_mass = 40.0f;

const float ball_launch_vel = 30.0f;
// ==========================
// Parameters for WorldObjectPenguin
// ==========================

const double world_grav = -0.98f * 1.5;

const double max_fall_vel = -0.5f;
const double move_vel = 1.5f;
const double jump_vel = 7.0f;

const double rotation_speed = 5.0f;
const float penguin_length = 10.0f;

// ==========================
// Parameters for WorldObjectPaddle
// ==========================

const float paddle_length = 10.0f;

class WorldObjectAbstract {
public:

	WorldObjectAbstract();
	~WorldObjectAbstract();
	void initWorldObject(Ogre::SceneManager*, PhysicsWrapper*);


	void updateAsClient(Ogre::Vector3);
	void updateAsClient(Ogre::Vector3, Ogre::Quaternion);			
   	Ogre::Vector3 getVisualPosition(); 			// Client Safe		
	Ogre::Quaternion getVisualOrientation(); 	// Client Safe

	int getUniqueId();

	virtual void update();

protected:
	void resetPosition(Ogre::Vector3);			// Resets the location to the passed in parameter, and velocity is 0
	void resetVelocity(Ogre::Vector3, float);

	void updateWorldObjectVisual();				// Syncs visuals with Physics
	Ogre::Vector3 getRigidBodyPosition(); 		// Only server objects can call this method
	Ogre::Quaternion getRigidBodyOrientation();	// Only server objects can call this method

	virtual void createRigidBody(PhysicsWrapper*) = 0;			// Following protocol will simply our lives.
	virtual void createSceneNode(Ogre::SceneManager*) = 0;		// These calls are made in the WorldObjectAbstract

	Ogre::SceneNode* 	worldObjectSceneNode;
	btRigidBody* 		worldObjectRigidBody;

	int 				worldObject_id; 		// World Object unique ID


	void attachToDynamicWorld(PhysicsWrapper* physics);

private:
	static int 			worldObject_id_counter;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
