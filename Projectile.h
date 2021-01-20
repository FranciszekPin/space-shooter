#pragma once

#include "sdlsystem.h"
#include <string>
#include "GameManager.h"

class Projectile
{
public:
	Projectile(int xpos, int ypos, int scale, int vel);
	~Projectile();
	void update();
	void render(SDL_Texture* texture);

private:
	SDL_Rect srcR = { 0,0,32,32 };
	SDL_Rect sprite;
	int  velocity = 1;//-1 gora
};