#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

/*
 * extern meaning that this variable will be defined somewhere
 * in this case gWindow is defined in main.cpp
 * because we made an extern forward declaration here, gWindow will also be available
 * everywhere where this game.h will be included
 * otherwise compiler would complain about multiple definitions 
 */
extern S2D_Window *gWindow;
extern float xAxis;
extern float yAxis;

typedef struct {
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
} sdEntity;

typedef struct {
    char *str;
    int i;
} UpdateArgs;

// Projectile
struct Projectile
{
    enum {
        LARGE,
        MEDIUM,
        SMALL
    } STATE;

    bool dead = false;
    float speed = 0;
    int frameBorn = 0;
    int framesLived = 0;
    int framesToDie = 0;
    S2D_FRect rect {0,0,0,0};
    S2D_Sprite *frame0 = NULL;
    S2D_Sprite *frame1 = NULL;
    S2D_Sprite *frame2 = NULL;
};

void projectileFree(Projectile *proj);
Projectile *projectileCreate(float playerX, float playerY);

// function decl: sdEntity 
sdEntity *sdEntityCreate(const char *path);
void sdEntityDraw(sdEntity *entity, bool debugMode);
void sdEntitySetSize(sdEntity *entity, float width, float height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

// invader 
void invader_init();
void invader_shoot(SDL_Keycode key);
void invader_update(UpdateArgs *args);
void invader_render();
#endif // GAME_H
