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
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::enter()
{

	server_controller = new MyController();
	client_controller = new MyController();
	physics = new PhysicsWrapper();
	sound_factory = new SoundWrapper();

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ServerState...");

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



	penguin = new Penguin(m_pSceneMgr, physics);		// Create Player 1's Penguin
	penguin_two = new Penguin(m_pSceneMgr, physics);	// Create Player 2's Penguin
	ball = new Ball(m_pSceneMgr, physics);				// Create Ball
	room = new Room(m_pSceneMgr, physics);				// Create Room
	goal = new Goal(m_pSceneMgr, physics);				// Create Goal

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);


	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
 
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);

    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
    sound_factory->playMusic(); 
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

    sound_factory->musicDone();
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

	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
 
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::update(double timeSinceLastFrame)
{
		// TODO - RECEIVE!!!!!!
		// Retrieve the input over the network and
		// update player two's controller

		
	OgreFramework::getSingletonPtr()->server->ReceiveMessage(recvbuffer, 0);

	client_controller->left_control_down = (recvbuffer[0] == '1') ? true : false;
	client_controller->right_control_down = (recvbuffer[1] == '1') ? true : false;
	client_controller->up_control_down = (recvbuffer[2] == '1') ? true : false;
	client_controller->bottom_control_down = (recvbuffer[3] == '1') ? true : false;
	client_controller->forward_control_down = (recvbuffer[4] == '1') ? true : false;
	client_controller->backward_control_down = (recvbuffer[5] == '1') ? true : false;
	client_controller->jump_control_down = (recvbuffer[6] == '1') ? true : false;
	client_controller->boost_control_down = (recvbuffer[7] == '1') ? true : false;
	

 	// Our Team's main loop
	ball->update(timeSinceLastFrame);

	penguin->update(timeSinceLastFrame, server_controller, m_pCamera);
	penguin_two->update(timeSinceLastFrame, client_controller, NULL);


	if (timeSinceLastFrame!=0)
		physics->stepPhysics(timeSinceLastFrame, 5);

	
	// Handles the event in which the player scores
	bool scored = false;
	if(ball->inGoal(goal)){
		scored = true;
		ball->reset(physics);
	}

	// Update Debug Camera
    if(server_controller->debugCameraOn())
    	OgreFramework::getSingletonPtr()->updateDebugCamera(timeSinceLastFrame, m_pCamera);

    // Update Base Framework
    OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

	// SEND Server Message (Visuals of all the items)!!!!!!
	Ogre::Vector3 newballVector = ball->getVisualPosition();
	memcpy(buffer, &newballVector[0], 4);
	memcpy(buffer+4, &newballVector[1], 4);
	memcpy(buffer+8, &newballVector[2], 4);

	printf("BallPosition\n");
	printf("%f\n", newballVector[0]);
	printf("%f\n", newballVector[1]);
	printf("%f\n", newballVector[2]);

	Ogre::Quaternion newballQuaternion = ball->getVisualOrientation();
	memcpy(buffer+12, &newballQuaternion[0], 4);	
	memcpy(buffer+16, &newballQuaternion[1], 4);	
	memcpy(buffer+20, &newballQuaternion[2], 4);	
	memcpy(buffer+24, &newballQuaternion[3], 4);

	Ogre::Vector3 newPenguinServerVector = penguin->getVisualPosition();
	memcpy(buffer+28, &newPenguinServerVector[0], 4);

	OgreFramework::getSingletonPtr()->server->SendMessage(buffer, 32, 0);

	memcpy(buffer, &newPenguinServerVector[1], 4);
	memcpy(buffer+4, &newPenguinServerVector[2], 4);

	printf("ServerPosition\n");
	printf("%f\n", newPenguinServerVector[0]);
	printf("%f\n", newPenguinServerVector[1]);
	printf("%f\n", newPenguinServerVector[2]);

	//printf("Before Quaternion");
	//printf("%02X%02X%02X%02X\n", buffer[12],buffer[13],buffer[14],buffer[15]);
		
	Ogre::Quaternion newPenguinServerQuaternion = penguin->getVisualOrientation();
	memcpy(buffer+8, &newPenguinServerQuaternion[0], 4);	
	memcpy(buffer+12, &newPenguinServerQuaternion[1], 4);	
	memcpy(buffer+16, &newPenguinServerQuaternion[2], 4);	
	memcpy(buffer+20, &newPenguinServerQuaternion[3], 4);

	//printf("After Quaternion");
	//printf("%02X%02X%02X%02X\n", buffer[12],buffer[13],buffer[14],buffer[15]);

	Ogre::Vector3 newPenguinClientVector = penguin_two->getVisualPosition();
	memcpy(buffer+24, &newPenguinClientVector[0], 4);
	memcpy(buffer+28, &newPenguinClientVector[1], 4);

	OgreFramework::getSingletonPtr()->server->SendMessage(buffer, 32, 0);

	memcpy(buffer, &newPenguinClientVector[2], 4);
		
	printf("ClientPosition\n");
	printf("%f\n", newPenguinServerVector[0]);
	printf("%f\n", newPenguinServerVector[1]);
	printf("%f\n", newPenguinServerVector[2]);

	Ogre::Quaternion newPenguinClientQuaternion = penguin_two->getVisualOrientation();
	memcpy(buffer+4, &newPenguinClientQuaternion[0], 4);	
	memcpy(buffer+8, &newPenguinClientQuaternion[1], 4);	
	memcpy(buffer+12, &newPenguinClientQuaternion[2], 4);	
	memcpy(buffer+16, &newPenguinClientQuaternion[3], 4);
		
	OgreFramework::getSingletonPtr()->server->SendMessage(buffer, 32, 0);


	// TODO - SEND!!!!!!
	// Send penguins' and ball's position
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	// Update Controller data members to pass into World later on
	server_controller->keyPressed(keyEventRef);

	// Key Presses to Change State
	if(keyEventRef.key == OIS::KC_P)	        pushAppState(findByName("PauseState"));
	if(keyEventRef.key == OIS::KC_ESCAPE)     	pushAppState(findByName("PauseState"));

	// Key Presses to Activate Sound Effect
    if(keyEventRef.key == OIS::KC_SPACE)		sound_factory->playJumpSoundEffect();

	OgreFramework::getSingletonPtr()->debugKeyPressed(keyEventRef, m_pCamera);

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	server_controller->keyReleased(keyEventRef);
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::mouseMoved(const OIS::MouseEvent &evt)
{

	server_controller->mouseMoved(evt);
	if(!server_controller->thirdPersonCameraOn()){
		m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
		m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
	}
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	server_controller->mousePressed(evt, id);
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	server_controller->mouseReleased(evt, id);
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}
