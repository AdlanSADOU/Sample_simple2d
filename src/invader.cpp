#include "game.h"

sdEntity *player = NULL;

S2D_Text *enemiesCountText = NULL;
S2D_Text *projCountText = NULL;

float xAxis = 0;
float yAxis = 0;
float gSpeed = 1.f;

void invaderInit()
{
    enemiesCountText = S2D_CreateText("assets/PixelSpaceRage/fonts/space_invaders.ttf", "lol", 20);
    enemiesCountText->x = 20;
    enemiesCountText->y = 25;
    enemiesCountText->color = {0.1f, 0.8f,0.1f, 1.f};

    projCountText = S2D_CreateText("assets/PixelSpaceRage/fonts/space_invaders.ttf", "lol", 20);
    projCountText->x = 20;
    projCountText->y = enemiesCountText->y + 25;
    projCountText->color = {0.1f, 0.8f,0.1f, 1.f};

    player = sdEntityCreate("assets/PixelSpaceRage/256px/PlayerRed_Frame_01_png_processed.png");
    sdEntitySetPosition(player, gWindow->width/2 - player->sprite->width/2, gWindow->height - 150);
    
    scrollBgInit();
}

void invaderUpdate(UpdateArgs *args)
{
    scrollBgUpdate();

    S2D_SetText(enemiesCountText, "Enemy Ships: %d | vector-Size: %d", getEnemyCount(), getEnemyVectorSize());
    S2D_SetText(projCountText, "vector-Size: %d", getProjectileVectorCount());

    enemyUpdate(player->rect);
    projectilesUpdate();

    if ((player->position.x + xAxis) > 0) {
        sdEntityMove(player, xAxis, yAxis);
    }
}

void invaderRender()
{
    scrollBgRender();
    projectilesRender();
    enemyRender();

    sdEntityDraw(player, false);

    S2D_DrawText(enemiesCountText);
    S2D_DrawText(projCountText);
}

void invaderOnKeyHeld(SDL_Keycode key)
{
    xAxis = yAxis = 0;

    switch (key)
    {
    case SDLK_SPACE:
        projectilesShoot(
            player->position.x + player->rect.width / 2 - 5.5f,
            player->position.y - 20);
        break;
    case SDLK_p:
        enemySpawn();
        break;
    case SDLK_w:
        sdEntityMove(player, 0, -(gDeltaTime * gSpeed));
        break;
    case SDLK_a:
        sdEntityMove(player, -(gDeltaTime * gSpeed), 0);
        break;
    case SDLK_s:
        sdEntityMove(player, 0, gDeltaTime * gSpeed);
        break;
    case SDLK_d:
        sdEntityMove(player, gDeltaTime * gSpeed, 0);
        break;
    case SDLK_LSHIFT:
        break;
    default:
        break;
    }
}