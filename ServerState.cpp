//|||||||||||||||||||||||||||||||||||||||||||||||

#include "ServerState.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

ServerState::ServerState()
{
	m_pOgreHeadNode			= 0;
	m_pOgreHeadEntity		= 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ServerState::~ServerState()
{
       delete OgreFramework::getSingletonPtr();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::enter()
{

	controller_two = new MyController();
	physics = new PhysicsWrapper();

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ServerState...");
    OgreFramework::getSingletonPtr()->is_gamestate = true;

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "ServerSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("ServerCam");
	m_pCamera->setPosition(Vector3(0, -40, 125));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);
 
    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
 

	// Sets global world conditions
	m_pSceneMgr->setSkyBox(true, "Examples/StarsSkyBox");


	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 

    // Create a light
  	m_pSceneMgr->createLight("MainLight")->setPosition(0,50,0);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("2ndLight")->setPosition(50, 50, 50);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("3rdLight")->setPosition(-50, 50, -50);
	//OgreFramework::getSingletonPtr()->m_pSceneMgr->createLight("4thLight")->setPosition(50, 50, -50);

	// Create Ball
	ball = new Ball(m_pSceneMgr, physics);
	//test_ball = new Ball(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics, 30, 30, 30);


	// Create Room
	room = new Room(m_pSceneMgr, physics);

	// Create Paddle
	//paddle = new Paddle(OgreFramework::getSingletonPtr()->m_pSceneMgr);
	//OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(paddle->paddleRigidBody);

	// Create Player 1's Penguin
	penguin = new Penguin(m_pSceneMgr, physics);

	// Create Player 2's Penguin
	penguin_two = new Penguin(m_pSceneMgr, physics);

	// Create Goal
	goal = new Goal(m_pSceneMgr, physics);


	OgreFramework::getSingletonPtr()->m_pSceneMgr = m_pSceneMgr;
	OgreFramework::getSingletonPtr()->m_pCamera = m_pCamera;

	pause_state = false;


    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);


	Ogre::StringVector items;
	items.push_back("Time Left      ");
    items.push_back("Target Score  ");
    items.push_back("Score          ");
    items.push_back("Status         ");

  	mDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(0, "60"); 	//Set initial Timer Value
    mDetailsPanel->setParamValue(1, "5");	//Set Target Score Value
    mDetailsPanel->setParamValue(2, "0");	//Set initial Score Value
    mDetailsPanel->setParamValue(3, "Playing");	//Set initial Score Value
	mDetailsPanel->show();

	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
 
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);

    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
    OgreFramework::getSingletonPtr()->sounds->playMusic();

    OgreFramework::getSingletonPtr()->hud->reset();
 
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::createScene()
{
	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving ServerState...");

	m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);

    OgreFramework::getSingletonPtr()->is_gamestate = false;

    OgreFramework::getSingletonPtr()->sounds->musicDone();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool ServerState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing ServerState...");
 
    return true;	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::resume()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming ServerState...");
 
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);


	Ogre::StringVector items;
	items.push_back("Time Left      ");
    items.push_back("Target Score  ");
    items.push_back("Score          ");
    items.push_back("Status         ");

  	mDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(0, "60"); 	//Set initial Timer Value
    mDetailsPanel->setParamValue(1, "5");	//Set Target Score Value
    mDetailsPanel->setParamValue(2, "0");	//Set initial Score Value
    mDetailsPanel->setParamValue(3, "Playing");	//Set initial Score Value
	mDetailsPanel->show();

	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
 
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::update(double timeSinceLastFrame)
{
		// TODO - RECEIVE!!!!!!
		// Retrieve the input over the network and
		// update player two's controller

		
		OgreFramework::getSingletonPtr()->server->ReceiveMessage(buffer);

		controller_two->left_control_down = (buffer[0] == '1') ? true : false;
		controller_two->right_control_down = (buffer[1] == '1') ? true : false;
		controller_two->up_control_down = (buffer[2] == '1') ? true : false;
		controller_two->bottom_control_down = (buffer[3] == '1') ? true : false;
		controller_two->forward_control_down = (buffer[4] == '1') ? true : false;
		controller_two->backward_control_down = (buffer[5] == '1') ? true : false;
		controller_two->jump_control_down = (buffer[6] == '1') ? true : false;
		controller_two->boost_control_down = (buffer[7] == '1') ? true : false;

		

 		// Our Team's main loop
		ball->update(timeSinceLastFrame);

		//test_ball->update(timeSinceLastFrame);
		//test_ball->reset(OgreFramework::getSingletonPtr()->physics);

		penguin->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller, OgreFramework::getSingletonPtr()->m_pCamera);
		penguin_two->update(timeSinceLastFrame, controller_two, NULL);

		OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

		if (timeSinceLastFrame!=0)
		{
	 		physics->stepPhysics(timeSinceLastFrame, 5);
		
		}

		//paddle->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller);
	
		// Handles the event in which the player scores

		bool scored = false;

		if(ball->inGoal(goal))
		{
			scored = true;
			ball->reset(physics);
		}


		OgreFramework::getSingletonPtr()->hud->update(timeSinceLastFrame, scored);


		if (!OgreFramework::getSingletonPtr()->m_pTrayMgr->isDialogVisible())
	    {
	       	//mCameraMan->frameRenderingQueued(m_FrameEvent);
	    	
	    	// if dialog isn't up, then update the camera
	    	// if details panel is visible, then update its contents

	    	if (mDetailsPanel->isVisible())
	       	{
				//Change Score and Timer Value each Frame
	       	    mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(OgreFramework::getSingletonPtr()->hud->timer));
	       	    mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(OgreFramework::getSingletonPtr()->hud->score));


	       	    std::string hud_status_message;
	       	    if(OgreFramework::getSingletonPtr()->hud->hud_status == HUD::HUD_STATUS_PLAYING)
	       	    	hud_status_message = "Playing";
	       	    else if(OgreFramework::getSingletonPtr()->hud->hud_status == HUD::HUD_STATUS_WIN)
	       	    	hud_status_message = "You Win";
	       	    else if(OgreFramework::getSingletonPtr()->hud->hud_status == HUD::HUD_STATUS_LOSE)
	       	    	hud_status_message = "You Lose";


	       	    mDetailsPanel->setParamValue(3, hud_status_message);    	
	       	}
	    }

		Ogre::Vector3 newballVector = ball->getBallPosition();
		memcpy(buffer, &newballVector[0], 4);
		memcpy(buffer+4, &newballVector[1], 4);
		memcpy(buffer+8, &newballVector[2], 4);

		Ogre::Quaternion newballQuaternion = ball->getBallOrientation();
		memcpy(buffer+12, &newballQuaternion[0], 4);	
		memcpy(buffer+16, &newballQuaternion[1], 4);	
		memcpy(buffer+20, &newballQuaternion[2], 4);	
		memcpy(buffer+24, &newballQuaternion[3], 4);

		Ogre::Vector3 newPenguinServerVector = penguin->getPenguinPosition();
		memcpy(buffer+28, &newPenguinServerVector[0], 4);
		memcpy(buffer+32, &newPenguinServerVector[1], 4);
		memcpy(buffer+36, &newPenguinServerVector[2], 4);

		Ogre::Quaternion newPenguinServerQuaternion = penguin->getPenguinOrientation();
		memcpy(buffer+40, &newPenguinServerQuaternion[0], 4);	
		memcpy(buffer+44, &newPenguinServerQuaternion[1], 4);	
		memcpy(buffer+48, &newPenguinServerQuaternion[2], 4);	
		memcpy(buffer+52, &newPenguinServerQuaternion[3], 4);
