//
// Created by ziemowit on 17.01.2021.
//
#include "constants.h"
#include "Spaceship.h"
#include <stdio.h>
#include "Projectile.h"
#include "CollisionManager.h"

Spaceship::Spaceship(SDL_Renderer *renderer, const char *imgSrc){
    shipPosX = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
    shipPosY = SCREEN_HEIGHT-SHIP_HEIGHT*2;


    SDL_Surface *tmpSurface = IMG_Load("assets/spaceship.png");
    spaceshipImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    if (!spaceshipImg)
        printf("IMG_Load: %s\n", IMG_GetError());
    SDL_FreeSurface(tmpSurface);
    if (!tmpSurface)
        printf("Failed to create surface %s\n", SDL_GetError());

    this->renderer = renderer;
}

void Spaceship::handleEvent(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym ) {
            case SDLK_w: shipVelY = -1; break;
            case SDLK_s: shipVelY = 1; break;
            case SDLK_a: shipVelX = -1; break;
            case SDLK_d: shipVelX = 1; break;
            case SDLK_SPACE: shoot(); break;
            default: break;
        }
    }
    else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_w: shipVelY = 0; break;
        case SDLK_s: shipVelY = 0; break;
        case SDLK_a: shipVelX = 0; break;
        case SDLK_d: shipVelX = 0; break;
        default: break;
        }
    }
}

void Spaceship::move() {
    //Move the spaceship left or right
    shipPosX += shipVelX * SHIP_VELOCITY;

    //If the spaceship went too far to the left or right
    if(shipPosX  < 0) {
        shipPosX = 0;
    }
    else if(shipPosX + SHIP_WIDTH > SCREEN_WIDTH) {
        shipPosX = SCREEN_WIDTH - SHIP_WIDTH;
    }

    //Move the spaceship up or down
    shipPosY += shipVelY * SHIP_VELOCITY;

    //If the spaceship went too far up or down
    if(shipPosY < 0) {
        shipPosY = 0;
    }
    else if(shipPosY + SHIP_HEIGHT> SCREEN_HEIGHT) {
        shipPosY = SCREEN_HEIGHT - SHIP_HEIGHT;
    }
}

void Spaceship::shoot() 
{
    Projectile* tmp = new Projectile(position.x + (position.w / 2 - 19/*adjust this if needed*/), position.y + 20, 1, -10);
    CollisionManager::add(tmp, 0);
    tmp = new Projectile(position.x + (position.w / 2 + 13/*adjust this if needed*/), position.y + 20, 1, -10);
    CollisionManager::add(tmp, 0);
}

void Spaceship::render() {
    position.x = shipPosX;
    position.y = shipPosY;
    position.w = SHIP_WIDTH;
    position.h = SHIP_HEIGHT;
    SDL_RenderCopy(renderer, spaceshipImg, NULL, &position);
}

SDL_Rect Spaceship::getRect() {
    return position;
}