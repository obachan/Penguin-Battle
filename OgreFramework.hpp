//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_FRAMEWORK_HPP
#define OGRE_FRAMEWORK_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
 
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
#include <SdkTrays.h>
#include "Physics.hpp"
#include "Controller.hpp"
#include "SoundWrapper.hpp"
#include "HUD.hpp"
#include "Network.hpp"

//#include <CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include <iostream>
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class OgreFramework : public Ogre::Singleton<OgreFramework>, OIS::KeyListener, OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
	OgreFramework();
	~OgreFramework();
 
	bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);
	void updateOgre(double timeSinceLastFrame);
	void updateDebugCamera(double timeSinceLastFrame, Ogre::Camera* camera);
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id); 
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
	bool debugKeyPressed(const OIS::KeyEvent &keyEventRef, Ogre::Camera*)
;
	Ogre::Root*					m_pRoot;
	Ogre::RenderWindow*			m_pRenderWnd;
	Ogre::Viewport*				m_pViewport;
	Ogre::Log*					m_pLog;
	Ogre::Timer*				m_pTimer;
 
	OIS::InputManager*			m_pInputMgr;
	OIS::Keyboard*				m_pKeyboard;
	OIS::Mouse*					m_pMouse;

	OgreBites::SdkTrayManager*	m_pTrayMgr;

	ServerNet*					server;
	ClientNet*					client;
	
private:
	OgreFramework(const OgreFramework&);
	OgreFramework& operator= (const OgreFramework&);

	void getCameraInput();
	void moveCamera(Ogre::Camera* camera);
 
	OgreBites::ParamsPanel* 			mDetailsPanel;
    Ogre::FrameEvent                    m_FrameEvent;
	int									m_iNumScreenShots;
 
	Ogre::Vector3						m_TranslateVector;
	Ogre::Real							m_MoveSpeed; 
	Ogre::Degree						m_RotateSpeed; 
	float								m_MoveScale; 
	Ogre::Degree						m_RotScale;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
