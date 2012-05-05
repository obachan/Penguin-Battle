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

const float ball_radius = 7.0f;
const float ball_mass = 40.0f;

// ==========================
// Parameters for WorldObjectPenguin
// ==========================

const double world_grav = -0.98f;

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

   	virtual void update() = 0;

	void updateAsClient(Ogre::Vector3);			// Called before below methods
   	Ogre::Vector3 getVisualPosition(); 			// Client Safe		
	Ogre::Quaternion getVisualOrientation(); 	// Client Safe

	int getUniqueId();

protected:
	void updateWorldObjectVisual();				// Syncs visuals with Physics
	Ogre::Vector3 getPosition(); 				// Only server objects can call this method
	Ogre::Quaternion getOrientation(); 			// Only server objects can call this method

	btRigidBody* 		worldObjectRigidBody;
	Ogre::SceneNode* 	worldObjectSceneNode;

	int 				worldObject_id; 		// World Object unique ID

private:
	static int 			worldObject_id_counter;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||