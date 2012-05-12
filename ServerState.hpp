//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef SERVER_STATE_HPP
#define SERVER_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
 
#include "OgreFramework.hpp"
#include "World.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||

class ServerState : public AppState
{
public:
	ServerState();
	~ServerState();
 
	DECLARE_APPSTATE_CLASS(ServerState)
 
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

	// Ball*			ball;
	// Room*			room;
	// Paddle*			paddle;
	// Penguin*		penguin;
	//Penguin*		penguin_two;
	//vector<Penguin*> 		clientPenguins;
	//vector<MyController*>		client_controllers;
	// Goal*			goal;

	MyController* 	server_controller;
	MyController* 	client_controller;
	PhysicsWrapper*	physics;
	SoundWrapper* 	sound_factory;
	HUD*			hud;
	World*			world;
	
private:
	ServerNet*					server;
 
	bool						m_bShutdown;

	int numberOfClients;
	
	char buffer[1024];
	char recvbuffer[1024];
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
