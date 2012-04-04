//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "OgreFramework.hpp"
#include "AppStateManager.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class OgreApp
{
public:
	OgreApp();
	~OgreApp();
 
	void startDemo();
 
private:
	AppStateManager*	m_pAppStateManager;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||