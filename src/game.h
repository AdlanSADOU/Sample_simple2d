#if !defined(GAME_H)
#define GAME_H

#include "simple2d.h"

typedef struct {
    S2D_Sprite *sprite;
    S2D_IRect rect;
    S2D_Vec2i position;
} sdEntity;

// function decl: sdEntity 
sdEntity *sdEntityCreate(const char *path);
void sdEntitySetSize(sdEntity *entity, int width, int height);
void sdEntityMove(sdEntity *entity, int x, int y);
void sdEntitySetPosition(sdEntity *entity, int x, int y);

#endif // GAME_H
