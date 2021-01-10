#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include"sdlsystem.h"




Enemy::Enemy(SDL_Renderer *renderer, const char imgSrc)
{
	SDL_Surface* tmpSurface = IMG_Load(imgSrc);
	enemyIMG = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

Enemy::~Enemy()
{
	SDL_DestroyTexture(enemyImg);
}


void Enemy::move()
{
	position.y += velocity;
	if (position.x <= 0)
		movevector = false;
	if (position.x >= SCREEN_WIDTH - 50)
		movevector = true;
	if (movevector == true)
		position.x -= 4 * velocity;
	else
		position.x += 4 * velocity;
	SDL_RenderCopy(renderer, enemyIMG, NULL, &position);
}