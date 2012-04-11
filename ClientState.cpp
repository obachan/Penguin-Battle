//|||||||||||||||||||||||||||||||||||||||||||||||

#include "ClientState.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

ClientState::ClientState()
{
	m_pOgreHeadNode			= 0;
	m_pOgreHeadEntity		= 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ClientState::~ClientState()
{
       delete OgreFramework::getSingletonPtr();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void ClientState::enter()
{
	controller_two = new MyController();

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ClientState...");
    OgreFramework::getSingletonPtr()->is_gamestate = true;

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "ClientSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("ClientCam");
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

	ball = new Ball(m_pSceneMgr, NULL, 0, -(room_width/2) + ball_radius, 0, false);
	//test_ball = new Ball(OgreFramework::getSingletonPtr()->m_pSceneMgr, OgreFramework::getSingletonPtr()->physics, 30, 30, 30);


	// Create Room
	room = new Room(m_pSceneMgr, NULL, false);

	// Create Paddle
	//paddle = new Paddle(OgreFramework::getSingletonPtr()->m_pSceneMgr);
	//OgreFramework::getSingletonPtr()->physics->add_object_to_dynamicWorld(paddle->paddleRigidBody);


	// Create Player 1's Penguin
	penguin = new Penguin(m_pSceneMgr, NULL, false);

	// Create Player 2's Penguin
	penguin_two = new Penguin(m_pSceneMgr, NULL, false);

	// Create Goal
	goal = new Goal(m_pSceneMgr, NULL, false);


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
 
 	penguin->update(0.1f, OgreFramework::getSingletonPtr()->controller, OgreFramework::getSingletonPtr()->m_pCamera);
	penguin_two->update(0.1f, controller_two, NULL);
	ball->update(0.1f);
	
	buffer[0] = '0';
	buffer[1] = '0';
	buffer[2] = '0';
	buffer[3] = '0';
	buffer[4] = '0';
	buffer[5] = '0';
	buffer[6] = '0';
	buffer[7] = '0';
	buffer[8] = '\0';

	OgreFramework::getSingletonPtr()->client->SendMessage(buffer, 8);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ClientState::createScene()
{
	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ClientState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving ClientState...");

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

bool ClientState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing ClientState...");
 
    return true;	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ClientState::resume()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming ClientState...");
 
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

void ClientState::update(double timeSinceLastFrame)
{
		// TODO - RECEIVE!!!!!!
		// ball position and penguin's positions

		OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
		
		Ogre::Vector3 newballPosition = Ogre::Vector3(0,0,0);
		memcpy(&newballPosition[0], buffer, 4);
		memcpy(&newballPosition[1], buffer+4, 4);
		memcpy(&newballPosition[2], buffer+8, 4);

		Ogre::Quaternion newballQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newballQuaternion[0], buffer+12, 4);
		memcpy(&newballQuaternion[1], buffer+16, 4);
		memcpy(&newballQuaternion[2], buffer+20, 4);
		memcpy(&newballQuaternion[3], buffer+24, 4);

		printf("%f\n", newballQuaternion[0]);
		printf("%f\n", newballQuaternion[1]);
		printf("%f\n", newballQuaternion[2]);
		printf("%f\n", newballQuaternion[3]);

		Ogre::Vector3 newPenguinServerPosition = Ogre::Vector3(0,0,0);
		memcpy(&newPenguinServerPosition[0], buffer+28, 4);
		memcpy(&newPenguinServerPosition[1], buffer+32, 4);
		memcpy(&newPenguinServerPosition[2], buffer+36, 4);

		Ogre::Quaternion newPenguinServerQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newPenguinServerQuaternion[0], buffer+40, 4);
		memcpy(&newPenguinServerQuaternion[1], buffer+44, 4);
		memcpy(&newPenguinServerQuaternion[2], buffer+48, 4);
		memcpy(&newPenguinServerQuaternion[3], buffer+52, 4);

		Ogre::Vector3 newPenguinClientPosition = Ogre::Vector3(0,0,0);
//		memcpy(&newPenguinClientPosition[0], buffer+56, 4);
//		memcpy(&newPenguinClientPosition[1], buffer+60, 4);
//		memcpy(&newPenguinClientPosition[2], buffer+64, 4);

		Ogre::Quaternion newPenguinClientQuaternion = Ogre::Quaternion(1,0,0,0);
//		memcpy(&newPenguinClientQuaternion[0], buffer+68, 4);
//		memcpy(&newPenguinClientQuaternion[1], buffer+72, 4);
//		memcpy(&newPenguinClientQuaternion[2], buffer+76, 4);
//		memcpy(&newPenguinClientQuaternion[3], buffer+80, 4);

 		// Our Team's main loop
		//ball->update(timeSinceLastFrame);
		ball->updateAsClient(newballPosition);

		penguin->updateAsClient(newPenguinClientPosition, newPenguinClientQuaternion);
		penguin->updateCamera(OgreFramework::getSingletonPtr()->m_pCamera);
		penguin_two->updateAsClient(newPenguinServerPosition, newPenguinServerQuaternion);
		//penguin_two->update(timeSinceLastFrame, controller_two, NULL);

		OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

		//paddle->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller);
	
		// Handles the event in which the player scores
		bool scored = false;

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

		

		// TODO - SEND!!!!!!
		// Player 2's controller

	buffer[0] = (OgreFramework::getSingletonPtr()->controller->left_control_down) ? '1' : '0';
	buffer[1] = (OgreFramework::getSingletonPtr()->controller->right_control_down) ? '1' : '0';
	buffer[2] = (OgreFramework::getSingletonPtr()->controller->up_control_down) ? '1' : '0';
	buffer[3] = (OgreFramework::getSingletonPtr()->controller->bottom_control_down) ? '1' : '0';
	buffer[4] = (OgreFramework::getSingletonPtr()->controller->forward_control_down) ? '1' : '0';
	buffer[5] = (OgreFramework::getSingletonPtr()->controller->backward_control_down) ? '1' : '0';
	buffer[6] = (OgreFramework::getSingletonPtr()->controller->jump_control_down) ? '1' : '0';
	buffer[7] = (OgreFramework::getSingletonPtr()->controller->boost_control_down) ? '1' : '0';
	buffer[8] = '\0';

	OgreFramework::getSingletonPtr()->client->SendMessage(buffer, 8);

	////////////////////////////////////////////////
	//OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();	
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ClientState::startDemo()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("ClientState v1.0", this, 0))
		return;
 
	m_bShutdown = false;
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");

	setupDemoScene();
	runDemo();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ClientState::setupDemoScene()
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
 
void ClientState::runDemo()
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

				/*
				bool scored = false;

				if(ball->inGoal(goal))
				{
					scored = true;
					ball->reset(physics);
				}
				

				OgreFramework::getSingletonPtr()->hud->update(timeSinceLastFrame, scored);
				*/
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
 
bool ClientState::keyPressed(const OIS::KeyEvent &keyEventRef)
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
 
bool ClientState::keyReleased(const OIS::KeyEvent &keyEventRef)
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
 
bool ClientState::mouseMoved(const OIS::MouseEvent &evt)
{
	OgreFramework::getSingletonPtr()->m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
	OgreFramework::getSingletonPtr()->m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));

	
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}
