#include "OgreFramework.hpp"
 
#include <iostream>

using namespace Ogre; 
 
template<> OgreFramework* Ogre::Singleton<OgreFramework>::ms_Singleton = 0;
 
OgreFramework::OgreFramework()
{
	m_MoveSpeed				= 0.1f;
	m_RotateSpeed		    = 0.3f;
 
	m_bShutDownOgre		    = false;
	m_iNumScreenShots	    = 0;
 
	m_pRoot					= 0;
	m_pSceneMgr				= 0;
	m_pRenderWnd		    = 0;
	m_pCamera				= 0;
	m_pViewport				= 0;
	m_pLog					= 0;
	m_pTimer				= 0;
 
	m_pInputMgr				= 0;
	m_pKeyboard				= 0;
	m_pMouse				= 0;
 
    m_pTrayMgr              = 0;
    m_FrameEvent            = Ogre::FrameEvent();

    is_gamestate 			= false;
}

bool OgreFramework::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
	Ogre::LogManager* logMgr = new Ogre::LogManager();
	
	//physics = new PhysicsWrapper();
	controller = new MyController();
	sounds = new SoundWrapper();
	hud = new HUD();
 
	m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
	m_pLog->setDebugOutputEnabled(true);
 
	m_pRoot = new Ogre::Root();
 
	if(!m_pRoot->showConfigDialog())
		return false;
	m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
 

 /*
	m_pSceneMgr = m_pRoot->createSceneManager(ST_GENERIC, "SceneManager");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));
 
	m_pCamera = m_pSceneMgr->createCamera("Camera");
	m_pCamera->setPosition(Vector3(0, -40, 125));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);
 
	m_pViewport = m_pRenderWnd->addViewport(m_pCamera);
	m_pViewport->setBackgroundColour(ColourValue(0.8f, 0.7f, 0.6f, 1.0f));
 
	m_pCamera->setAspectRatio(Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight()));
 
	m_pViewport->setCamera(m_pCamera);
*/
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
    //m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);

	Ogre::StringVector items;
	items.push_back("Time Left      ");
    items.push_back("Target Score  ");
    items.push_back("Score          ");
    items.push_back("Status         ");
 
  	mDetailsPanel = m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(0, "60"); 	//Set initial Timer Value
    mDetailsPanel->setParamValue(1, "5");	//Set Target Score Value
    mDetailsPanel->setParamValue(2, "0");	//Set initial Score Value
    mDetailsPanel->setParamValue(3, "Playing");	//Set initial Score Value
	mDetailsPanel->show();	

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

	// This code was initially here

	/*
	if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
			m_bShutDownOgre = true;
			return true;
	}
	*/
 
	if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ))
	{
		m_pRenderWnd->writeContentsToTimestampedFile("BOF_Screenshot_", ".png");
		return true;
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_M))
	{
		static int mode = 0;
 
		if(mode == 2)
		{
			m_pCamera->setPolygonMode(PM_SOLID);
			mode = 0;
		}
		else if(mode == 0)
		{
			 m_pCamera->setPolygonMode(PM_WIREFRAME);
			 mode = 1;
		}
		else if(mode == 1)
		{
			m_pCamera->setPolygonMode(PM_POINTS);
			mode = 2;
		}
	}
 
	if(m_pKeyboard->isKeyDown(OIS::KC_O))
	{
		if(m_pTrayMgr->isLogoVisible())
       		{
        	    	//m_pTrayMgr->hideLogo();
        	    	m_pTrayMgr->hideFrameStats();
        	}
        	else
        	{
        		//m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        		m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
        	}
	}

	return true;
}

bool OgreFramework::keyReleased(const OIS::KeyEvent &keyEventRef)
{	

	return true;
}

bool OgreFramework::mouseMoved(const OIS::MouseEvent &evt)
{
	m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
	m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
 
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

void OgreFramework::updateOgre(double timeSinceLastFrame)
{
	m_MoveScale = 15 * m_MoveSpeed   * (float)timeSinceLastFrame;
	m_RotScale  = 15 * m_RotateSpeed * (float)timeSinceLastFrame;
 
	m_TranslateVector = Vector3::ZERO;
	if(is_gamestate){

 		// Get input for Camera
		getCameraInput();
		moveCamera();


/*
		if (timeSinceLastFrame!=0)
		{
	 		physics->stepPhysics(timeSinceLastFrame, 5);
		
		}
*/		
		m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	    m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
		m_pTrayMgr->adjustTrays();



		/*
		if (!m_pTrayMgr->isDialogVisible())
	    {
	       	//mCameraMan->frameRenderingQueued(m_FrameEvent);
	    	
	    	// if dialog isn't up, then update the camera
	    	// if details panel is visible, then update its contents

	    	if (mDetailsPanel->isVisible())
	       	{
				//Change Score and Timer Value each Frame
	       	    mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(hud->timer));
	       	    mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(hud->score));


	       	    std::string hud_status_message;
	       	    if(hud->hud_status == hud->HUD_STATUS_PLAYING)
	       	    	hud_status_message = "Playing";
	       	    else if(hud->hud_status == hud->HUD_STATUS_WIN)
	       	    	hud_status_message = "You Win";
	       	    else if(hud->hud_status == hud->HUD_STATUS_LOSE)
	       	    	hud_status_message = "You Lose";


	       	    mDetailsPanel->setParamValue(3, hud_status_message);    	
	       	}
	    }
	    */
	}
}

void OgreFramework::moveCamera()
{
	if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)) 
		m_pCamera->moveRelative(m_TranslateVector);
	else
		m_pCamera->moveRelative(m_TranslateVector / 10);
}

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
