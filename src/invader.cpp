#include "game.h"
#include "vector"

sdEntity *player = NULL;
S2D_Sprite *background = NULL;
float xAxis;
float yAxis;

struct Projectile
{
    enum {
        LARGE,
        MEDIUM,
        SMALL
    } STATE;

    float speed;
    float timeToDie;
    S2D_FRect rect;
    S2D_Sprite *frame0;
    S2D_Sprite *frame1;
    S2D_Sprite *frame2;
};

std::vector<Projectile> Projectiles;

struct Assets {
    S2D_Sprite *frame0 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Large_png_processed.png");
    S2D_Sprite *frame1 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Medium_png_processed.png");
    S2D_Sprite *frame2 = S2D_CreateSprite("assets/PixelSpaceRage/256px/Minigun_Small_png_processed.png");
};

Assets g_assets;

// Projectile projectile_init()
// {
//     proj->frame0 = g_assets.frame0;
//     proj->frame1 = g_assets.frame1;
//     proj->frame2 = g_assets.frame2;

//     proj->timeToDie = 1.5f;
//     proj->STATE = proj->LARGE;
//     proj->speed = 1.f;
// }

void invader_init()
{
    background = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
    background->width = 800;
    background->height = 600;
    player = sdEntityCreate("assets/PixelSpaceRage/256px/PlayerRed_Frame_01_png_processed.png");

    Projectile proj = {.STATE = Projectile::LARGE, 
                       .speed = 1.f,
                       .timeToDie = 1.f,
                       .frame0 = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png"),
                       .frame1 = g_assets.frame1,
                       .frame2 = g_assets.frame2};

    proj.frame0->x = 50;
    proj.frame0->y = 50;


    Projectiles.push_back(proj);
}

void invader_update(update_args *args)
{
    sdEntityMove(player, xAxis, yAxis);
}

void invader_render()
{
    S2D_DrawSprite(background);
    sdEntityDraw(player, false);
    if (Projectiles.size() > 0) {
        S2D_GL_DrawSprite(Projectiles[0].frame0);
    }
}