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

class Ball
{
public:
	Ball(Ogre::SceneManager*);
	~Ball();

	btRigidBody* 		ballRigidBody;
	Ogre::SceneNode* 	_objSphereNode;

	Ogre::Vector3 getBallPosition();
	Ogre::Vector3 getBallDirectionVector();
	Ogre::Vector3 getBallUpVector();

	void update(double);

private:

	void createSphere(Ogre::SceneManager*, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::Real, Ogre::String);

	Ogre::Entity* 		_objSphereEntity;
	Ogre::Vector3 		sphere_TranslateVector;

	btCollisionShape* 	ball;
};
