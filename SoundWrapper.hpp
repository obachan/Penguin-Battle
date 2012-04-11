
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

class SoundWrapper 
{
public:
	SoundWrapper();
	~SoundWrapper();
 

	void playMusic();
	void playJumpSoundEffect();
	
	void musicDone();
private:
	bool	is_music_playing;

	Mix_Chunk*	jump_sound;
	Mix_Music*	music;
		
};