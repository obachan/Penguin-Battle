#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>

class HUD 
{
public:
	HUD(OgreBites::SdkTrayManager*);
	~HUD();

	void update(double, bool);
	void reset();
	void resume();

	int				score;
	float			timer;
	int				hud_status;

	static int		target_score;
	static float	start_timer;

	static int		HUD_STATUS_PLAYING;
	static int		HUD_STATUS_WIN;
	static int		HUD_STATUS_LOSE;

private:
	OgreBites::SdkTrayManager*	mTrayMgr;
	OgreBites::ParamsPanel* 	mDetailsPanel;
};
