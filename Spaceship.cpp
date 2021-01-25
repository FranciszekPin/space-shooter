//
// Created by ziemowit on 17.01.2021.
//
#include "Spaceship.h"
#include <stdio.h>
#include "Projectile.h"
#include "CollisionManager.h"
#include "MusicManager.h"
#include "AssetManager.h"

AssetManager* assetManagerS = new AssetManager;

MusicManager* jukebox3 = new MusicManager();
Spaceship::Spaceship(SDL_Renderer *renderer, const char *imgSrc){

    assetManagerS->AddTexture("hp", "assets/hp3.png");

    shipPosX = SCREEN_WIDTH/2 - SHIP_WIDTH/2;
    shipPosY = SCREEN_HEIGHT-SHIP_HEIGHT*2;


    SDL_Surface *tmpSurface = IMG_Load("assets/spaceship.png");
    spaceshipImg = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    if (!spaceshipImg)
        printf("IMG_Load: %s\n", IMG_GetError());
    SDL_FreeSurface(tmpSurface);
    if (!tmpSurface)
        printf("Failed to create surface %s\n", SDL_GetError());
    jukebox3->init();

    this->renderer = renderer;
}

Spaceship::~Spaceship()
{
    SDL_DestroyTexture(spaceshipImg);
}

bool Spaceship::isAlive()
{
    if (hp <= 0)return false;
    else return true;
}

void Spaceship::handleEvent(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN) {
        switch( e.key.keysym.sym ) {
    
            case SDLK_w: shipVelY = -1; break;
            case SDLK_s: shipVelY = 1; break;
            case SDLK_a: shipVelX = -1; break;
            case SDLK_d: shipVelX = 1; break;
            case SDLK_SPACE: if (e.key.repeat == 0)shoot(); break;
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
    jukebox3->playShot();
    Projectile* tmp = new Projectile(position.x + (position.w / 2 - 19/*adjust this if needed*/), position.y + 20, PLAYER_PROJECTILE_SCALE, PLAYER_PROJECTILE_SPEED);
    CollisionManager::add(tmp, 0);
    tmp = new Projectile(position.x + (position.w / 2 + 13/*adjust this if needed*/), position.y + 20, PLAYER_PROJECTILE_SCALE, PLAYER_PROJECTILE_SPEED);
    CollisionManager::add(tmp, 0);
}

void Spaceship::render_hp()
{
    SDL_Rect hpRect;
    hpRect.w = 20;
    hpRect.h = 20;
    hpRect.x = SCREEN_WIDTH - 152;
    hpRect.y = 80;
    for (int i = 0;i < hp;i++)
    {
        hpRect.x += 25;
        SDL_RenderCopy(renderer, assetManagerS->GetTexture("hp"), NULL, &hpRect);
    }
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