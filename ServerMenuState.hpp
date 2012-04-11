//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef SERVER_MENU_STATE_HPP
#define SERVER_MENU_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "AppState.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class ServerMenuState : public AppState
{
public:
    	ServerMenuState();
 
	DECLARE_APPSTATE_CLASS(ServerMenuState)
 
	void enter();
	void createScene();
	void exit();
 
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
 
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
 
	void buttonHit(OgreBites::Button* button);
 
	void update(double timeSinceLastFrame);
 
private:
	bool m_bQuit;
	int portNumber;
	char portNumber_text[1025];
	int portstringLength;
	bool isPort;
	void appendLetter(char);
	void deleteLetter();
	void connectMenu();
	OgreBites::TextBox *portNumberTextBox;
	OgreBites::Label *ip;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
