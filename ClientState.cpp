//|||||||||||||||||||||||||||||||||||||||||||||||

#include "ClientState.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

ClientState::ClientState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ClientState::~ClientState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void ClientState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ClientState...");

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

	client_controller = new MyController();

	penguin = new Penguin(m_pSceneMgr, NULL);									// Create Player 1's Penguin
	penguin_two = new Penguin(m_pSceneMgr, NULL);								// Create Player 2's Penguin
	ball = new Ball(m_pSceneMgr, NULL, 0, -(room_width/2) + ball_radius, 0);	// Create Ball
	room = new Room(m_pSceneMgr, NULL);											// Create Room
	goal = new Goal(m_pSceneMgr, NULL);											// Create Goal

	sound_factory = new SoundWrapper();
    sound_factory->playMusic();

	OgreFramework::getSingletonPtr()->m_pSceneMgr = m_pSceneMgr;
	OgreFramework::getSingletonPtr()->m_pCamera = m_pCamera;

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);


	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
 
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);

    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();

 
 	penguin->update(0.1f, client_controller, OgreFramework::getSingletonPtr()->m_pCamera);
	penguin_two->update(0.1f, client_controller, NULL);
	ball->update(0.1f);
	
	sendbuffer[0] = '0';
	sendbuffer[1] = '0';
	sendbuffer[2] = '0';
	sendbuffer[3] = '0';
	sendbuffer[4] = '0';
	sendbuffer[5] = '0';
	sendbuffer[6] = '0';
	sendbuffer[7] = '0';
	sendbuffer[8] = '\0';

	OgreFramework::getSingletonPtr()->client->SendMessage(sendbuffer, 8);
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

    sound_factory->musicDone();
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
		
	printf("BallPosition\n");
	printf("%f\n", newballPosition[0]);
	printf("%f\n", newballPosition[1]);
	printf("%f\n", newballPosition[2]);

	Ogre::Quaternion newballQuaternion = Ogre::Quaternion(1,0,0,0);
	memcpy(&newballQuaternion[0], buffer+12, 4);
	memcpy(&newballQuaternion[1], buffer+16, 4);
	memcpy(&newballQuaternion[2], buffer+20, 4);
	memcpy(&newballQuaternion[3], buffer+24, 4);	

	Ogre::Vector3 newPenguinServerPosition = Ogre::Vector3(0,0,0);
	memcpy(&newPenguinServerPosition[0], buffer+28, 4);

	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);

	memcpy(&newPenguinServerPosition[1], buffer, 4);
	memcpy(&newPenguinServerPosition[2], buffer+4, 4);

	printf("ServerPosition\n");
	printf("%f\n", newPenguinServerPosition[0]);
	printf("%f\n", newPenguinServerPosition[1]);
	printf("%f\n", newPenguinServerPosition[2]);

	Ogre::Quaternion newPenguinServerQuaternion = Ogre::Quaternion(1,0,0,0);
	memcpy(&newPenguinServerQuaternion[0], buffer+8, 4);
	memcpy(&newPenguinServerQuaternion[1], buffer+12, 4);
	memcpy(&newPenguinServerQuaternion[2], buffer+16, 4);
	memcpy(&newPenguinServerQuaternion[3], buffer+20, 4);

	Ogre::Vector3 newPenguinClientPosition = Ogre::Vector3(0,0,0);
	memcpy(&newPenguinClientPosition[0], buffer+24, 4);
	memcpy(&newPenguinClientPosition[1], buffer+28, 4);

	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);

	memcpy(&newPenguinClientPosition[2], buffer, 4);

	printf("ClientPosition\n");
	printf("%f\n", newPenguinClientPosition[0]);
	printf("%f\n", newPenguinClientPosition[1]);
	printf("%f\n", newPenguinClientPosition[2]);

	Ogre::Quaternion newPenguinClientQuaternion = Ogre::Quaternion(1,0,0,0);
	memcpy(&newPenguinClientQuaternion[0], buffer+4, 4);
	memcpy(&newPenguinClientQuaternion[1], buffer+8, 4);
	memcpy(&newPenguinClientQuaternion[2], buffer+12, 4);
	memcpy(&newPenguinClientQuaternion[3], buffer+16, 4);

 	// Our Team's main loop
	//ball->update(timeSinceLastFrame);
	ball->updateAsClient(newballPosition);

	penguin->updateAsClient(newPenguinClientPosition, newPenguinClientQuaternion);
	penguin_two->updateAsClient(newPenguinServerPosition, newPenguinServerQuaternion);
	
  	// Update Debug Camera
    if(client_controller->debugCameraOn())
    	OgreFramework::getSingletonPtr()->updateDebugCamera(timeSinceLastFrame);

    // Update Base Framework
    OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);


	// TODO - SEND Client Message (just the controller)!!!!!!
	// Player 2's controller

	sendbuffer[0] = (client_controller->left_control_down) ? '1' : '0';
	sendbuffer[1] = (client_controller->right_control_down) ? '1' : '0';
	sendbuffer[2] = (client_controller->up_control_down) ? '1' : '0';
	sendbuffer[3] = (client_controller->bottom_control_down) ? '1' : '0';
	sendbuffer[4] = (client_controller->forward_control_down) ? '1' : '0';
	sendbuffer[5] = (client_controller->backward_control_down) ? '1' : '0';
	sendbuffer[6] = (client_controller->jump_control_down) ? '1' : '0';
	sendbuffer[7] = (client_controller->boost_control_down) ? '1' : '0';
	sendbuffer[8] = '\0';

	OgreFramework::getSingletonPtr()->client->SendMessage(sendbuffer, 8);
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	// Update Controller data members to pass into World later on
	client_controller->keyPressed(keyEventRef);

	// Key Presses to Change State
	if(keyEventRef.key == OIS::KC_P)	        pushAppState(findByName("PauseState"));
	if(keyEventRef.key == OIS::KC_ESCAPE)     	pushAppState(findByName("PauseState"));

	// Key Presses to Activate Sound Effect
    if(keyEventRef.key == OIS::KC_SPACE)		sound_factory->playJumpSoundEffect();

	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	client_controller->keyReleased(keyEventRef);
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mouseMoved(const OIS::MouseEvent &evt)
{
	client_controller->mouseMoved(evt);
	// If it's in debug mode, allow the mouse to navigate the scene
	if(!client_controller->thirdPersonCameraOn())		OgreFramework::getSingletonPtr()->mouseMoved(evt);
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	client_controller->mouseReleased(evt, id);
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	client_controller->mouseReleased(evt, id);
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}
