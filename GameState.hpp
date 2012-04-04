//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreFramework.hpp"
#include "WorldObjects.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public OIS::KeyListener
{
public:
	GameState();
	~GameState();
 
	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef); 

	Ball 		*ball;
	Room 		*room;
	Paddle		*paddle;
	Penguin		*penguin;
	Goal		*goal;

	//Ball 		*test_ball;

	bool		pause_state;
	
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