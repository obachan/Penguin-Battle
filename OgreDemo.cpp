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
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setSkyBox(true, "Examples/StarsSkyBox");

	OgreFramework::getSingletonPtr()->m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	OgreFramework::getSingletonPtr()->m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    	// Create a light
  	OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("MainLight")->setPosition(0,50,0);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("2ndLight")->setPosition(50, 50, 50);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("3rdLight")->setPosition(-50, 50, -50);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("4thLight")->setPosition(50, 50, -50);

	// Create Ball
	ball = new Ball(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics);
	//test_ball = new Ball(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics, 30, 30, 30);


	// Create Room
	room = new Room(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics);

	// Create Paddle
	//paddle = new Paddle(OgreFramework::getSingletonPtr()->m_pSceneMgr);
	//OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(paddle->paddleRigidBody);

	// Create Penguin
	penguin = new Penguin(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics);

	// Create Goal
	goal = new Goal(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics);

	pause_state = false;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void DemoApp::runDemo()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Start main loop...");
 
	double timeSinceLastFrame = 0;
	double startTime = 0;
 
    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
 
    OgreFramework::getSingletonPtr()->sounds->playMusic();

	while(!m_bShutdown && !OgreFramework::getSingletonPtr()->isOgreToBeShutDown()) 
	{
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isClosed())m_bShutdown = true;
 
		Ogre::WindowEventUtilities::messagePump();
 
		if(OgreFramework::getSingletonPtr()->m_pRenderWnd->isActive())
		{
			startTime = OgreFramework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();
 
			OgreFramework::getSingletonPtr()->m_pKeyboard->capture();
			OgreFramework::getSingletonPtr()->m_pMouse->capture();
 			
			if (!pause_state)
			{
 				// Our Team's main loop

				ball->update(timeSinceLastFrame);
				//test_ball->update(timeSinceLastFrame);
				//test_ball->reset(OgreFramework::getSingletonPtr()->physics);




				penguin->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller, OgreFramework::getSingletonPtr()->m_pCamera);
				OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
				//paddle->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller);
	
				// Handles the event in which the player scores


				bool scored = false;

				if(ball->inGoal(goal))
				{
					scored = true;
					ball->reset(OgreFramework::getSingletonPtr()->physics);
				}


				OgreFramework::getSingletonPtr()->hud->update(timeSinceLastFrame, scored);
			}

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

	//std::cout << controller->left_control_down << std::endl;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_LEFT))
		controller->left_control_down = true;	
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RIGHT))
		controller->right_control_down = true;
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_UP))
		controller->forward_control_down = true;
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_DOWN))
		controller->backward_control_down = true;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_P))
		controller->up_control_down = true;
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_SEMICOLON))
		controller->bottom_control_down = true;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_SPACE)){
		controller->jump_control_down = true;
		if(!penguin->in_air)
			OgreFramework::getSingletonPtr()->sounds->playJumpSoundEffect();
	}


	if(keyEventRef.key == OIS::KC_Z){
		controller->boost_control_down = true;
	}

	if(keyEventRef.key == OIS::KC_Q)
	{
		penguin->toggleThirdPersonCamera();
	}

	if(keyEventRef.key == OIS::KC_P)
	{
		pause_state = !pause_state;
	}

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool DemoApp::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
 
	MyController* controller = OgreFramework::getSingletonPtr()->controller;

	if(keyEventRef.key == OIS::KC_LEFT){
		//std::cout << controller->left_control_down << std::endl;		
		controller->left_control_down = false;
	}	

	if(keyEventRef.key == OIS::KC_RIGHT){
		controller->right_control_down = false;	
	}	

	if(keyEventRef.key == OIS::KC_UP){
		controller->forward_control_down = false;	
	}

	if(keyEventRef.key == OIS::KC_DOWN){
		controller->backward_control_down = false;	
	}

	if(keyEventRef.key == OIS::KC_P){
		controller->up_control_down = false;
	}

	if(keyEventRef.key == OIS::KC_SEMICOLON){
		controller->bottom_control_down = false;
	}

	if(keyEventRef.key == OIS::KC_Z){
		controller->boost_control_down = false;
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool mouseMoved(const OIS::MouseEvent &arg )
{

  controller->mouse_x_movement = e.state.X.rel;
  std::cerr << "x: " << e.state.X.rel << std::endl;

}



//||||||||||||||||||||||||||||||||||||||||||||||||
