#include "game.h"

sdEntity *player = NULL;
float xAxis;
float yAxis;

struct ScrollBackground {
    float speed = 1.5f;
    S2D_Sprite *bgTop = NULL;
    S2D_Sprite *bgMid = NULL;
    S2D_Sprite *bgBot = NULL;
};

ScrollBackground scBg;

void invaderInit()
{
    player = sdEntityCreate("assets/PixelSpaceRage/256px/PlayerRed_Frame_01_png_processed.png");

    {//Scrolling Background init
        scBg.bgTop = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
        scBg.bgMid = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
        scBg.bgBot = S2D_CreateSprite("assets/PixelSpaceRage/PixelBackgroundSeamlessVertically.png");
        scBg.bgTop->width = gWindow->width;
        scBg.bgMid->width = gWindow->width;
        scBg.bgBot->width = gWindow->width;
        scBg.bgTop->height = gWindow->height;
        scBg.bgMid->height = gWindow->height;
        scBg.bgBot->height = gWindow->height;
        scBg.bgTop->y -= gWindow->height;
        scBg.bgMid->y = 0;
        scBg.bgBot->y += gWindow->height;
    }
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
    {//Scrolling Background update
        ++scBg.bgTop->y += scBg.speed;
        ++scBg.bgMid->y += scBg.speed;
        ++scBg.bgBot->y += scBg.speed;

        if (scBg.bgBot->y >= (gWindow->height)) scBg.bgBot->y -= gWindow->height * 2;  
        if (scBg.bgMid->y >= (gWindow->height)) scBg.bgMid->y -= gWindow->height * 2;  
        if (scBg.bgTop->y >= (gWindow->height)) scBg.bgTop->y -= gWindow->height * 2;  
    }

    projectilesUpdate();
    sdEntityMove(player, xAxis, yAxis);
}

void invaderRender()
{
    {//Scrolling Background update
        S2D_DrawSprite(scBg.bgTop);
        S2D_DrawSprite(scBg.bgMid);
        S2D_DrawSprite(scBg.bgBot);
    }

    sdEntityDraw(player, false);
    projectilesRender();
}