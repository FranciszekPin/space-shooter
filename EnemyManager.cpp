
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


Enemy* EnemyManager::createMonster(const char* imgSrc, int x, int y, int creatureType, int xspeed, int yspeed)
{
	Enemy* enem = new Enemy(renderer, imgSrc, x, y, creatureType, xspeed, yspeed);
	return enem;
}

void EnemyManager::createMultripleMonsters()
{
	srand(time(NULL));
	int randomMonster = rand() % 4;
	Enemy* enemyTmp;
	switch (randomMonster)
	{
	case 0:
		for (int i = 0; i < 6; i++)
		{
			enemyTmp = createMonster("assets/yellow1.bmp", i * 80, -50, randomMonster, 3, 2);
			yellowEnemies.emplace_back(enemyTmp);
		}
		break;
	case 1:
		for (int i = 0; i < 5; i++)
		{
			enemyTmp = createMonster("assets/red1.bmp", i * 120, -50, randomMonster, 3, 1);
			redEnemies.emplace_back(enemyTmp);
		}
		break;
	case 2:
		for (int i = 1; i < 6; i++)
		{
			enemyTmp = createMonster("assets/green1.bmp", i * 100, -50, randomMonster, 3, 1);
			redEnemies.emplace_back(enemyTmp);
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++)
		{
			enemyTmp = createMonster("assets/blue1.bmp", i * 200, i * 50 - 200, randomMonster, 3, 3);
			redEnemies.emplace_back(enemyTmp);
		}
		break;
	}
}

void EnemyManager::moveAll()
{
	if (yellowEnemies.size() > 0) {
		bool changeDirection = false;
		bool direction = true;
		if (yellowEnemies[yellowEnemies.size() - 1]->position.x >= SCREEN_WIDTH - 50) {
			yellowEnemies[yellowEnemies.size() - 1]->moveVector = true;
			changeDirection = true;
			direction = true;
		}
		if (yellowEnemies[0]->position.x <= 0)
		{
			yellowEnemies[0]->moveVector = false;
			changeDirection = true;
			direction = false;
		}

		for (int i = 0; i < yellowEnemies.size(); i++)
		{
			if (changeDirection) {
				if (!direction)
					yellowEnemies[i]->moveVector = yellowEnemies[0]->moveVector;
				else
					yellowEnemies[i]->moveVector = yellowEnemies[yellowEnemies.size() - 1]->moveVector;
			}
			yellowEnemies[i]->move();
		}
	}
	if (redEnemies.size() > 0)
	{
		for (int i = 0; i < redEnemies.size(); i++)
		{
			redEnemies[i]->move();
		}
	}
	if (greenEnemies.size() > 0)
	{
		for (int i = 0; i < greenEnemies.size(); i++)
		{
			greenEnemies[i]->move();
		}
	}
	if (blueEnemies.size() > 0)
	{
		for (int i = 0; i < blueEnemies.size(); i++)
		{
			blueEnemies[i]->move();
		}
	}
}
