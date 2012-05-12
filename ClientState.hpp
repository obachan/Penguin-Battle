//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef CLIENT_STATE_HPP
#define CLIENT_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
 
#include "OgreFramework.hpp"
#include "WorldObjectFactory.hpp"
 
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
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef); 
 
	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	Ball*			ball;
	Room*			room;
	Icecube*		icecube;
	Penguin*		penguin;
	Penguin*		penguin_two;
	Goal*			goal;

	MyController* 	client_controller;
	SoundWrapper*	sound_factory;

	vector<WorldObjectAbstract*> 		balls;
	vector<Penguin*> penguins;
	vector<Icecube*> 				icecubes;
	vector<Igloo*> 					igloos; 
	
private:
	bool						m_bShutdown;
	int clientID; 
	int totalNumberPlayers;
	char buffer[1024];
	char sendbuffer[1024];
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
