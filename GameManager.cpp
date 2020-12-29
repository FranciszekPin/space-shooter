//
// Created by pumassv1 on 28.12.2020.
//
#include <stdio.h>
#include "GameManager.h"
#include "constants.h"


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
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }
    return success;
}

void GameManager::startGame() {

    bool quit = false;

    SDL_Event e;

    while (!quit) {
        SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear (renderer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // adding all render objects should be done before this function
        SDL_RenderPresent(renderer);
    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}