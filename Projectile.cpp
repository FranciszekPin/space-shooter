#include "Projectile.h"
#include "constants.h"
#include <string>



Projectile::Projectile(int xpos, int ypos, int scale, int vel)
{
	sprite.x = xpos;
	sprite.y = xpos;
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