#include "CollisionManager.h"
#include "Collision.h"
#include "AssetManager.h"
#include "constants.h"
#include <iostream>

AssetManager* assetManager = new AssetManager();

std::vector<std::unique_ptr<Projectile>> friendlyProjectiles;
std::vector<std::unique_ptr<Projectile>> enemyProjectiles;

void CollisionManager::init()
{
    assetManager->AddTexture("Bullet", "assets/bullet.png"); //adds projectile texture to asset manager
    assetManager->AddTexture("enemyBullet", "assets/fallingbullet.png");
    Projectile* tmp;
    for (int i = 0;i < SCREEN_WIDTH;i += 50)
    {
        tmp = new Projectile(i, 0, 1, i / 50 + 1); //creates projectiles and adds them to vector
        enemyProjectiles.emplace_back(tmp);
    }
}

void CollisionManager::add(Projectile* tmp, bool isEnemy)
{
    if (isEnemy) 
        enemyProjectiles.emplace_back(tmp);
    else
       friendlyProjectiles.emplace_back(tmp);
}
void CollisionManager::refresh()
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

void CollisionManager::update(Spaceship& spaceship)
{
    SDL_Rect tmp;

    for (auto& p : friendlyProjectiles) //updates friendly projectiles, draws them and checks if they collide with enemies
    {
        /*for (auto& e : enemies)
        {
            //if collision then ...
        }*/
        tmp = p->GetRectangle();
        if (tmp.y < 0 - tmp.h || tmp.y>SCREEN_HEIGHT)
        {
            p->destroy();
            std::cout << "Projectile out of range\n";
        }

        p->update();
    }

    for (auto& p : enemyProjectiles) //updates enemy projectiles, draws them and checks if they collide with the spaceship
    {
        if (Collision::AABB(spaceship.getRect(), p->GetRectangle())) //checks if two rectangles (player's and enemy's) collide
        {

            std::cout << "Player hit!\n";
            p->destroy();
        }
        tmp = p->GetRectangle();
        if (tmp.y< 0 - tmp.h || tmp.y >SCREEN_HEIGHT)
        {
            p->destroy();
            std::cout << "Projectile out of range\n";
        }

        p->update();
    }
}

void CollisionManager::render()
{
    for (auto& p : friendlyProjectiles) //updates friendly projectiles, draws them and checks if they collide with enemies
    {
        
        p->render(assetManager->GetTexture("Bullet"));
    }

    for (auto& p : enemyProjectiles) //updates enemy projectiles, draws them and checks if they collide with the spaceship
    {
        p->render(assetManager->GetTexture("enemyBullet"));
    }
}