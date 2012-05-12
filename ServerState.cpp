//|||||||||||||||||||||||||||||||||||||||||||||||

#include "ServerState.hpp"

#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;

ServerState::ServerState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ServerState::~ServerState()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::enter()
{

	printf("ENTERED SERVER STATE\n\n\n\n\n");
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

    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);

	OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
	OgreFramework::getSingletonPtr()->m_pRenderWnd->setActive(true);
    OgreFramework::getSingletonPtr()->m_pRenderWnd->resetStatistics();

	// penguin = new Penguin(m_pSceneMgr, physics);		// Create Player 1's Penguin
	// ball = new Ball(m_pSceneMgr, physics);				// Create Ball
	// room = new Room(m_pSceneMgr, physics);				// Create Room
	// goal = new Goal(m_pSceneMgr, physics);				// Create Goal

	server_controller = new MyController();
	
	physics = new PhysicsWrapper();
	sound_factory = new SoundWrapper();

	hud = new HUD(OgreFramework::getSingletonPtr()->m_pTrayMgr);
	numberOfClients = OgreFramework::getSingletonPtr()->server->getNumberOfClients();
    	world = new World(m_pSceneMgr, physics, server_controller, numberOfClients);
	int totalPlayers = numberOfClients+1;
	memcpy(buffer, &totalPlayers, 4);
	
	OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 4);

	/*
	for (int i = 0;i<numberOfClients; i++)
	{
		client_controllers.push_back(new MyController());
    		clientPenguins.push_back(new Penguin(m_pSceneMgr, physics, client_controllers[i]));	// Create Player 2's Penguin
		
	}*/

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
	hud->resume();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void ServerState::update(double timeSinceLastFrame)
{
		// TODO - RECEIVE!!!!!!
		// Retrieve the input over the network and
		// update player two's controller
	printf("Before Server UPDATE");



	int tempClientID = 0;
	
	
	for (int i = 0; i< numberOfClients; i++)
	{
		OgreFramework::getSingletonPtr()->server->ReceiveMessage(recvbuffer, 0);
		memcpy(&tempClientID, recvbuffer, 4);
		world->client_controllers[tempClientID]->left_mouse_button_down = (recvbuffer[4] == '1') ? true : false;
		world->client_controllers[tempClientID]->right_mouse_button_down = (recvbuffer[5] == '1') ? true : false;
		world->client_controllers[tempClientID]->left_control_down = (recvbuffer[6] == '1') ? true : false;
		world->client_controllers[tempClientID]->right_control_down = (recvbuffer[7] == '1') ? true : false;
		world->client_controllers[tempClientID]->up_control_down = (recvbuffer[8] == '1') ? true : false;
		world->client_controllers[tempClientID]->bottom_control_down = (recvbuffer[9] == '1') ? true : false;
		world->client_controllers[tempClientID]->forward_control_down = (recvbuffer[10] == '1') ? true : false;
		world->client_controllers[tempClientID]->backward_control_down = (recvbuffer[11] == '1') ? true : false;
		world->client_controllers[tempClientID]->jump_control_down = (recvbuffer[12] == '1') ? true : false;
		world->client_controllers[tempClientID]->boost_control_down = (recvbuffer[13] == '1') ? true : false;
		printf("BEFORE CLIENT PENGUIN UPDATE");
		//world->clientPenguins[tempClientID]->update(timeSinceLastFrame, world->client_controllers[tempClientID], NULL);
		printf("After client penguin update");
	}
	
	world->update(timeSinceLastFrame, server_controller, m_pCamera);		// Update World

	std::cout << "Here ====================================" << std::endl;
	
	std::cout << "Here ====================================" << std::endl;

	hud->update(timeSinceLastFrame, false);

	// Update Debug Camera
    if(server_controller->debugCameraOn())
    	OgreFramework::getSingletonPtr()->updateDebugCamera(timeSinceLastFrame, m_pCamera);

    // Update Base Framework
    OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);

    // ===========================================================================
	// SEND Server Message (Visuals of all the items)!!!!!!
	int ballNum = world->world_objects.size();

	memcpy(buffer, &ballNum, 4);

	OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 32);

	//for (int i = 0; i<ballNum;i++)
	//{
	
		Ogre::Vector3 newballVector = world->world_objects[0]->getVisualPosition();
		memcpy(buffer, &newballVector[0], 4);
		memcpy(buffer+4, &newballVector[1], 4);
		memcpy(buffer+8, &newballVector[2], 4);
	
		printf("BallPosition\n");
		printf("%f\n", newballVector[0]);
		printf("%f\n", newballVector[1]);
		printf("%f\n", newballVector[2]);	

		Ogre::Quaternion newballQuaternion = world->world_objects[0]->getVisualOrientation();
		memcpy(buffer+12, &newballQuaternion[0], 4);	
		memcpy(buffer+16, &newballQuaternion[1], 4);	
		memcpy(buffer+20, &newballQuaternion[2], 4);	
		memcpy(buffer+24, &newballQuaternion[3], 4);
		OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 32);
	//}

	Ogre::Vector3 newPenguinServerVector = world->penguin->getVisualPosition();
	memcpy(buffer, &newPenguinServerVector[0], 4);
	memcpy(buffer+4, &newPenguinServerVector[1], 4);
	memcpy(buffer+8, &newPenguinServerVector[2], 4);

	printf("ServerPosition\n");
	printf("%f\n", newPenguinServerVector[0]);
	printf("%f\n", newPenguinServerVector[1]);
	printf("%f\n", newPenguinServerVector[2]);

	Ogre::Quaternion newPenguinServerQuaternion = world->penguin->getVisualOrientation();
	memcpy(buffer+12, &newPenguinServerQuaternion[0], 4);	
	memcpy(buffer+16, &newPenguinServerQuaternion[1], 4);	
	memcpy(buffer+20, &newPenguinServerQuaternion[2], 4);	
	memcpy(buffer+24, &newPenguinServerQuaternion[3], 4);

	printf("Before Server Send");
	OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 32);
	printf("After Server Send");

	//for (int i = 0; i<numberOfClients;i++)
	//{
		
		Ogre::Vector3 newPenguinClientVector = world->clientPenguins[0]->getVisualPosition();
		//Ogre::Vector3 newPenguinClientVector = Ogre::Vector3(0, 0, 0);
		memcpy(buffer, &newPenguinClientVector[0], 4);
		memcpy(buffer+4, &newPenguinClientVector[1], 4);
		memcpy(buffer+8, &newPenguinClientVector[2], 4);
		
	printf("ClientPosition\n");
	printf("%f\n", newPenguinServerVector[0]);
	printf("%f\n", newPenguinServerVector[1]);
	printf("%f\n", newPenguinServerVector[2]);

		Ogre::Quaternion newPenguinClientQuaternion = world->clientPenguins[0]->getVisualOrientation();
		//Ogre::Quaternion newPenguinClientQuaternion = Ogre::Quaternion(1, 0, 0, 0);
		memcpy(buffer+12, &newPenguinClientQuaternion[0], 4);	
		memcpy(buffer+16, &newPenguinClientQuaternion[1], 4);	
		memcpy(buffer+20, &newPenguinClientQuaternion[2], 4);	
		memcpy(buffer+24, &newPenguinClientQuaternion[3], 4);

		//printf("Before Client %d Send", 0);
		std::cout << "Before Client 0 Send" << std::endl;

		OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 32);
		//printf("After Client %d Send", 0);
		std::cout << "After Client 0 Send" << std::endl;
	//}
		printf("End Server UPDATE\n\n\n\n\n");
    // ===========================================================================

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
