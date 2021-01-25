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
	SDL_Rect GetRectangle() { return sprite; }
	bool isActive() { return active; }
	void refresh();
	void destroy() { active = false; }

private:
	bool active;
	SDL_Rect srcR;
	SDL_Rect sprite;
	int  velocity = 1;//-1 up
};