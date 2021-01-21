//
// Created by pumassv1 on 28.12.2020.
//

#ifndef SPACE_SHOOTER_GAMEMANAGER_H
#define SPACE_SHOOTER_GAMEMANAGER_H

#include "sdlsystem.h"

class GameManager {
private:
    SDL_Window *window;

public:
    static SDL_Renderer* renderer;
    GameManager();
    bool init();
    void startGame();
    ~GameManager();
};


#endif //SPACE_SHOOTER_GAMEMANAGER_H
