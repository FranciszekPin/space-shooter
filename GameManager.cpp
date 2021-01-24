//
// Created by pumassv1 on 28.12.2020.
//
#include "GameManager.h"
#include "constants.h"
#include "Clock.h"
#include <cstdio>
#include <ctime>
#include "EnemyManager.h"
#include"CollisionManager.h"

SDL_Renderer* GameManager::renderer = nullptr;

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

                CollisionManager::init();
            }
        }
    }
    return success;
}

void GameManager::startGame() {

    double duration;
    double lastTime = (std::clock()) / (double)CLOCKS_PER_SEC;
    double deltaTime = 0;
    double timeSinceLastFrame = 0;
    int secs = 0;

    bool quit = false;

    SDL_Event e;
    Clock zegar(renderer);

    //Creating a spaceship
    EnemyManager enemyManager(renderer);
    Spaceship spaceship(renderer, "xd");


    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                spaceship.handleEvent(e);
            }
        }
        duration = (std::clock()) / (double)CLOCKS_PER_SEC;
        deltaTime = duration - lastTime;
        lastTime = duration;
        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame > 1.0 / SCREEN_FPS)
        {
            timeSinceLastFrame = 0;
            // adding all render objects should be done before this function
            zegar.render();

            CollisionManager::update(spaceship, enemyManager);
            CollisionManager::refresh();
            enemyManager.destroyInactive();
            secs = zegar.getTime().x + zegar.getTime().y * 10;
            if (secs % 15)
                enemyManager.shootDelay2 - 3;
            enemyManager.spawnMonsters();
            spaceship.move();
            enemyManager.moveAll();
            enemyManager.randomShots();
            CollisionManager::render();
            spaceship.render();

            SDL_RenderPresent(renderer);
        }

    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}