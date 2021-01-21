
#ifndef SPACE_SHOOTER_ENEMYMANAGER_H
#define SPACE_SHOOTER_ENEMYMANAGER_H
#include "sdlsystem.h"
#include "Enemy.h"
#include <vector>
#include <memory>
using namespace std;
class EnemyManager
{
private:

	SDL_Renderer* renderer;
public:
	Enemy* createMonster(const char* imgSrc, int x, int y, int creatureType, int xspeed, int yspeed);
	EnemyManager(SDL_Renderer* r);
	vector<unique_ptr<Enemy> > redEnemies;
	vector<unique_ptr<Enemy> > blueEnemies;
	vector<unique_ptr<Enemy> > greenEnemies;
	vector<unique_ptr<Enemy> > yellowEnemies;
	void moveAll();
	void createMultripleMonsters();
};

#endif //SPACE_S