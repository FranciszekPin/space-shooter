#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include "sdlsystem.h"




Enemy::Enemy(SDL_Renderer* renderer, const char* imgSrc)
{
	SDL_Surface* tmpSurface = IMG_Load(imgSrc);
	enemyImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (!enemyImg)
		printf("Failed to create texture\n");
	SDL_FreeSurface(tmpSurface);
	if (!tmpSurface)
		printf("Failed to create surface\n");
	this->renderer = renderer;
	position.x = 0;
	position.y = 0;
	position.h = 64;
	position.w = 64;
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyImg);
}


void Enemy::move()
{
	position.y += velocity;
	if (position.x <= 0)
		moveVector = false;
	if (position.x >= SCREEN_WIDTH - 50)
		moveVector = true;
	if (moveVector == true)
		position.x -= velocity;
	else
		position.x += velocity;
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}