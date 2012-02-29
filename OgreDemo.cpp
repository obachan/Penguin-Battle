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

	// Create Paddle
	paddle = new Paddle(OgreFramework::getSingletonPtr()->m_pSceneMgr);

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
 			

 			// Our Team's main loop
			processController();

			OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

			ball->update(timeSinceLastFrame);


			////////////////////////////////////////////////

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
 
	MyController* controller = OgreFramework::getSingletonPtr()->controller;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_LEFT))
	{
		//std::cout << controller->left_control_down << std::endl;
		controller->left_control_down = true;	
		
	}

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RIGHT))
	{
		controller->right_control_down = true;
		
	}
 
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_UP))
	{
		controller->up_control_down = true;
		
	}

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_DOWN))
	{
		controller->bottom_control_down = true;
		
	}

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
 
	MyController* controller = OgreFramework::getSingletonPtr()->controller;

	if(keyEventRef.key == OIS::KC_LEFT){
		std::cout << controller->left_control_down << std::endl;		
		controller->left_control_down = false;	
	}	

	if(keyEventRef.key == OIS::KC_RIGHT){
		controller->right_control_down = false;	
	}	

	if(keyEventRef.key == OIS::KC_UP){
		controller->up_control_down = false;	
	}

	if(keyEventRef.key == OIS::KC_DOWN){
		controller->bottom_control_down = false;	
	}

	return true;
}

//||||||||||||||||||||||||||||||||||||||||||||||||

void DemoApp::processController()
{
	MyController* controller = OgreFramework::getSingletonPtr()->controller;

	if(controller->left_control_down == true){
		paddle->moveLeft();
	}

	if(controller->right_control_down == true){
		paddle->moveRight();
	}

	if(controller->up_control_down == true){
		paddle->moveUp();
	}

	if(controller->bottom_control_down == true){
		paddle->moveDown();
	}
}