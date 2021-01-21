
#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include "sdlsystem.h"
#include <string>



Enemy::Enemy(SDL_Renderer* renderer, const char* imgSrc, int x, int y, int creature)
{
	creatureType = creature;
	SDL_Surface* tmpSurface = IMG_Load(imgSrc);
	enemyImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (!enemyImg)
		printf("Failed to create texture\n");
	SDL_FreeSurface(tmpSurface);
	if (!tmpSurface)
		printf("Failed to create surface\n");
	this->renderer = renderer;
	position.x = x;
	position.y = y;
	position.h = 48;
	position.w = 48;
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}

void Enemy::move()
{
	if (moveY == 3)
	{
		position.y += velocityY;
		moveY = 0;
	}
	else
	{
		moveY++;
	}
	if (position.x <= 0)
		moveVector = false;
	if (position.x >= SCREEN_WIDTH - 50)
		moveVector = true;
	if (moveVector == true)
		position.x -= velocityX;
	else
		position.x += velocityX;

}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyImg);
}
