#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include "sdlsystem.h"




Enemy::Enemy(SDL_Renderer *renderer, const char * imgSrc)
{
	SDL_Surface* tmpSurface = IMG_Load(imgSrc);
	enemyImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	if (!enemyImg)
		printf("Failed to create texture\n");
	SDL_FreeSurface(tmpSurface);
	if (!tmpSurface)
		printf("Failed to create surface\n");
	this->renderer = renderer;

	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyImg);
}


void Enemy::move()
{
    position.x = 0;
    position.y = 0;
    position.h = 100;
    position.w = 100;
	SDL_RenderCopy(renderer, enemyImg, NULL, &position);
}