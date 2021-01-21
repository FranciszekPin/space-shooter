#pragma once
#include "Projectile.h"
#include <vector>
#include <memory>
#include "Spaceship.h"


class CollisionManager
{
public:
	static void init();
	static void refresh();
	static void update(Spaceship& spaceship);
	static void render();
	static void add(Projectile* tmp, bool isEnenmy);
private:
};