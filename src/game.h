#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"
#include "vector"

#define internal static

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
extern float gSpeed;
extern float gDeltaTime;
// Entity
typedef struct
{
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
} sdEntity;

typedef struct
{
    char *str;
    int i;
} UpdateArgs;

// Projectile
struct Projectile
{
    enum
    {
        LARGE,
        MEDIUM,
        SMALL
    } STATE;

    bool dead = false;
    float speed = 0;
    int frameBorn = 0;
    int framesLived = 0;
    int framesToDie = 0;
    S2D_FRect rect{0, 0, 0, 0};
    S2D_Sprite *largeBullet = NULL;
    S2D_Sprite *mediumBullet = NULL;
    S2D_Sprite *smallBullet = NULL;
};

// Scrolling Background
struct ScrollBackground
{
    float speed = 0;
    S2D_Sprite *bgTop = NULL;
    S2D_Sprite *bgMid = NULL;
    S2D_Sprite *bgBot = NULL;
};

struct Enemy
{
    sdEntity *entity;
    bool dead = false;
};

// Projectiles
void projectileFree(Projectile *proj);
Projectile *projectileCreate(float playerX, float playerY);
void projectilesShoot(float playerX, float playerY);
void projectilesUpdate();
void projectilesRender();
S2D_FRect *getProjectileRects();
int getProjectileVectorCount();
int getProjectileCount();

// Entity
sdEntity *sdEntityCreate(const char *path);
void sdEntityDraw(sdEntity *entity, bool debugMode);
void sdEntitySetSize(sdEntity *entity, float width, float height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

// invader
void invaderInit();
void invaderOnKeyHeld(SDL_Keycode key);
void invaderUpdate(UpdateArgs *args);
void invaderRender();

// scrolling background
void scrollBgInit();
void scrollBgUpdate();
void scrollBgRender();

// enemies
Enemy *enemyCreate();
void enemySpawn();
void enemyUpdate(S2D_FRect playerRect);
void enemyRender();
int getEnemyCount();
int getEnemyVectorSize();

#endif // GAME_H
