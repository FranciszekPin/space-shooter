
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
	int shootDelay = 0;
	SDL_Renderer* renderer;
public:
	int monstersSpeed = 0;
	int shootDelay2 = 50;
	Enemy* createMonster(std::string texID, int x, int y, int creatureType, int xspeed, int yspeed, bool moveVector);
	EnemyManager(SDL_Renderer* r);
	vector<unique_ptr<Enemy> > redEnemies;
	vector<unique_ptr<Enemy> > blueEnemies;
	vector<unique_ptr<Enemy> > greenEnemies;
	vector<unique_ptr<Enemy> > yellowEnemies;
	void moveAll();
	void randomShots();
	void spawnMonsters();
	void destroyInactive();
};

#endif //SPACE_S