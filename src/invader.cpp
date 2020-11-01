#include "game.h"

sdEntity *player = NULL;
S2D_Sprite *background = NULL;
float xAxis;
float yAxis;

void invaderInit()
{
    player = sdEntityCreate("assets/PixelSpaceRage/256px/PlayerRed_Frame_01_png_processed.png");
    background = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
    background->width = 800;
    background->height = 600;
}

void invaderOnKeyHeld(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_SPACE:
        projectilesShoot(
            player->position.x + player->rect.width/2 - 5.5f,
            player->position.y - 20);
        break;
    
    default:
        break;
    }
}

void invaderUpdate(UpdateArgs *args)
{
    projectilesUpdate();
    sdEntityMove(player, xAxis, yAxis);
}

void invaderRender()
{
    S2D_DrawSprite(background);
    sdEntityDraw(player, false);
    projectilesRender();
}