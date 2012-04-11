//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreApp.hpp"
 
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "MultiplayerMenuState.hpp"
#include "ClientMenuState.hpp"
#include "ServerMenuState.hpp"
 
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
	GameState::create(m_pAppStateManager, "GameState");
	PauseState::create(m_pAppStateManager, "PauseState");
	MultiplayerMenuState::create(m_pAppStateManager, "MultiplayerMenuState");
	ClientMenuState::create(m_pAppStateManager, "ClientMenuState");
	ServerMenuState::create(m_pAppStateManager, "ServerMenuState");

//std::cout << "SEG FAULT" << std::endl;
	m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
//std::cout << "SEG FAULT" << std::endl;
}
 
//|||||||||||||||||||||||||||||||||||||||||||||||
