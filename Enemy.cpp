
#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>
#include "sdlsystem.h"
#include "math.h"
#include "Projectile.h"
#include "CollisionManager.h"
#include "MusicManager.h"
#include "AssetManager.h"

MusicManager* jukebox2 = new MusicManager();
AssetManager* assetManagerE = new AssetManager();

Enemy::Enemy(SDL_Renderer* r, std::string texID, int x, int y, int creature, int xspeed, int yspeed, bool V)
{
	moveVector = V;
	this->renderer = r;
	creatureType = creature;
	textureID = texID;

	if (creature == 1) {
		prevPosY = y + 100;
		prevPosX = x;
	}
	if (creature == 2)
	{
		orbitX = x;
		orbitY = y;
	}
	srcR.x = srcR.y = 0;
	srcR.w = 21;
	srcR.h = 15;
	position.x = x;
	position.y = y;
	position.h = srcR.h * ENEMY_SCALE;
	position.w = srcR.w * ENEMY_SCALE;


	velocityX = xspeed;
	velocityY = yspeed;
	jukebox2->init();
}

void Enemy::init()
{
	assetManagerE->AddTexture("blue", "assets/blue_anim.png");
	assetManagerE->AddTexture("yellow", "assets/yellow_anim.png");
	assetManagerE->AddTexture("green", "assets/green_anim.png");
	assetManagerE->AddTexture("red", "assets/red_anim.png");
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

		if (moveVector)
			angle -= 0.05;
		else
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

	srcR.x = srcR.w * static_cast<int>((SDL_GetTicks() / 200) % 2);
	SDL_RenderCopy(renderer, assetManagerE->GetTexture(textureID), &srcR, &position);
}

void Enemy::deactive()
{
	active = false;
}


void Enemy::shoot()
{
	jukebox2->playAlienShot();
	Projectile* tmp = new Projectile(position.x + (position.w / 2 - 5/*adjust this if needed*/), position.y + position.h - 10/*adjust this if needed*/, ENEMY_PROJECTILE_SCALE, ENEMY_PROJECTILE_SPEED);
	CollisionManager::add(tmp, 1);
}
Enemy::~Enemy()
{}

SDL_Rect Enemy::GetRectangle()
{
	return position;
}