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


Enemy* EnemyManager::createMonster(std::string texID, int x, int y, int creatureType, int xspeed, int yspeed, bool moveVector)
{
	Enemy* enem = new Enemy(renderer, texID, x, y, creatureType, xspeed, yspeed, moveVector);
	return enem;
}

void EnemyManager::spawnMonsters()
{
	if (!redEnemies.size() && !greenEnemies.size() && !yellowEnemies.size() && !blueEnemies.size()) {
		srand(time(NULL));
		int randomMonster = rand() % 4;
		bool greenVector = rand() % 2;
		//Enemy* enemyTmp;
		switch (randomMonster)
		{
		case 0:
			for (int i = 0; i < 6; i++)
			{
				//enemyTmp = createMonster("yellow", i * 80, -50, randomMonster, 3, 2, true);
				//yellowEnemies.emplace_back(enemyTmp);
				yellowEnemies.push_back(std::make_unique<Enemy>(renderer, "yellow", i * 80, -50, randomMonster, 3+ monstersSpeed, 2 + monstersSpeed, true));
			}
			break;
		case 1:
			for (int i = 0; i < 5; i++)
			{
				//enemyTmp = createMonster("red", i * 120, -50, randomMonster, 3, 1, true);
				//redEnemies.emplace_back(enemyTmp);
				redEnemies.push_back(std::make_unique<Enemy>(renderer, "red", i * 120, -50, randomMonster, 3 + monstersSpeed, 1 + monstersSpeed, true));
			}
			break;
		case 2:
			for (int i = 1; i < 7; i++)
			{
				if (i % 2 == 0)
					greenVector = true;
				else
					greenVector = false;
				//enemyTmp = createMonster("green", i * 100, -50, randomMonster, 3, 1, greenVector);
				//greenEnemies.emplace_back(enemyTmp);
				greenEnemies.push_back(std::make_unique<Enemy>(renderer, "green", i * 100, -50, randomMonster, 3 + monstersSpeed, 1 + monstersSpeed, greenVector));
			}
			break;
		case 3:
			for (int i = 0; i < 6; i++)
			{
				//enemyTmp = createMonster("blue", i * 200, i * 50 - 200, randomMonster, 3, 2, true);
				//blueEnemies.emplace_back(enemyTmp);
				blueEnemies.push_back(std::make_unique<Enemy>(renderer, "blue", i * 200, i * 50 - 200, randomMonster, 3 + monstersSpeed, 2 + monstersSpeed, true));
			}
			break;
		}
	}
}

void EnemyManager::eraseAll()
{
	greenEnemies.clear();
	blueEnemies.clear();
	redEnemies.clear();
	yellowEnemies.clear();
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

void EnemyManager::randomShots()
{
	if (shootDelay == shootDelay2) {
		srand(time(NULL));
		if (yellowEnemies.size() > 0)
		{
			int random = 0;
			for (int i = 0; i < yellowEnemies.size(); i++)
			{
				if (rand() % 4 == 2)
					yellowEnemies[i]->shoot();
			}
		}
		if (blueEnemies.size() > 0)
		{
			int random = 0;
			for (int i = 0; i < blueEnemies.size(); i++)
			{
				if (rand() % 3)
					blueEnemies[i]->shoot();
			}
		}
		if (redEnemies.size() > 0)
		{
			int random = 0;
			for (int i = 0; i < redEnemies.size(); i++)
			{
				if (rand() % 4 == 2)
					redEnemies[i]->shoot();
			}
		}
		if (greenEnemies.size() > 0)
		{
			int random = 0;
			for (int i = 0; i < greenEnemies.size(); i++)
			{
				if (rand() % 4 == 2)
					greenEnemies[i]->shoot();
			}
		}
		shootDelay = 0;
	}
	shootDelay += 1;
}

void EnemyManager::destroyInactive()
{
	if (yellowEnemies.size() > 0)
	{
		int random = 0;
		for (int i = 0; i < yellowEnemies.size(); i++) {
			if (!yellowEnemies[i]->active)
				yellowEnemies.erase(yellowEnemies.begin() + i);
		}
	}
	if (blueEnemies.size() > 0)
	{
		for (int i = 0; i < blueEnemies.size(); i++)
		{
			if (!blueEnemies[i]->active)
				blueEnemies.erase(blueEnemies.begin() + i);
		}
	}
	if (redEnemies.size() > 0)
	{
		for (int i = 0; i < redEnemies.size(); i++)
		{
			if (!redEnemies[i]->active)
				redEnemies.erase(redEnemies.begin() + i);
		}
	}
	if (greenEnemies.size() > 0)
	{
		for (int i = 0; i < greenEnemies.size(); i++)
		{
			if (!greenEnemies[i]->active)
				greenEnemies.erase(greenEnemies.begin() + i);
		}
	}
}