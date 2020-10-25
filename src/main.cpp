#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

S2D_Window *window = NULL;
sdEntity *entity = NULL;
float speed = 2.f;

bool sdContainsPointRect(S2D_IRect rect, int point_x, int point_y)
{
    printf("rect(%d, %d)\nmous(%d, %d)\n", rect.x, rect.y, point_x, point_y);

    bool topLeft = (point_x >= rect.x);
    bool bottomLeft = (point_y >= rect.y);
    bool topRight = (point_x <= (rect.x + rect.width));
    bool bottomRight = (point_y <= (rect.y + rect.height));

    if (topLeft && topRight &&
        bottomLeft && bottomRight)
    {
        printf("collides!\n");
        return true;
    }
    return false;
}

void move_sprite(SDL_Keycode key)
{
    int x = 0, y = 0;

    switch (key)
    {
    case SDLK_w: --y;
        break;
    case SDLK_a: --x;
        break;
    case SDLK_s: ++y;
        break;
    case SDLK_d: ++x;
        break;
    default:
        break;
    }
    
    sdEntityMove(entity, x * speed, y * speed);
}

bool contains = 0;
void on_key(S2D_Event e) 
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);
    

    switch (e.type)
    {
    case S2D_KEY_UP: 
        key == SDLK_ESCAPE ? S2D_Close(window) : 0;
    break;
    case S2D_KEY_HELD:
        if (contains)
            move_sprite(key);
    break;
    
    default:
        break;
    }
}

void update()
{
    system("cls");
    contains = sdContainsPointRect(entity->rect, window->mouse.x, window->mouse.y);
}

void render()
{
    S2D_DrawSprite(entity->sprite);
}

int main(int argc, char const *argv[])
{
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->vsync = false;
    window->on_key = on_key;

    entity = sdEntityCreate("assets/profile.png");
    if (entity && entity->sprite) {
        sdEntitySetSize(entity, 128, 128);
    } else printf("could not load sprite\n");

    S2D_Show(window);
    return 0;
}
