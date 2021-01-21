
#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"

class Enemy
{
private:
	int moveY = 0;
	SDL_Renderer* renderer;
public:
	int creatureType;
	bool moveVector = true;
	bool moveVector2 = true;
	bool active = true;
	SDL_Texture* enemyImg;
	SDL_Rect position;
	int prevPosY = 0;
	int prevPosX = 0;
	double angle = 0;
	int orbitX = 0;
	int orbitY = 0;
	Enemy(SDL_Renderer* r, const char* imgSrc, int x, int y, int creature, int xspeed, int yspeed);
	void move();
	~Enemy();
	int  velocityX = 3;
	int	velocityY = 1;
	void deactive();
};

#endif //SPACE_S