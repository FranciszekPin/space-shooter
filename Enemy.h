
#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"
#include <string>

class Enemy
{
private:
	int moveY = 0;
	SDL_Renderer* renderer;
	int prevPosY = 0;
	int prevPosX = 0;
	double angle = 0;
	int orbitX = 0;
	int orbitY = 0;
	int creatureType;
	bool moveVector2 = true;
public:
	bool moveVector = true;

	bool active = true;
	std::string textureID;
	SDL_Rect position, srcR;

	Enemy(SDL_Renderer* r, std::string texID, int x, int y, int creature, int xspeed, int yspeed, bool moveVector);
	static void init();
	void move();
	int  velocityX = 3;
	int	velocityY = 1;
	void deactive();
	void shoot();
	SDL_Rect GetRectangle();
	~Enemy();
};

#endif //SPACE_S