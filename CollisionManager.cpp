#include "CollisionManager.h"
#include "Collision.h"
#include "AssetManager.h"
#include "constants.h"
#include <iostream>

AssetManager* assetManager = new AssetManager();
//add sound mixer object here

std::vector<std::unique_ptr<Projectile>> friendlyProjectiles;
std::vector<std::unique_ptr<Projectile>> enemyProjectiles;



void CollisionManager::init()
{
    assetManager->AddTexture("Bullet", "assets/bullet.png"); //adds projectile texture to asset manager
    assetManager->AddTexture("enemyBullet", "assets/fallingbullet.png");
    assetManager->AddTexture("background", "assets/background.png");

    Projectile* tmp = new Projectile(-60, 50, 1, 0); //creates  friendly projectile that stays idle outside the screen so that enemyProjectiles is never empty
    enemyProjectiles.emplace_back(tmp);
    tmp = new Projectile(-60, 50, 1, 0); //same as above but for friendlyProjectiles
    friendlyProjectiles.emplace_back(tmp);

    /*for (int i = 0;i < SCREEN_WIDTH;i += 50)
    {
        tmp = new Projectile(i, 0, 1, i / 50 + 1); //creates projectiles and adds them to vector
        enemyProjectiles.emplace_back(tmp);
    }*/
}

void CollisionManager::add(Projectile* tmp, bool isEnemy)
{
    if (isEnemy)
    {
        //play enemy shooting sound here
        enemyProjectiles.emplace_back(tmp);
    }
    else
    {
        //play spaceship shooting sound here
        friendlyProjectiles.emplace_back(tmp);
    }
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

void CollisionManager::update(Spaceship& spaceship, EnemyManager& enemyManager)
{
    SDL_Rect tmp;

    for (auto& p : friendlyProjectiles) //updates friendly projectiles, draws them and checks if they collide with enemies
    {
        tmp = p->GetRectangle();

        for (auto& e : enemyManager.blueEnemies)
        {
            if (Collision::AABB(e->GetRectangle(), tmp))
            {
                //play collision (bullet x enemy) sound here
                e->deactive();
                p->destroy();
                cout << "Blue enemy hit!\n";
            }
            if (e->GetRectangle().y > SCREEN_HEIGHT)
            {
                e->deactive();
                printf("Enemy out of range!");
            }
        }

        for (auto& e : enemyManager.yellowEnemies)
        {
            if (Collision::AABB(e->GetRectangle(), tmp))
            {
                //play collision (bullet x enemy) sound here
                e->deactive();
                p->destroy();
                cout << "Yellow enemy hit!\n";
            }
            if (e->GetRectangle().y > SCREEN_HEIGHT)
            {
                e->deactive();
                printf("Enemy out of range!\n");
            }
        }

        for (auto& e : enemyManager.greenEnemies)
        {
            if (Collision::AABB(e->GetRectangle(), tmp))
            {
                //play collision (bullet x enemy) sound here
                e->deactive();
                p->destroy();
                cout << "Green enemy hit!\n";
            }
            if (e->GetRectangle().y > SCREEN_HEIGHT)
            {
                e->deactive();
                printf("Enemy out of range!\n");
            }
        }

        for (auto& e : enemyManager.redEnemies)
        {
            if (Collision::AABB(e->GetRectangle(), tmp))
            {
                //play collision (bullet x enemy) sound here
                e->deactive();
                p->destroy();
                cout << "Red enemy hit!\n";
            }
            if (e->GetRectangle().y > SCREEN_HEIGHT)
            {
                e->deactive();
                printf("Enemy out of range!\n");

            }
        }

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
            //play collision (enemy bullet x spaceship) sound here
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
    assetManager->render("background");

    for (auto& p : friendlyProjectiles) //updates friendly projectiles, draws them and checks if they collide with enemies
    {
        
        p->render(assetManager->GetTexture("Bullet"));
    }

    for (auto& p : enemyProjectiles) //updates enemy projectiles, draws them and checks if they collide with the spaceship
    {
        p->render(assetManager->GetTexture("enemyBullet"));
    }
}