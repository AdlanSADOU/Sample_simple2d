#include "game.h"
#include "vector"

sdEntity *player = NULL;
S2D_Sprite *background = NULL;
float xAxis;
float yAxis;

std::vector<Projectile*> Projectiles;

void invader_init()
{
    background = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
    background->width = 800;
    background->height = 600;
    player = sdEntityCreate("assets/PixelSpaceRage/256px/PlayerRed_Frame_01_png_processed.png");
}

void invader_shoot(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_SPACE:
        Projectiles.push_back(projectileCreate(player->position.x + player->rect.width/2 - 5.5f, player->position.y - 20));
        break;
    
    default:
        break;
    }
}

void invader_update(UpdateArgs *args)
{
    // Projectiles: Update & Mark as dead
    if (Projectiles.size() > 0) {
        for (size_t i = 0; i < Projectiles.size(); i++) {
            Projectile *proj = Projectiles.at(i);
            // 
            proj->frame0->y -= proj->speed;

            ++proj->framesLived;
            int test = ((proj->frameBorn + proj->framesLived) - proj->frameBorn);
            if (test > proj->framesToDie) {
                proj->dead = true;
            }
        }
    }

    // Check collision with entities

    // Projectiles: Destroy marked as dead
    if (Projectiles.size() > 0) {
        for (size_t i = 0; i < Projectiles.size(); i++) {
            Projectile *proj = Projectiles.at(i);
            if (proj->dead) {
                projectileFree(proj);
                Projectiles.erase(Projectiles.begin() + i);
            }
        }
    }

    sdEntityMove(player, xAxis, yAxis);
}

void invader_render()
{
    S2D_DrawSprite(background);
    sdEntityDraw(player, false);
    if (Projectiles.size() > 0) {
        for (size_t i = 0; i < Projectiles.size(); i++) {
            if (!Projectiles[i]->dead)
                S2D_DrawSprite(Projectiles[i]->frame0);
        }
    }
}