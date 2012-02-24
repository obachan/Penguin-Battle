//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreFramework.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class DemoApp : public OIS::KeyListener
{
public:
	DemoApp();
	~DemoApp();
 
	void startDemo();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
private:
        void setupDemoScene();
	void runDemo();
 
	void createSphere(Ogre::Real _rCoordX, Ogre::Real _rCoordY, Ogre::Real _rCoordZ,
						Ogre::Real _rScaleFactor, Ogre::String _strObjName);

	Ogre::SceneNode*			m_pOgreHeadNode;
	Ogre::Entity*				m_pOgreHeadEntity;
 
	bool					m_bShutdown;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif 
 
//|||||||||||||||||||||||||||||||||||||||||||||||
