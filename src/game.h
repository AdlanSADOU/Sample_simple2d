#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

extern S2D_Window *window;

extern float xAxis;
extern float yAxis;

typedef struct {
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
} sdEntity;

typedef struct args {
    char *str;
    int i;
} update_args;


// function decl: sdEntity 
sdEntity *sdEntityCreate(const char *path);
void sdEntityDraw(sdEntity *entity, bool debugMode);
void sdEntitySetSize(sdEntity *entity, float width, float height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

// invader 
void invader_init();
void invader_update(update_args *args);
void invader_render();

#endif // GAME_H
