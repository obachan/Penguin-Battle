//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "ServerMenuState.hpp"
#include "stdlib.h"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ServerMenuState::ServerMenuState()
{
    m_bQuit         = false;
    portNumber      = 0;
    portstringLength    = 0;
    portNumber_text[0] = '\0';
    isPort = true;
    totalNumberOfPlayers = 0;
    m_FrameEvent    = Ogre::FrameEvent();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ServerMenuState::enter()
{

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ServerMenuState...");
 

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "ServerMenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);
 
    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
 
    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
 
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

    portNumberTextBox = OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox(OgreBites::TL_CENTER, "PortNumber", "Enter Port Number Below", 250, 75);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ConnectBtn", "Connect", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedOgreFramework", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);
 
    portNumberTextBox->setText(portNumber_text);

    createScene();

}

void ServerMenuState::createScene()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ServerMenuState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving ServerMenuState...");
 
    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

void ServerMenuState::appendLetter(char letter)
{
	if(portstringLength < 1024)
	{
		portNumber_text[portstringLength++] = letter;
		portNumber_text[portstringLength] = '\0';
	}
}

void ServerMenuState::deleteLetter()
{
	portNumber_text[--portstringLength] = '\0';
}

bool ServerMenuState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
  	switch (keyEventRef.key)
	{
		case OIS::KC_ESCAPE:
		    m_bQuit = true;
		    break;
		case OIS::KC_0:
		    appendLetter('0');
	    	    break;
		case OIS::KC_1:
		    appendLetter('1');
	    	    break;
		case OIS::KC_2:
		    appendLetter('2');
	    	    break;
		case OIS::KC_3:
		    appendLetter('3');
	    	    break;
		case OIS::KC_4:
		    appendLetter('4');
	    	    break;
		case OIS::KC_5:
		    appendLetter('5');
	    	    break;
		case OIS::KC_6:
		    appendLetter('6');
	    	    break;
		case OIS::KC_7:
		    appendLetter('7');
	    	    break;
		case OIS::KC_8:
		    appendLetter('8');
	    	    break;
		case OIS::KC_9:
		    appendLetter('9');
	    	    break;
		case OIS::KC_PERIOD:
		    appendLetter('.');
	    	    break;
		case OIS::KC_BACK:
		    deleteLetter();
		    break;
	    	default:
	    	    break;
	}
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerMenuState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerMenuState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerMenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ServerMenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

void ServerMenuState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
    else if(isPort)
    {
	portNumberTextBox->setText(portNumber_text);
    }
    else
    {
	if(OgreFramework::getSingletonPtr()->server->WaitConnection())
	{
		std::cout << "Connected to Client Number " << totalNumberOfPlayers << "\n\n" << std::endl;
		char buffer[sizeof(int)];
		memcpy(buffer, &totalNumberOfPlayers, sizeof(int));
		OgreFramework::getSingletonPtr()->server->SendMessage(buffer, sizeof(int), totalNumberOfPlayers);
		totalNumberOfPlayers++;
	}
	char blankMessage[2] = "0";
	OgreFramework::getSingletonPtr()->server->Broadcast(blankMessage, 2);
    }
}

void ServerMenuState::connectMenu()
{
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("PortNumber");
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyWidget("ConnectBtn");
	char buff[1024];
	if(gethostname(buff, 1024)==0)
	{
		ip = OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_CENTER, "IPLbl", "Server IP Address is: " + std::string(inet_ntoa(*((struct in_addr *)( struct hostent * )gethostbyname(buff)->h_addr))), 350);
		OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "StartBtn", "Start Game", 250);

	}
	else
		ip = OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_CENTER, "IPLbl", "Error getting IP Address. Please Quit", 250);
}

void ServerMenuState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
        m_bQuit = true;
    else if(button->getName() == "ConnectBtn")
    {
	OgreFramework::getSingletonPtr()->server = new ServerNet(strtol(portNumber_text, NULL, 0));
	connectMenu();
	isPort = false;
    }
    else if(button->getName() == "StartBtn")
    {
	char buffer[] = "start";
	OgreFramework::getSingletonPtr()->server->Broadcast(buffer, 6);
	changeAppState(findByName("ServerState"));
    }
}
