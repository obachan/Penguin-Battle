//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef CLIENT_MENU_STATE_HPP
#define CLIENT_MENU_STATE_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#include "AppState.hpp"
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
class ClientMenuState : public AppState
{
public:
    	ClientMenuState();
 
	DECLARE_APPSTATE_CLASS(ClientMenuState)
 
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
	char ip_text[1025];
	int ipStringLength;
	bool isPort;
	bool isIP;
	void appendLetter(char);
	void deleteLetter();
	OgreBites::TextBox *portNumberTextBox;
	OgreBites::TextBox *ipAddressTextBox;
};
 
//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||
