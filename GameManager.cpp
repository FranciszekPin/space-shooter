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
#include "Background.h"

SDL_Renderer* GameManager::renderer = nullptr;

GameManager::GameManager() {
    window = NULL;
    renderer = NULL;
}

bool GameManager::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("MIXER could not be created! SDL Error: %s\n", Mix_GetError());
                    success = false;
                }
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                CollisionManager::init();
            }
        }
    }
    return success;
}

int GameManager::startGame() {
    double duration;
    double lastTime = (std::clock()) / (double)CLOCKS_PER_SEC;
    double deltaTime = 0;
    double timeSinceLastFrame = 0;
    int secs = 0;

    bool quit = false;

    SDL_Event e;
    Clock zegar(renderer);
    zegar.resetTIME();

    //Creating a spaceship
    EnemyManager enemyManager(renderer);
    Spaceship spaceship(renderer, "xd");
    Background B;
    Enemy::init();
    CollisionManager::init();

    while (1) {
        if (!spaceship.isAlive())
        {
            enemyManager.eraseAll();
            CollisionManager::eraseAll();
            return 1;
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                return 0;
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

            B.render();

            CollisionManager::update(spaceship, enemyManager);
            CollisionManager::refresh();
            enemyManager.destroyInactive();
           secs = zegar.getTime().x + zegar.getTime().y * 10;
           if ((secs % 18 > 15) && (enemyManager.shootDelay2 > 20))
               enemyManager.shootDelay2 -= 4;
           if ((secs % 50 > 45) && (enemyManager.monstersSpeed < 4))
               enemyManager.monstersSpeed += 1;

            enemyManager.spawnMonsters();
            spaceship.move();
            enemyManager.randomShots();

            CollisionManager::render();
            zegar.render();
            enemyManager.moveAll();
            spaceship.render();
            zegar.render();
            spaceship.render_hp();

            SDL_RenderPresent(renderer);
        }

    }
}

void GameManager::playGame()
{
    SDL_Event e;
    Background B(123);
start:
    if(startGame())
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        B.render2();
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
        while (1)
        {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    return;
                }
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    goto start;
                }
            }
        }
 
    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}