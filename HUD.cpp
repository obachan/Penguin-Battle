#include "HUD.hpp"
#include <iostream>

int HUD::target_score = 5;
float HUD::start_timer = 60;

int HUD::HUD_STATUS_PLAYING = 0;
int	HUD::HUD_STATUS_WIN = 1;
int HUD::HUD_STATUS_LOSE = 2;

HUD::HUD(OgreBites::SdkTrayManager* trayMgr)
{
	mTrayMgr = trayMgr;
	
	reset();
}

//|||||||||||||||||||||||||||||||||||||||||||||||
 
HUD::~HUD()
{
}

void HUD::update(double timeSinceLastFrame, bool scored)
{


	if(hud_status == HUD_STATUS_PLAYING)
	{
		timer -= timeSinceLastFrame / 1000.0;
		if(scored)
			score++;

		if(timer < 0){
			timer = 0;
			if(score > target_score)
				hud_status = HUD_STATUS_WIN;
			else
				hud_status = HUD_STATUS_LOSE;

		}
	}
	
  	if (mDetailsPanel->isVisible())
   	{
		//Change Score and Timer Value each Frame
   	    mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(timer));
   	    mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(score));

   	    std::string hud_status_message;
   	    if(hud_status == HUD::HUD_STATUS_PLAYING)
   	    	hud_status_message = "Playing";
  	    else if(hud_status == HUD::HUD_STATUS_WIN)
  	    	hud_status_message = "You Win";
   	    else if(hud_status == HUD::HUD_STATUS_LOSE)
   	    	hud_status_message = "You Lose";

   	    mDetailsPanel->setParamValue(3, hud_status_message);    	
  	}
}

void HUD::reset()
{
	timer = start_timer;
	score = 0;
	hud_status = HUD_STATUS_PLAYING;

	Ogre::StringVector items;
	items.push_back("Time Left      ");
    items.push_back("Target Score  ");
    items.push_back("Score          ");
    items.push_back("Status         "); 

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(0, "60"); 	//Set initial Timer Value
    mDetailsPanel->setParamValue(1, "5");	//Set Target Score Value
    mDetailsPanel->setParamValue(2, "0");	//Set initial Score Value
    mDetailsPanel->setParamValue(3, "Playing");	//Set initial Score Value
	mDetailsPanel->show();	
}

void HUD::resume()
{
	Ogre::StringVector items;
	items.push_back("Time Left      ");
    items.push_back("Target Score  ");
    items.push_back("Score          ");
    items.push_back("Status         "); 

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_TOPRIGHT, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(0, "60"); 	//Set initial Timer Value
    mDetailsPanel->setParamValue(1, "5");	//Set Target Score Value
    mDetailsPanel->setParamValue(2, "0");	//Set initial Score Value
    mDetailsPanel->setParamValue(3, "Playing");	//Set initial Score Value
	mDetailsPanel->show();	
}