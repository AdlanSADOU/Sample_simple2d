#include "game.h"
#include <random>

int enemiesCount = 0;
int killed = 0;
float spawnY = 100;

std::vector<Enemy *> Enemies;

Enemy *enemyCreate()
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    enemy->entity = sdEntityCreate("assets/PixelSpaceRage/256px/Enemy01_Green_Frame_1_png_processed.png");
    enemy->dead = false;

    std::random_device rd;                                           // obtain a random number from hardware
    std::mt19937 gen(rd());                                          // seed the generator
    std::uniform_int_distribution<> distr(10, gWindow->width - 100); // define the range

    int randX = distr(gen);
    sdEntitySetPosition(enemy->entity, randX, spawnY);
    ++enemiesCount;

    return enemy;
}

void enemySpawn()
{
    Enemies.push_back(enemyCreate());
}

void enemyUpdate(S2D_FRect playerRect)
{
    if (Enemies.size() > 0)
    {
        for (size_t i = 0; i < Enemies.size(); i++)
        { // for every enemy ship
            auto tmp = Enemies[i];

            // sdEntityMove(tmp->entity, 0, 1); // move the ship

            if ((tmp->entity->position.y > gWindow->height) || S2D_Intersect_FRect(playerRect, tmp->entity->rect))
                tmp->dead = true; // mark the ship as dead if it goes out of the screen (height) or collides with the player
                ++killed;
            S2D_FRect *rects = getProjectileRects();
            for (size_t i = 0; rects[i].width != -1; i++)
            {
                if (S2D_Intersect_FRect(rects[i], tmp->entity->rect))
                {
                    tmp->dead = true; // mark the ship as dead if it's hit by a player projectile
                }
            }

            if (tmp->dead)
            {
                S2D_FreeSprite(tmp->entity->sprite);
                free(tmp->entity);
                Enemies.erase(Enemies.begin() + i); // delete the enemy from the list if it's marked as dead
                --enemiesCount;
            }
        }
    }
}

void enemyRender()
{
    if (Enemies.size() > 0)
        for (size_t i = 0; i < Enemies.size(); i++)
        {
            auto tmp = Enemies[i]->entity;
            sdEntityDraw(Enemies[i]->entity, false);
        }
}

int getEnemyCount()
{
    return enemiesCount;
}

int getEnemyVectorSize()
{
    return Enemies.size();
}

int getEnemyKillCount()
{
    return killed;
}