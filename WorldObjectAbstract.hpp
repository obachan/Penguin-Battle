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

class WorldObjectAbstract {
public:

	WorldObjectAbstract();
	~WorldObjectAbstract();
   	virtual void update() = 0;

protected:
	void updateWorldObjectVisual(); // Called in the main loop to sync
									// Visuals with the Physics

	btRigidBody* 		worldObjectRigidBody;
	Ogre::SceneNode* 	worldObjectSceneNode;
};
