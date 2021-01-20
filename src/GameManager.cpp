//
// Created by pumassv1 on 28.12.2020.
//
#include "GameManager.h"
#include "constants.h"
#include <cstdio>
#include <ctime>


GameManager::GameManager() {
    window = NULL;
    renderer = NULL;
}

bool GameManager::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

void GameManager::startGame() {

    double duration;
    double lastTime = ( std::clock()) / (double) CLOCKS_PER_SEC;
    double deltaTime = 0;
    double timeSinceLastFrame = 0;


    bool quit = false;

    SDL_Event e;

    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_SPACE:

                        // spaceship opens fire
                        break;
                    case SDLK_LEFT:

                        // move spaceship left
                        break;
                    case SDLK_RIGHT:

                        // move spaceship right
                        break;
                }
            }
        }
        duration = ( std::clock()) / (double) CLOCKS_PER_SEC;
        deltaTime = duration - lastTime;
        lastTime = duration;
        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame > 1.0/SCREEN_FPS)
        {
            timeSinceLastFrame = 0;
            // adding all render objects should be done before this function


            SDL_RenderPresent(renderer);
        }

    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}