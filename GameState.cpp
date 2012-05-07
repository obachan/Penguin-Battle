//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"
#include "WorldObjectBall.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

GameState::GameState()
{
	m_pOgreHeadNode			= 0;
	m_pOgreHeadEntity		= 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
GameState::~GameState()
{
       delete OgreFramework::getSingletonPtr();
       delete physics;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{

	physics = new PhysicsWrapper();

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
    OgreFramework::getSingletonPtr()->is_gamestate = true;

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("GameCam");
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

  	worldObjectFactory = new WorldObjectFactory();
	ball = new Ball(m_pSceneMgr, physics); 			// Create Ball
	room = new Room(m_pSceneMgr, physics); 			// Create Room
	penguin = new Penguin(m_pSceneMgr, physics); 	// Create Penguin
	goal = new Goal(m_pSceneMgr, physics);			// Create Goal
	terrain = new Terrain(m_pSceneMgr);				// Create Terrain

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

void GameState::createScene()
{
	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);

    OgreFramework::getSingletonPtr()->is_gamestate = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");
 
    return true;	
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");
 
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

void GameState::update(double timeSinceLastFrame)
{


 		// Our Team's main loop
		ball->update(timeSinceLastFrame);

		//test_ball->update(timeSinceLastFrame);
		//test_ball->reset(OgreFramework::getSingletonPtr()->physics);

		penguin->update(timeSinceLastFrame, OgreFramework::getSingletonPtr()->controller, OgreFramework::getSingletonPtr()->m_pCamera);

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

	////////////////////////////////////////////////
	//OgreFramework::getSingletonPtr()->m_pRoot->renderOneFrame();	
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
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
		controller->toggleThirdPersonCamera();
	}

	if(keyEventRef.key == OIS::KC_P)
	{
        pushAppState(findByName("PauseState"));
	}

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
    }

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
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
 
bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
	MyController* controller = OgreFramework::getSingletonPtr()->controller;
	//std::cerr << "mouse moved " << evt.state.X.rel << std::endl;
	controller->mouse_x_movement = -evt.state.X.rel;
	controller->mouse_y_movement = -evt.state.Y.rel;

	if(!controller->thirdPersonCameraOn()){
		OgreFramework::getSingletonPtr()->m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
		OgreFramework::getSingletonPtr()->m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
	}
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	switch (id)
	{
	case OIS::MB_Left:
	//	fireSnowBall();
	   break;

	case OIS::MB_Right:
		
	   break;

	default:
	   break;
	}


    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}
