#include "OgreDemo.hpp"

DemoApp::DemoApp()
{
	m_pOgreHeadNode		= 0;
	m_pOgreHeadEntity		= 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
DemoApp::~DemoApp()
{
       delete OgreFramework::getSingletonPtr();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::startDemo()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("DemoApp v1.0", this, 0))
		return;
 
	m_bShutdown = false;
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");
 
	setupDemoScene();
	runDemo();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::setupDemoScene()
{
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("Light")->setPosition(50, 50, 50); 
	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("2ndLight")->setPosition(-50, -50, -50); 
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

 	OgreFramework::getSingletonPtr()->sphere_TranslateVector = Ogre::Vector3(0.02, 0.02, 0.02);
	/*
	m_pOgreHeadEntity = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("OgreHeadEntity", "ogrehead.mesh");
	m_pOgreHeadNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
	m_pOgreHeadNode->attachObject(m_pOgreHeadEntity);
	*/

	// Bottom Plane
	Ogre::Plane bottom_plane(Ogre::Vector3::UNIT_Y, -50);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        bottom_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entGround = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("GroundEntity", "ground");
    OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");

	// Top Plane
	Ogre::Plane top_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("top", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        top_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_topNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entTop = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("TopEntity", "top");
    _topNode->attachObject(entTop);
	_topNode->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(180));
	_topNode->setPosition(0, 50, 0);
	entTop->setMaterialName("Examples/Rockwall");


	// Left Plane
	Ogre::Plane left_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        left_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_leftNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entLeft = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("LeftEntity", "left");
    _leftNode->attachObject(entLeft);
	_leftNode->roll(Ogre::Degree(90));
	_leftNode->setPosition(50, 0, 0);
	entLeft->setMaterialName("Examples/Rockwall");

	// Right Plane
	Ogre::Plane right_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        right_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_rightNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entRight = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("RightEntity", "right");
    _rightNode->attachObject(entRight);
	_rightNode->roll(Ogre::Degree(-90));
	_rightNode->setPosition(-50, 0, 0);
	entRight->setMaterialName("Examples/Rockwall");

	// Back Plane
	Ogre::Plane back_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("back", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        back_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_backNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entBack = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("BackEntity", "back");
    _backNode->attachObject(entBack);
	_backNode->pitch(Ogre::Degree(90));
	_backNode->setPosition(0, 0, -50);
	entBack->setMaterialName("Examples/Rockwall");

	// Front Plane
	Ogre::Plane front_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("front", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        front_plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_frontNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entFront = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity("FrontEntity", "front");
    _frontNode->attachObject(entFront);
	_frontNode->pitch(Ogre::Degree(-90));
	_frontNode->setPosition(0, 0, 50);
	entFront->setMaterialName("Examples/Rockwall");

	// Create Sphere
	createSphere(3.5f, 10.0f, -25.0f, 0.1f, "Sphere_-X");
/*
	Ogre::Vector3 _v3SpherePosition = Ogre::Vector3(_rCoordX, _rCoordY, _rCoordZ);
	Ogre::Vector3 _v3SphereScaleFactor = Ogre::Vector3(_rScaleFactor, _rScaleFactor, _rScaleFactor);

	Ogre::Entity *_objSphereEntity = mSceneMgr->createEntity(_strObjName, "sphere.mesh");
	Ogre::SceneNode *_objSphereNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(_strObjName);
	_objSphereNode->attachObject(_objSphereEntity);

	_objSphereNode->setPosition(_v3SpherePosition);
	_objSphereNode->setScale(_v3SphereScaleFactor);
*/
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::runDemo()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Start main loop...");
 
	double timeSinceLastFrame = 0;
	double startTime = 0;
 
      OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
 
	while(!m_bShutdown && !OgreFramework::getSingletonPtr()->isOgreToBeShutDown()) 
	{
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed())m_bShutdown = true;
 
		Ogre::WindowEventUtilities::messagePump();
 
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();
 
			OgreFramework::getSingletonPtr()->m_pKeyboard->capture();
			OgreFramework::getSingletonPtr()->m_pMouse->capture();
 
			OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
			OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();
 
			timeSinceLastFrame = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		}
		else
		{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Shutdown OGRE...");
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
 
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
	{
		 //do something
	}
 
	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
 
	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void DemoApp::createSphere(Ogre::Real _rCoordX, Ogre::Real _rCoordY, Ogre::Real _rCoordZ, Ogre::Real _rScaleFactor, Ogre::String _strObjName)
{
	Ogre::Vector3 _v3SpherePosition = Ogre::Vector3(_rCoordX, _rCoordY, _rCoordZ);
	Ogre::Vector3 _v3SphereScaleFactor = Ogre::Vector3(_rScaleFactor, _rScaleFactor, _rScaleFactor);

	OgreFramework::getSingletonPtr()->_objSphereEntity = OgreFramework::getSingletonPtr()->m_pSceneMgr->createEntity(_strObjName, "sphere.mesh");
	OgreFramework::getSingletonPtr()->_objSphereNode = OgreFramework::getSingletonPtr()->m_pSceneMgr->getRootSceneNode()->createChildSceneNode(_strObjName);
	OgreFramework::getSingletonPtr()->_objSphereNode->attachObject(OgreFramework::getSingletonPtr()->_objSphereEntity);

	OgreFramework::getSingletonPtr()->_objSphereNode->setPosition(_v3SpherePosition);
	OgreFramework::getSingletonPtr()->_objSphereNode->setScale(_v3SphereScaleFactor);


	OgreFramework::getSingletonPtr()->_objSphereEntity->setMaterialName("Examples/SphereMappedRustySteel");

}
