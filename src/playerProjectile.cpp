#include "game.h"
#include "vector"

internal std::vector<Projectile*> Projectiles;

static int projCount = 0;

internal Projectile *projectileCreate(float playerX, float playerY)
{
    Projectile *proj = (Projectile *)malloc(sizeof(Projectile));
    // Projectile *proj = new Projectile;

    proj->largeBullet = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Large_png_processed.png");
    proj->mediumBullet = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Medium_png_processed.png");
    proj->smallBullet = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Small_png_processed.png");
    
    if (!proj->largeBullet || !proj->mediumBullet || !proj->smallBullet) {
        SDL_LogError(1, "could not malloc projectile sprites: %s\n", SDL_GetError());
    }

    // memcpy(proj->largeBullet, g_assets.large, sizeof(S2D_Sprite));
    // memcpy(proj->mediumBullet, g_assets.medium, sizeof(S2D_Sprite));
    // memcpy(proj->smallBullet, g_assets.smallBullet, sizeof(S2D_Sprite));

    proj->largeBullet->x = playerX;
    proj->largeBullet->y = playerY;

    proj->mediumBullet->x = playerX;
    proj->mediumBullet->y = playerY;

    proj->smallBullet->x = playerX;
    proj->smallBullet->y = playerY;

    proj->rect.width = proj->largeBullet->width;
    proj->rect.height = proj->largeBullet->height;
    proj->rect.x = proj->largeBullet->x;
    proj->rect.y = proj->largeBullet->y;

    proj->frameBorn = gWindow->frames;
    proj->framesLived = 0;
    proj->framesToDie = 100;
    proj->dead = false;
    proj->STATE = proj->LARGE;
    proj->speed = 1.f;

    ++projCount;

    return proj;
}

void projectileFree(Projectile *proj)
{
    S2D_FreeSprite(proj->largeBullet);
    S2D_FreeSprite(proj->mediumBullet);
    S2D_FreeSprite(proj->smallBullet);
    free(proj);
}

void projectilesShoot(float playerX, float playerY)
{
    Projectiles.push_back(projectileCreate(playerX, playerY));
}

void projectilesUpdate()
{
        if (Projectiles.size() > 0) {
        for (size_t i = 0; i < Projectiles.size(); i++) {
            Projectile *proj = Projectiles.at(i);
            // 
            proj->largeBullet->y -= proj->speed * gDeltaTime;
            proj->rect.x = proj->largeBullet->x;
            proj->rect.y = proj->largeBullet->y;

            ++proj->framesLived;
            int test = ((proj->frameBorn + proj->framesLived) - proj->frameBorn);
            if (test > proj->framesToDie) {
                proj->dead = true;

                S2D_FreeSprite(proj->largeBullet);
                S2D_FreeSprite(proj->mediumBullet);
                S2D_FreeSprite(proj->smallBullet);
                
                (proj->largeBullet->img = NULL);
                (proj->mediumBullet->img = NULL);
                (proj->smallBullet->img = NULL);

                (proj->largeBullet = NULL);
                (proj->mediumBullet = NULL);
                (proj->smallBullet = NULL);

                free(proj);
                Projectiles.erase(Projectiles.begin() + i);
                --projCount;
            }
        }
    }

    // Check collision with entities
}

void projectilesRender()
{
    if (Projectiles.size() > 0) {
        for (size_t i = 0; i < Projectiles.size(); i++) {
            if (!Projectiles[i]->dead)
                S2D_DrawSprite(Projectiles[i]->largeBullet);
        }
    }
}

S2D_FRect rects[512];
S2D_FRect *getProjectileRects()
{
    size_t i;

    for (i = 0; i < Projectiles.size(); i++) {
            rects[i] = Projectiles[i]->rect;
    }
    rects[i+1].width = -1;
    return rects;
}

int getProjectileCount()
{
    return projCount;
}

int getProjectileVectorCount()
{
    return Projectiles.size();
}