#include "game.h"
#include "vector"

void projectileFree(Projectile *proj)
{
    S2D_FreeSprite((proj)->frame0);
    S2D_FreeSprite((proj)->frame1);
    S2D_FreeSprite((proj)->frame2);
    free(proj);
}

Projectile *projectileCreate(float playerX, float playerY)
{
    Projectile *proj = (Projectile *)malloc(sizeof(Projectile));
    // Projectile *proj = new Projectile;

    proj->frame0 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Large_png_processed.png");
    proj->frame1 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Medium_png_processed.png");
    proj->frame2 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Small_png_processed.png");
    
    if (!proj->frame0 || !proj->frame1 || !proj->frame2) {
        SDL_LogError(1, "could not malloc projectile sprites: %s\n", SDL_GetError());
    }

    // memcpy(proj->frame0, g_assets.frame0, sizeof(S2D_Sprite));
    // memcpy(proj->frame1, g_assets.frame1, sizeof(S2D_Sprite));
    // memcpy(proj->frame2, g_assets.frame2, sizeof(S2D_Sprite));

    proj->frame0->x = playerX;
    proj->frame0->y = playerY;
    proj->frame1->x = playerX;
    proj->frame1->y = playerY;
    proj->frame2->x = playerX;
    proj->frame2->y = playerY;
    
    proj->frameBorn = gWindow->frames;
    proj->framesLived = 0;
    proj->framesToDie = 100;
    proj->dead = false;
    proj->STATE = proj->LARGE;
    proj->speed = 20.f;

    return proj;
}