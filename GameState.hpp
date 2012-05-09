//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
 
#include "OgreFramework.hpp"
#include "World.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public AppState
{
public:
	GameState();
	~GameState();
 
	DECLARE_APPSTATE_CLASS(GameState)
 
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

	World* 					world;

	// ===============================
	// World Object
	// ===============================
	WorldObjectFactory* 	worldObjectFactory;

	//Ball*					ball;
	//Room*					room;
	//Paddle*					paddle;
	//Penguin*				penguin;
	//Goal*					goal;
	//Terrain*				terrain;

	std::vector<Ball*> 		ballList;

	OgreBites::ParamsPanel* mDetailsPanel;

	PhysicsWrapper*			physics;
	MyController* 			controller;
	SoundWrapper*			soundFactory;
	HUD*					hud;
	
private: 
	bool					m_bShutdown;

	// ========================
	// Parameters to control debug camera
	// ========================

};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
