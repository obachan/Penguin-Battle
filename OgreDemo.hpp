//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreFramework.hpp"
#include "WorldObjects.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||

class DemoApp : public OIS::KeyListener, public OIS::MouseListener
{
public:
	DemoApp();
	~DemoApp();
 
	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef); 
	bool mouseMoved(const OIS::MouseEvent &arg );

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
