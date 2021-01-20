//
// Created by pumassv1 on 28.12.2020.
//
#include "GameManager.h"
#include "constants.h"
#include "Spaceship.h"
#include <cstdio>
#include <ctime>
#include <memory>
#include <vector>
#include "Projectile.h"
#include "AssetManager.h"
#include "Collision.h"
#include "Enemy.h"
#include "Collision.h"
#include <iostream>

AssetManager* assetManager= new AssetManager();
SDL_Renderer* GameManager::renderer = nullptr;

std::vector <std::unique_ptr <Projectile>> friendlyProjectiles;
std::vector <std::unique_ptr <Projectile>> enemyProjectiles;

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

                assetManager->AddTexture("proj", "assets/proj.png"); //adds projectile texture to asset manager
                Projectile* tmp;
                for (int i = 0;i < SCREEN_WIDTH;i+=50)
                {
                    tmp = new Projectile(i,0,1,i/50+1); //creates projectiles and adds them to vector
                    enemyProjectiles.emplace_back(tmp);
                }

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

    //Creating a spaceship
    Spaceship spaceship(GameManager::renderer, "xd");

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
        duration = ( std::clock()) / (double) CLOCKS_PER_SEC;
        deltaTime = duration - lastTime;
        lastTime = duration;
        timeSinceLastFrame += deltaTime;

        if (timeSinceLastFrame > 1.0/SCREEN_FPS)
        {
            timeSinceLastFrame = 0;
            // adding all render objects should be done before this function

            spaceship.move();
            spaceship.render();
            RefreshProjectiles();

            for (auto& p : enemyProjectiles) //updates enemy projectiles, draws them and checks if they collide with the spaceship
            {
                if (Collision::AABB(spaceship.getRect(), p->GetRectangle())) //checks if two rectangles (player's and enemy's) collide
                {
                    
                    std::cout << duration << " Player hit!\n";
                    p->destroy();
                }

                p->update();
                p->render(assetManager->GetTexture("proj"));
            }
            
            for (auto& p : friendlyProjectiles) //updates friendly projectiles, draws them and checks if they collide with enemies
            {
                /*for (auto& e : enemies)
                {
                    //if collision then ...
                }*/

                p->update();
                p->render(assetManager->GetTexture("proj"));
            }

            SDL_RenderPresent(renderer);
        }

    }
}

GameManager::~GameManager() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameManager::AddNewProjectileToVector(Projectile* tmp, bool ifEnemy)
{
    if (ifEnemy)
        enemyProjectiles.emplace_back(tmp);
    else
        friendlyProjectiles.emplace_back(tmp);
}

void GameManager::RefreshProjectiles()
{
    enemyProjectiles.erase(std::remove_if(std::begin(enemyProjectiles), std::end(enemyProjectiles),
        [](const std::unique_ptr<Projectile>& proj)  //Lambda expr
        {
            return !proj->isActive();
        }),
        std::end(enemyProjectiles));

    friendlyProjectiles.erase(std::remove_if(std::begin(friendlyProjectiles), std::end(friendlyProjectiles),
        [](const std::unique_ptr<Projectile>& proj)  //Lambda expr
        {
            return !proj->isActive();
        }),
        std::end(friendlyProjectiles));
}