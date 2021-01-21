
#ifndef SPACE_SHOOTER_ENEMYMANAGER_H
#define SPACE_SHOOTER_ENEMYMANAGER_H
#include "sdlsystem.h"
#include "Enemy.h"
#include <vector>

using namespace std;
class EnemyManager
{
private:

	SDL_Renderer* renderer;
public:
	Enemy createMonster(const char* imgSrc, int i);
	EnemyManager(SDL_Renderer* r);
	vector<Enemy> Enemies;
	void moveAll();
	void createMultripleMonsters();
};

#endif //SPACE_S