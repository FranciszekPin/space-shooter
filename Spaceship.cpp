//
// Created by ziemowit on 17.01.2021.
//
#include "constants.h"
#include "Spaceship.h"

Spaceship::Spaceship(){
    shipPosX = SCREEN_WIDTH/2;
    shipPosY = SCREEN_HEIGHT;
}

void Spaceship::handleEvent(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP: shipVelY -= SHIP_VELOCITY; break;
            case SDLK_DOWN: shipVelY += SHIP_VELOCITY; break;
            case SDLK_LEFT: shipVelX -= SHIP_VELOCITY; break;
            case SDLK_RIGHT: shipVelX += SHIP_VELOCITY; break;
            case SDLK_SPACE: shoot(); break;
        }
    }
}

void Spaceship::move() {
    //Move the spaceship left or right
    shipPosX += shipVelX;

    //If the spaceship went too far to the left or right
    if(shipPosX + SHIP_WIDTH/2 < 0) {
        shipPosX = 0 + SHIP_WIDTH/2;
    }
    else if(shipPosX + SHIP_WIDTH/2 > SCREEN_WIDTH) {
        shipPosX = SCREEN_WIDTH - SHIP_WIDTH/2;
    }

    //Move the spaceship up or down
    shipPosY += shipVelY;

    //If the spaceship went too far up or down
    if(shipPosY - SHIP_HEIGHT/2 < 0) {
        shipPosY = 0 + SHIP_HEIGHT/2;
    }
    else if(shipPosY + SHIP_HEIGHT/2 > SCREEN_HEIGHT) {
        shipPosY = SCREEN_WIDTH - SHIP_HEIGHT/2;
    }
}

void Spaceship::shoot() {}

void Spaceship::render() {}