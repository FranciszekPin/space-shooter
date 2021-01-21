#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include "sdlsystem.h"
#include <string>
#include "math.h"


Enemy::Enemy(SDL_Renderer* r, const char* imgSrc, int x, int y, int creature, int xspeed, int yspeed)
{
	this->renderer = r;
	creatureType = creature;
	SDL_Surface* tmpSurface = IMG_Load(imgSrc);
	enemyImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (!enemyImg)
		printf("Failed to create texture\n");
	SDL_FreeSurface(tmpSurface);
	if (!tmpSurface)
		printf("Failed to create surface\n");
	if (creature == 1) {
		prevPosY = y + 100;
		prevPosX = x;
	}
	if (creature == 2)
	{
		orbitX = x;
		orbitY = y;
	}
	position.x = x;
	position.y = y;
	position.h = 48;
	position.w = 48;
	velocityX = xspeed;
	velocityY = yspeed;
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}

void Enemy::move()

{
	switch (creatureType) {
	case 0:
		if (moveY == 3)
		{
			position.y += velocityY;
			moveY = 0;
		}
		else
		{
			moveY++;
		}
		if (moveVector)
			position.x -= velocityX;
		else
			position.x += velocityX;
		break;
	case 1:
		if (moveVector2)
			position.x += velocityX;
		else
			position.x -= velocityX;
		if (moveVector) {
			position.y += velocityY;
			if (position.y - prevPosY > 150)
			{

				moveVector = false;
			}
		}
		else {
			position.y -= velocityY;
			if (position.y == prevPosY)
			{
				prevPosY = position.y + 100;
				moveVector = true;
			}
		}
		if (prevPosX == position.x)
		{
			moveVector2 = true;
		}
		else if ((position.x - prevPosX) > 100 || (position.x >= SCREEN_WIDTH - 40))
		{
			moveVector2 = false;
		}
		break;
	case 2:

		angle += 0.05;
		if (moveY == 3)
		{
			orbitY += velocityY;
			moveY = 0;
		}
		else
		{
			moveY++;
		}
		position.x = orbitX + 70 * cos(angle);
		position.y = orbitY + 70 * sin(angle);
		break;
	case 3:
		if (moveY == 3)
		{
			position.y += velocityY;
			moveY = 0;
		}
		else
		{
			moveY++;
		}
		if (position.x >= SCREEN_WIDTH - 40)
			moveVector = true;
		else if (position.x <= 0)
			moveVector = false;
		if (moveVector)
			position.x -= velocityX;
		else
			position.x += velocityX;
		break;
	}
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}

void Enemy::deactive()
{
	active = false;
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyImg);
}
