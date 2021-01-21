
#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"

class Enemy
{
private:
	bool moveVector = true;
	int moveY = 0;


	SDL_Renderer* renderer;
	int creatureType;
public:
	SDL_Texture* enemyImg;
	SDL_Rect position;
	Enemy(SDL_Renderer* renderer, const char* imgSrc, int x, int y, int creatureType);
	void move();
	~Enemy();
	int  velocityX = 3;
	int	velocityY = 1;
};

#endif //SPACE_SE_S