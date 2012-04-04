//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreApp.hpp"
 
#include "MenuState.hpp"
//#include "GameState.hpp"
#include "PauseState.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
OgreApp::OgreApp()
{
	m_pAppStateManager = 0;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
OgreApp::~OgreApp()
{
	delete m_pAppStateManager;
    delete OgreFramework::getSingletonPtr();
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
void OgreApp::startDemo()
{
	new OgreFramework();
	if(!OgreFramework::getSingletonPtr()->initOgre("OgreFramework", 0, 0))
		return;
 
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");
 
	m_pAppStateManager = new AppStateManager();
 
	MenuState::create(m_pAppStateManager, "MenuState");
	//GameState::create(m_pAppStateManager, "GameState");
    PauseState::create(m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||