//
// Created by ziemowit on 17.01.2021.
//

#ifndef SPACE_SHOOTER_SPACESHIP_H
#define SPACE_SHOOTER_SPACESHIP_H

#include "sdlsystem.h"

class Spaceship {
private:
    //Current position and velocity of the spaceship
    int shipPosX, shipPosY;
    int shipVelX, shipVelY;
public:
    //Spaceship dimensions
    static const int SHIP_WIDTH = 50;
    static const int SHIP_HEIGHT = 50;
    //Maximum axis velocity of the spaceship
    static const int SHIP_VELOCITY = 0;

    Spaceship();

    //Handles keys pressed
    void handleEvent(SDL_Event &e);
    //Moves the spaceship in accordance to the velocity
    void move();
    //Shoots missiles
    void shoot();
    //Shows the spaceship on the screen
    void render();

};

#endif //SPACE_SHOOTER_SPACESHIP_H
