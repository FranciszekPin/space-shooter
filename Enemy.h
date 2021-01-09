

#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"

class Enemy
{
public:

	SDL_Rect position;
	SDL_Texture* enemyIMG;
	void loadIMG(SDL_Renderer* renderer, const char* img_src);
	void move(SDL_Renderer* renderer, const char* img_src);
	int  velocity = 1;
	bool movevector = true;
};

#endif //SPACE_S