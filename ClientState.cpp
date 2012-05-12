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

	client_controller = new MyController();
	sound_factory = new SoundWrapper();
    sound_factory->playMusic();

	//penguin = new Penguin(m_pSceneMgr, NULL, client_controller);				// Create Player 1's Penguin
	//penguin_two = new Penguin(m_pSceneMgr, NULL, client_controller);								// Create Player 2's Penguin
	ball = new Ball(m_pSceneMgr, NULL, 0, -(room_width/2) + ball_radius, 0);	// Create Ball
	room = new Room(m_pSceneMgr, NULL);											// Create Room
	goal = new Goal(m_pSceneMgr, NULL);											// Create Goal
 
 	//penguin->update(0.1f, client_controller, m_pCamera);
	//penguin_two->update(0.1f, client_controller, NULL);

	std::cout << "Before Client Receive" << std::endl;
	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
	std::cout << "After Client Receive" << std::endl;
	memcpy(&totalNumberPlayers, buffer, 4);

	for(int i = 0; i<totalNumberPlayers; i++)
	{
		penguins.push_back(new Penguin(m_pSceneMgr, NULL, client_controller));
	}

	//ball->update();

	clientID = OgreFramework::getSingletonPtr()->client->GetClientID();

	balls.push_back(ball);
	
	memcpy(sendbuffer, &clientID, 4);

	sendbuffer[4] = '0';
	sendbuffer[5] = '0';
	sendbuffer[6] = '0';
	sendbuffer[7] = '0';
	sendbuffer[8] = '0';
	sendbuffer[9] = '0';
	sendbuffer[10] = '0';
	sendbuffer[11] = '0';
	sendbuffer[12] = '0';
	sendbuffer[13] = '0';
	int blank = 0;
	memcpy(sendbuffer+14, &blank, 4);
	
	std::cout << "Before Client Send Blank Control" << std::endl;
	OgreFramework::getSingletonPtr()->client->SendMessage(sendbuffer, 32);
	std::cout << "After Client Send Blank Control" << std::endl;
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

    // ===========================================================================

	std::cout << "Entered Client UPDATE" << std::endl;
	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
	std::cout << "Received Message from Server" << std::endl;

	int ballNum = 0;
	memcpy(&ballNum, buffer, 4);

	while(balls.size()<ballNum)
	{
		balls.push_back(new Ball(m_pSceneMgr, NULL, 0, 0, 0));
	}
	
	for (int i=0;i<ballNum;i++)
	{
		std::cout << "Ball Number" << ballNum << std::endl;
		OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
		Ogre::Vector3 newballPosition = Ogre::Vector3(0,0,0);
		memcpy(&newballPosition[0], buffer, 4);
		memcpy(&newballPosition[1], buffer+4, 4);
		memcpy(&newballPosition[2], buffer+8, 4);
			
	//printf("BallPosition\n");
/*	std::cout << "BallPosition" << 0 << std::endl;
	printf("%f\n", newballPosition[0]);
	printf("%f\n", newballPosition[1]);
	printf("%f\n", newballPosition[2]);*/

		Ogre::Quaternion newballQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newballQuaternion[0], buffer+12, 4);
		memcpy(&newballQuaternion[1], buffer+16, 4);
		memcpy(&newballQuaternion[2], buffer+20, 4);
		memcpy(&newballQuaternion[3], buffer+24, 4);
		balls[i]->updateAsClient(newballPosition, newballQuaternion);
	}

	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
	int iceNum = 0;
	memcpy(&iceNum, buffer, 4);

	while(icecubes.size()<iceNum)
	{
		icecubes.push_back(Icecube::createNewIcecube(m_pSceneMgr, NULL, Ogre::Vector3(0, -95, 0)));
	}


	std::cout<< "NUMBER OF ICECUBES" << icecubes.size() << std::endl;
	
	for (int i=0;i<iceNum;i++)
	{
		OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
		Ogre::Vector3 newballPosition = Ogre::Vector3(0,0,0);
		memcpy(&newballPosition[0], buffer, 4);
		memcpy(&newballPosition[1], buffer+4, 4);
		memcpy(&newballPosition[2], buffer+8, 4);
			
	//printf("BallPosition\n");
/*	std::cout << "BallPosition" << 0 << std::endl;
	printf("%f\n", newballPosition[0]);
	printf("%f\n", newballPosition[1]);
	printf("%f\n", newballPosition[2]);*/

		Ogre::Quaternion newballQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newballQuaternion[0], buffer+12, 4);
		memcpy(&newballQuaternion[1], buffer+16, 4);
		memcpy(&newballQuaternion[2], buffer+20, 4);
		memcpy(&newballQuaternion[3], buffer+24, 4);
		icecubes[i]->updateAsClient(newballPosition, newballQuaternion);
	}

	OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
	int iglooNum = 0;
	memcpy(&iglooNum, buffer, 4);

	while(igloos.size()<iglooNum)
	{
		igloos.push_back(Igloo::createNewIgloo(m_pSceneMgr, NULL, Ogre::Vector3(40, -room_width/2, 0)));
	}

	
	for (int i=0;i<iglooNum;i++)
	{
		OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
		Ogre::Vector3 newballPosition = Ogre::Vector3(0,0,0);
		memcpy(&newballPosition[0], buffer, 4);
		memcpy(&newballPosition[1], buffer+4, 4);
		memcpy(&newballPosition[2], buffer+8, 4);
			
	//printf("BallPosition\n");
/*	std::cout << "BallPosition" << 0 << std::endl;
	printf("%f\n", newballPosition[0]);
	printf("%f\n", newballPosition[1]);
	printf("%f\n", newballPosition[2]);*/

		Ogre::Quaternion newballQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newballQuaternion[0], buffer+12, 4);
		memcpy(&newballQuaternion[1], buffer+16, 4);
		memcpy(&newballQuaternion[2], buffer+20, 4);
		memcpy(&newballQuaternion[3], buffer+24, 4);
		igloos[i]->updateAsClient(newballPosition, newballQuaternion);
	}
	
	for (int i = 0; i<totalNumberPlayers;i++)
	{
		printf("Before Receive player %d", 0);
		OgreFramework::getSingletonPtr()->client->ReceiveMessage(buffer);
		printf("After Receive player %d", 0);
		Ogre::Vector3 newPenguinServerPosition = Ogre::Vector3(0,0,0);
		memcpy(&newPenguinServerPosition[0], buffer, 4);
		memcpy(&newPenguinServerPosition[1], buffer+4, 4);
		memcpy(&newPenguinServerPosition[2], buffer+8, 4);
/*
	printf("ServerPosition\n");
	printf("%f\n", newPenguinServerPosition[0]);
	printf("%f\n", newPenguinServerPosition[1]);
	printf("%f\n", newPenguinServerPosition[2]);*/

		Ogre::Quaternion newPenguinServerQuaternion = Ogre::Quaternion(1,0,0,0);
		memcpy(&newPenguinServerQuaternion[0], buffer+12, 4);
		memcpy(&newPenguinServerQuaternion[1], buffer+16, 4);
		memcpy(&newPenguinServerQuaternion[2], buffer+20, 4);
		memcpy(&newPenguinServerQuaternion[3], buffer+24, 4);
		printf("Before Update As Client");
		if((i-1) == clientID)
		{
			std::cout <<"Same Client ID" << std::endl;
			penguins[i]->updateAsClient(timeSinceLastFrame, newPenguinServerPosition, newPenguinServerQuaternion, m_pCamera);
		}
		else
		{
			penguins[i]->updateAsClient(timeSinceLastFrame, newPenguinServerPosition, newPenguinServerQuaternion);
		}
		printf("After Update As Client");

	}

	
  	// Update Debug Camera
    if(client_controller->debugCameraOn())
    	OgreFramework::getSingletonPtr()->updateDebugCamera(timeSinceLastFrame, m_pCamera);

    // Update Base Framework
    OgreFramework::getSingletonPtr()->updateOgre(timeSinceLastFrame);


	// TODO - SEND Client Message (just the controller)!!!!!!
	// Player 2's controller

	printf("Before Send\n\n\n\n\n");

	memcpy(sendbuffer, &clientID, 4);

	sendbuffer[4] = (client_controller->left_mouse_button_down) ? '1' : '0';	
	sendbuffer[5] = (client_controller->right_mouse_button_down) ? '1' : '0';
	sendbuffer[6] = (client_controller->left_control_down) ? '1' : '0';
	sendbuffer[7] = (client_controller->right_control_down) ? '1' : '0';
	sendbuffer[8] = (client_controller->up_control_down) ? '1' : '0';
	sendbuffer[9] = (client_controller->bottom_control_down) ? '1' : '0';
	sendbuffer[10] = (client_controller->forward_control_down) ? '1' : '0';
	sendbuffer[11] = (client_controller->backward_control_down) ? '1' : '0';
	sendbuffer[12] = (client_controller->jump_control_down) ? '1' : '0';
	sendbuffer[13] = (client_controller->boost_control_down) ? '1' : '0';

	std::cout << "CLient X movement (Float)" << client_controller->mouse_x_movement << std::endl;
	int mouseX = client_controller->mouse_x_movement;
	std::cout << "CLient X movement (Int)" << mouseX << std::endl;

	memcpy(buffer+14, &(mouseX), 4);

	std::cout << "After Memcpy CLient X movement (Int)" << mouseX << std::endl;

	client_controller->left_mouse_button_down = false;
	client_controller->jump_control_down = false;
	client_controller->right_mouse_button_down = false;
	client_controller->mouse_x_movement = 0;

	OgreFramework::getSingletonPtr()->client->SendMessage(sendbuffer, 32);

	printf("Ended Update\n\n\n\n\n");
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

	OgreFramework::getSingletonPtr()->debugKeyPressed(keyEventRef, m_pCamera);

	return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	client_controller->keyReleased(keyEventRef);
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mouseMoved(const OIS::MouseEvent &evt)
{
	client_controller->mouseMoved(evt);
	// If it's in debug mode, allow the mouse to navigate the scene
	if(!client_controller->thirdPersonCameraOn()){
		m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
		m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
	}
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	client_controller->mousePressed(evt, id);
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
