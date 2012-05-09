//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"
#include "OgreBillboardParticleRenderer.h"

#include "World.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

GameState::GameState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
GameState::~GameState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{

	physics = new PhysicsWrapper();
	controller = new MyController();
	soundFactory = new SoundWrapper();
	hud = new HUD();

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("GameCam");
	m_pCamera->setPosition(Vector3(0, -40, 125));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);
 
    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
 

	// Sets global world 
	m_pSceneMgr->setSkyBox(true, "CustomSkyBox");

	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 


	//create particle effects
	ParticleSystem* pSys4 = m_pSceneMgr->createParticleSystem("rain", "Examples/Rain");
	SceneNode* rNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	rNode->translate(0,1000,0);
	rNode->attachObject(pSys4);






    // Create a light
  	m_pSceneMgr->createLight("MainLight")->setPosition(0,50,0);

	OgreFramework::getSingletonPtr()->m_pSceneMgr = m_pSceneMgr;
	OgreFramework::getSingletonPtr()->m_pCamera = m_pCamera;

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

    soundFactory->playMusic();
    

    worldObjectFactory = new WorldObjectFactory(m_pSceneMgr, physics);	// World Object Factory

    ball = worldObjectFactory->createNewBall(); 		// Create Ball
	room = worldObjectFactory->createNewRoom(); 		// Create Room
	penguin =  worldObjectFactory->createNewPenguin(); 	// Create Penguin
	goal = worldObjectFactory->createNewGoal(); 		// Create Goal
	terrain = worldObjectFactory->createNewTerrain(); 	// Create Terrain
 
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
	penguin->update(timeSinceLastFrame, controller, m_pCamera);

	OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

	if (timeSinceLastFrame!=0){
		physics->stepPhysics(timeSinceLastFrame, 5);
	}
	
	// Handles the event in which the player scores
	bool scored = false;
	if(ball->inGoal(goal)){
		scored = true;
		ball->reset(physics);
	}

	// Update HUD
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

    // Update Debug Camera
    if(controller->debugCameraOn())
    	OgreFramework::getSingletonPtr()->updateDebugCamera(timeSinceLastFrame);
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

	// Key Presses to Modify Controller
	if(keyEventRef.key == OIS::KC_LEFT)			controller->left_control_down = true;
	if(keyEventRef.key == OIS::KC_RIGHT)		controller->right_control_down = true;
	if(keyEventRef.key == OIS::KC_UP)			controller->forward_control_down = true;
	if(keyEventRef.key == OIS::KC_DOWN)			controller->backward_control_down = true;
	if(keyEventRef.key == OIS::KC_P)			controller->up_control_down = true;
	if(keyEventRef.key == OIS::KC_SEMICOLON)	controller->bottom_control_down = true;
	if(keyEventRef.key == OIS::KC_SPACE)		controller->jump_control_down = true;
	if(keyEventRef.key == OIS::KC_Z)			controller->boost_control_down = true;
	if(keyEventRef.key == OIS::KC_Q)			controller->toggleThirdPersonCamera();

	// Key Presses to Change State
	if(keyEventRef.key == OIS::KC_P)	        pushAppState(findByName("PauseState"));
	if(keyEventRef.key == OIS::KC_ESCAPE)     	pushAppState(findByName("PauseState"));

	// Key Presses to Activate Sound Effect
    if(keyEventRef.key == OIS::KC_SPACE){
		if(!penguin->in_air)
			soundFactory->playJumpSoundEffect();
	}
	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef){
	// Key Presses to Modify Controller
	if(keyEventRef.key == OIS::KC_LEFT)			controller->left_control_down = false;
	if(keyEventRef.key == OIS::KC_RIGHT)		controller->right_control_down = false;	
	if(keyEventRef.key == OIS::KC_UP)			controller->forward_control_down = false;	
	if(keyEventRef.key == OIS::KC_DOWN)			controller->backward_control_down = false;	
	if(keyEventRef.key == OIS::KC_P)			controller->up_control_down = false;
	if(keyEventRef.key == OIS::KC_SEMICOLON)	controller->bottom_control_down = false;
	if(keyEventRef.key == OIS::KC_Z)			controller->boost_control_down = false;

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
	// Controller holds the last mouse position
	controller->mouse_x_movement = -evt.state.X.rel;
	controller->mouse_y_movement = -evt.state.Y.rel;

	// If it's in debug mode, allow the mouse to navigate the scene
	if(!controller->thirdPersonCameraOn()){
		m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
		m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
	}
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	switch (id)
	{
	case OIS::MB_Left:
		//ball->reset(physics);
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
