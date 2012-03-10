#include "HUD.hpp"
#include <iostream>

int 	HUD::target_score = 5;
float 	HUD::start_timer = 60;

int HUD::HUD_STATUS_PLAYING = 0;
int HUD::HUD_STATUS_WIN = 1;
int HUD::HUD_STATUS_LOSE = 2;

HUD::HUD()
{
	timer = start_timer;
	score = 0;
	hud_status = HUD_STATUS_PLAYING;
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
	//std::cout << "Timer:\t" << timer << "\tScore:\t" << score << std::endl;
	//std::cout << "======" << timeSinceLastFrame* 1000 << "======" << std::endl;
}