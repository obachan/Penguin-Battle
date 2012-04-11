//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef CLIENT_STATE_HPP
#define CLIENT_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
 
#include "OgreFramework.hpp"
#include "GameState.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||

class ClientState : public AppState
{
public:
	ClientState();
	~ClientState();
 
	DECLARE_APPSTATE_CLASS(ClientState)
 
	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();
	void update(double timeSinceLastFrame);

	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef); 
 
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	Ball 		*ball;
	Room 		*room;
	Paddle		*paddle;
	Penguin		*penguin;
	Penguin		*penguin_two;
	Goal		*goal;
	
	bool		pause_state;

	OgreBites::ParamsPanel* mDetailsPanel;
	MyController* controller_two;
	
private:
    void setupDemoScene();
	void runDemo();

	Ogre::SceneNode*			m_pOgreHeadNode;
	Ogre::Entity*				m_pOgreHeadEntity;
 
	bool						m_bShutdown;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
