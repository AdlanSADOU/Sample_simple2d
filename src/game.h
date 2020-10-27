#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

typedef struct {
    S2D_SpriteF *sprite;
    S2D_FRect rect;
    S2D_Vec2f position;
} sdEntity;

// function decl: sdEntity 
sdEntity *sdEntityCreate(const char *path);
void sdEntitySetSize(sdEntity *entity, int width, int height);
void sdEntityMove(sdEntity *entity, float x, float y);
void sdEntitySetPosition(sdEntity *entity, float x, float y);

#endif // GAME_H
