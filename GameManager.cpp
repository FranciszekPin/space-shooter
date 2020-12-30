//
// Created by pumassv1 on 28.12.2020.
//
#include <stdio.h>
#include "GameManager.h"
#include "constants.h"
#include "Enemy.h"
#include <cstdlib>
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
    Enemy enemy[5];
    const double frames = 60.0;
    int frameStart, frameTime;
    SDL_Surface* background = NULL;
    SDL_Event e;
    //enemy = (Enemy*)malloc(sizeof(Enemy));

    background = SDL_GetWindowSurface(window);
    for (int i = 0; i < 5; i++)
    {
        enemy[i].enemyIMG = enemy[i].loadImage("assets/monster2.bmp");
        enemy[i].position.x = 1 + (rand() % 600);
    }
    srand((unsigned)time(0));
   
    while (!quit) {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear (renderer);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            enemy[i].move(1.0 / frames, background);
        }
        frameTime = SDL_GetTicks() - frameStart;
        SDL_UpdateWindowSurface(window);
        
        SDL_Delay(frameTime);
       
        // adding all render objects should be done before this function
        SDL_RenderPresent(renderer);
    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
