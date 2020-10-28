#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

typedef struct {
    S2D_Sprite *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
} sdEntity;

// function decl: sdEntity 
sdEntity *sdEntityCreate(const char *path);
void sdEntityDraw(sdEntity *entity, bool debugMode);
void sdEntitySetSize(sdEntity *entity, float width, float height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

#endif // GAME_H
