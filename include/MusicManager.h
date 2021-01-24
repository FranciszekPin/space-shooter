#pragma once
#include "sdlsystem.h"
#include <stdio.h>

class MusicManager
{
public:
	void init();
	void playShot();
	void playAlienShot();
	void playExplosion();
private:
	Mix_Music *background;
	Mix_Chunk *alienshot;
	Mix_Chunk *explosion;
	 Mix_Chunk *smallshot;
};