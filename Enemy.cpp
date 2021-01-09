#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include"sdlsystem.h"




void Enemy::loadIMG(SDL_Renderer* renderer, const char* img_src)
{
	SDL_Surface* tmpSurface = IMG_Load(img_src);
	enemyIMG = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Enemy::move(SDL_Renderer* renderer, const char* img_src)
{

	loadIMG(renderer, img_src);
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