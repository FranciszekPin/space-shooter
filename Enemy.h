

#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"

class Enemy
{
private:
	bool moveVector = true;
	SDL_Rect position;
	SDL_Texture* enemyImg;
public:
	Enemy(SDL_Renderer* renderer, const char imgSrc);
	void move();
	~Enemy();
	int  velocity = 1;
};

#endif //SPACE_S