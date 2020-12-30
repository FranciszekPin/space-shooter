

#ifndef SPACE_SHOOTER_ENEMY_H
#define SPACE_SHOOTER_ENEMY_H
#include "sdlsystem.h"

class Enemy
{	
public:
	SDL_Surface* loadImage(const char* enemy_img);
	SDL_Surface* enemyIMG;
	SDL_Rect position;
	
	double enemy_y=0.0;
	void move(double delta_time, SDL_Surface* background);
};

#endif //SPACE_SHOOTER_ENEMY_H