/*
		Ogre::Vector3 newPenguinClientVector = penguin_two->getPenguinPosition();
		memcpy(buffer+56, &newPenguinClientVector[0], 4);
		memcpy(buffer+60, &newPenguinClientVector[1], 4);
		memcpy(buffer+64, &newPenguinClientVector[2], 4);

		Ogre::Quaternion newPenguinClientQuaternion = penguin_two->getPenguinOrientation();
		memcpy(buffer+68, &newPenguinClientQuaternion[0], 4);	
		memcpy(buffer+72, &newPenguinClientQuaternion[1], 4);	
		memcpy(buffer+76, &newPenguinClientQuaternion[2], 4);	
		memcpy(buffer+80, &newPenguinClientQuaternion[3], 4);
*/
		OgreFramework::getSingletonPtr()->server->SendMessage(buffer, 56);
//		OgreFramework::getSingletonPtr()->server->SendMessage(buffer, 84);


		// TODO - SEND!!!!!!
		// Send penguins' and ball's position



}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ServerState::startDemo()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("ServerState v1.0", this, 0))
		return;
 
	m_bShutdown = false;
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");

	setupDemoScene();
	runDemo();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ServerState::setupDemoScene()
{
/*

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
*/
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ServerState::runDemo()
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
					ball->reset(physics);
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
 
bool ServerState::keyPressed(const OIS::KeyEvent &keyEventRef)
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
/*
	if(keyEventRef.key == OIS::KC_P)
	{
		pause_state = !pause_state;
	}
*/
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::keyReleased(const OIS::KeyEvent &keyEventRef)
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
 
bool ServerState::mouseMoved(const OIS::MouseEvent &evt)
{
	OgreFramework::getSingletonPtr()->m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
	OgreFramework::getSingletonPtr()->m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));

	
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}
