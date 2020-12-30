#include <stdio.h>
#include "Enemy.h"
#include "constants.h"
#include <string>

SDL_Surface* Enemy::loadImage(const char *enemy_img)
{
    //Loading success flag
    bool success = true;
    SDL_Surface* enemy;
    //Load splash image
    enemy = SDL_LoadBMP(enemy_img);
    if (enemy == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", enemy_img, SDL_GetError());
        success = false;
    }

    return enemy;

}

void Enemy::move(double delta_time, SDL_Surface* background)
{
    SDL_FillRect(enemyIMG, NULL, SDL_MapRGB(enemyIMG->format, 0, 0, 0));
    if (enemyIMG) {
        enemy_y = enemy_y + (5 * delta_time);
        position.y = enemy_y;
      
        enemyIMG = loadImage("monster2.bmp");
        SDL_BlitSurface(enemyIMG, NULL, background, &position);
        
    }
}