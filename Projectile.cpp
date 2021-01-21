#include "Projectile.h"
#include "constants.h"
#include <string>



Projectile::Projectile(int xpos, int ypos, int scale, int vel)
{
	active = true;
	srcR.x = srcR.y = 0;
	if (vel < 0)
	{
		srcR.w = 5;
		srcR.h = 15;
	}
	else
	{
		srcR.w = 9;
		srcR.h = 30;
	}
	sprite.x = xpos;
	sprite.y = ypos;
	sprite.w = srcR.w * scale;
	sprite.h = srcR.h * scale;
	velocity = vel;
	
}

Projectile::~Projectile()
{}

void Projectile::update()
{
	sprite.y += velocity;
}

void Projectile::render(SDL_Texture* texture)
{
	SDL_RenderCopy(GameManager::renderer, texture, &srcR, &sprite);
}