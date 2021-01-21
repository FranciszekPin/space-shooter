
#include <stdio.h>
#include "EnemyManager.h"

#include "constants.h"
#include <string>
#include "sdlsystem.h"
#include <string>
#include <cstdlib>
#include <ctime>





EnemyManager::EnemyManager(SDL_Renderer* r)
{
	renderer = r;
}


Enemy EnemyManager::createMonster(const char* imgSrc, int i)
{
	Enemy enem(renderer, imgSrc, i * 64, 0, 0);
	return enem;
}

void EnemyManager::createMultripleMonsters()
{
	srand(time(NULL));
	int randomMonster = rand() % 2;
	for (int i = 0; i < 13; i++)
	{
		if (randomMonster == 0)
		{
			Enemies.push_back(createMonster("assets/blue1.bmp", i));
		}
		else
		{
			Enemies.push_back(createMonster("assets/yellow1.bmp", i));
		}
	}
}

void EnemyManager::moveAll()
{
	for (auto& it : Enemies)
	{
		it.move();
		SDL_RenderCopy(renderer, it.enemyImg, NULL, &it.position);
	}
}
