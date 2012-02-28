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

	// Sets global world conditions
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("Light")->setPosition(50, 50, 50); 
	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("2ndLight")->setPosition(-50, -50, -50); 
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);


	// Create Ball
	ball = new Ball(OgreFramework::getSingletonPtr()->m_pSceneMgr);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(ball->ballRigidBody);

	// Create Room
	room = new Room(OgreFramework::getSingletonPtr()->m_pSceneMgr);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->frontRigidBody);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->backRigidBody);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->rightRigidBody);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->leftRigidBody);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->topRigidBody);
	OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(room->bottomRigidBody);
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

			ball->update(timeSinceLastFrame);


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
