#include "OgreFramework.hpp"
 
#include <iostream>

using namespace Ogre; 
 
template<> OgreFramework* Ogre::Singleton<OgreFramework>::ms_Singleton = 0;
 
OgreFramework::OgreFramework()
{
	m_MoveSpeed				= 0.1f;
	m_RotateSpeed		    = 0.3f;
 
	m_iNumScreenShots	    = 0;
 
	m_pRoot					= 0;
	m_pRenderWnd		    = 0;
	m_pViewport				= 0;
	m_pLog					= 0;
	m_pTimer				= 0;
 
	m_pInputMgr				= 0;
	m_pKeyboard				= 0;
	m_pMouse				= 0;
 
    m_pTrayMgr              = 0;
    m_FrameEvent            = Ogre::FrameEvent();
}

bool OgreFramework::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
	Ogre::LogManager* logMgr = new Ogre::LogManager();
 
	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);
 
	m_pRoot = new Ogre::Root();
 
	if(!m_pRoot->showConfigDialog())
		return false;
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
 
	m_pViewport = m_pRenderWnd->addViewport(0);
	m_pViewport->setBackgroundColour(ColourValue(0.8f, 0.7f, 0.6f, 1.0f));


	size_t hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
 
	paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
 
	m_pInputMgr = OIS::InputManager::createInputSystem(paramList);
 
    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
	m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));
 
	m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
	m_pMouse->getMouseState().width	 = m_pRenderWnd->getWidth();
 
	if(pKeyListener == 0)
		m_pKeyboard->setEventCallback(this);
	else
		m_pKeyboard->setEventCallback(pKeyListener);
 
	if(pMouseListener == 0)
		m_pMouse->setEventCallback(this);
	else
		m_pMouse->setEventCallback(pMouseListener);
 
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
        cf.load("resources.cfg");
 
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
	m_pTimer = new Ogre::Timer();
	m_pTimer->reset();
 
	m_pTrayMgr = new OgreBites::SdkTrayManager("TrayMgr", m_pRenderWnd, m_pMouse, this);
    m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	
    m_pTrayMgr->hideCursor();
 
	m_pRenderWnd->setActive(true);
 
	return true;
}

OgreFramework::~OgreFramework()
{
    if(m_pInputMgr) OIS::InputManager::destroyInputSystem(m_pInputMgr);
    if(m_pTrayMgr)  delete m_pTrayMgr;
    if(m_pRoot)     delete m_pRoot;
}

bool OgreFramework::keyPressed(const OIS::KeyEvent &keyEventRef)
{ 
	return true;
}

bool OgreFramework::keyReleased(const OIS::KeyEvent &keyEventRef)
{	
	return true;
}

bool OgreFramework::mouseMoved(const OIS::MouseEvent &evt)
{
	return true;
}

bool OgreFramework::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}
 
bool OgreFramework::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}


bool OgreFramework::debugKeyPressed(const OIS::KeyEvent &keyEventRef, Ogre::Camera* camera)
{ 
	if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ)){
		m_pRenderWnd->writeContentsToTimestampedFile("BOF_Screenshot_", ".png");
		return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_M)){
		static int mode = 0;
 
		if(mode == 2){
			camera->setPolygonMode(PM_SOLID);
			mode = 0;
		}
		else if(mode == 0){
			 camera->setPolygonMode(PM_WIREFRAME);
			 mode = 1;
		}
		else if(mode == 1){
			camera->setPolygonMode(PM_POINTS);
			mode = 2;
		}
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_O)){
		if(m_pTrayMgr->isLogoVisible())	{
            m_pTrayMgr->hideFrameStats();
        }
        else {
        	m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
        }
	}

	return true;
}


void OgreFramework::updateOgre(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
	m_pTrayMgr->adjustTrays();
}

void OgreFramework::updateDebugCamera(double timeSinceLastFrame, Ogre::Camera* camera)
{
	m_MoveScale = 15 * m_MoveSpeed   * (float)timeSinceLastFrame;
	m_RotScale  = 15 * m_RotateSpeed * (float)timeSinceLastFrame;
 
	m_TranslateVector = Vector3::ZERO;

	getCameraInput();
	moveCamera(camera);
}

//=========================
// Private Methods
//=========================

void OgreFramework::getCameraInput()
{

	if(m_pKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;
 
	if(m_pKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;
}

void OgreFramework::moveCamera(Ogre::Camera* camera)
{
	if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)) 
		camera->moveRelative(m_TranslateVector);
	else
		camera->moveRelative(m_TranslateVector / 10);
}
