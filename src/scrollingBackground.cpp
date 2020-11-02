#include "game.h"

ScrollBackground scBg;

void scrollBgInit()
{ //Scrolling Background init
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
    scBg.speed = 0.1f;
}

void scrollBgUpdate()
{ //Scrolling Background update
    ++scBg.bgTop->y += (scBg.speed * gDeltaTime);
    ++scBg.bgMid->y += (scBg.speed * gDeltaTime);
    ++scBg.bgBot->y += (scBg.speed * gDeltaTime);

    if (scBg.bgBot->y >= (gWindow->height))
        scBg.bgBot->y -= gWindow->height * 2;
    if (scBg.bgMid->y >= (gWindow->height))
        scBg.bgMid->y -= gWindow->height * 2;
    if (scBg.bgTop->y >= (gWindow->height))
        scBg.bgTop->y -= gWindow->height * 2;
}

void scrollBgRender()
{ //Scrolling Background update
    S2D_DrawSprite(scBg.bgTop);
    S2D_DrawSprite(scBg.bgMid);
    S2D_DrawSprite(scBg.bgBot);
}