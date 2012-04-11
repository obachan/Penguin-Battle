//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "ClientMenuState.hpp"
#include "stdlib.h"

//|||||||||||||||||||||||||||||||||||||||||||||||
 
using namespace Ogre;
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
ClientMenuState::ClientMenuState()
{
    m_bQuit         = false;
    portNumber      = 0;
    portstringLength    = 0;
    portNumber_text[0] = '\0';
    ipStringLength = 0;
    ip_text[0] = '\0';
    isPort = false;
    isIP = false;
    m_FrameEvent    = Ogre::FrameEvent();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ClientMenuState::enter()
{

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering ClientMenuState...");
 

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "ClientMenuSceneMgr");
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

    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "PortBtn", "Click to Enter Port Number", 250);
    portNumberTextBox = OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox(OgreBites::TL_CENTER, "PortNumber", "Enter Port Number Below", 250, 75);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ServerIPBtn", "Click to Enter IP Address of Server", 250);
    ipAddressTextBox = OgreFramework::getSingletonPtr()->m_pTrayMgr->createTextBox(OgreBites::TL_CENTER, "IPAddress", "Enter Server IP Address Below", 250, 75);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ConnectBtn", "Connect", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedOgreFramework", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "MenuLbl", "Menu mode", 250);
 
    portNumberTextBox->setText(portNumber_text);
    ipAddressTextBox->setText(ip_text);

    createScene();

}

void ClientMenuState::createScene()
{
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void ClientMenuState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving ClientMenuState...");
 
    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
 
    OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

void ClientMenuState::appendLetter(char letter)
{
	if(isPort)
	{
		if(portstringLength < 1024)
		{
			portNumber_text[portstringLength++] = letter;
			portNumber_text[portstringLength] = '\0';
		}
	}
	else if(isIP)
	{
		
		if(ipStringLength < 1024)
		{
			ip_text[ipStringLength++] = letter;
			ip_text[ipStringLength] = '\0';
		}
	}
}

void ClientMenuState::deleteLetter()
{
	if(isPort)
	{
		portNumber_text[--portstringLength] = '\0';
	}
	else if(isIP)
	{
		ip_text[--ipStringLength] = '\0';
	}
}

bool ClientMenuState::keyPressed(const OIS::KeyEvent &keyEventRef)
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
 
    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientMenuState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientMenuState::mouseMoved(const OIS::MouseEvent &evt)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientMenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
    return true;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
bool ClientMenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
    return true;
}

void ClientMenuState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
    else
    {
	portNumberTextBox->setText(portNumber_text);
	ipAddressTextBox->setText(ip_text);
    }

}

void ClientMenuState::buttonHit(OgreBites::Button *button)
{
    if(button->getName() == "ExitBtn")
        m_bQuit = true;
    else if(button->getName() == "PortBtn")
    {
	isPort = true;
	isIP = false;
    }
    else if(button->getName() == "ServerIPBtn")
    {
	isPort = false;
	isIP = true;
    }
    else if(button->getName() == "ConnectBtn")
    {
	OgreFramework::getSingletonPtr()->client = new ClientNet(strtol(portNumber_text, NULL, 0), ip_text);	
	changeAppState(findByName("ClientState"));
    }
}
