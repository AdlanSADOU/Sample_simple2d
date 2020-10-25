#include "simple2d.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

struct sfSprite
{
    S2D_Sprite *S2D_sprite = NULL;
    S2D_FRect rect;
    S2D_Vec2f position;
};

S2D_Window *window = NULL;
S2D_Sprite *sprite = NULL;
float speed = 2.f;

void contains_point_rect(S2D_FRect rect, S2D_Vec2f vec)
{
    
}

void move_sprite(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_w:
        (sprite->y) -= 1 * speed;
        break;
    case SDLK_a:
        (sprite->x) -= 1 * speed;
        break;
    case SDLK_s:
        (sprite->y) += 1 * speed;
    break;
    case SDLK_d:
        (sprite->x) += 1 * speed;
        break;
    default:
        break;
    }
}

void on_key(S2D_Event e) 
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);

    switch (e.type)
    {
    case S2D_KEY_UP: 
        key == SDLK_ESCAPE ? S2D_Close(window) : 0;
    break;
    case S2D_KEY_HELD:
        move_sprite(key);
    break;
    
    default:
        break;
    }
}

void update()
{
    printf("mouse (%d, %d)\n", window->mouse.x, window->mouse.y);
}

void render()
{
    S2D_DrawSprite(sprite);
}

int main(int argc, char const *argv[])
{
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->vsync = false;
    window->on_key = on_key;

    sprite = S2D_CreateSprite("assets/profile.png");
    if (sprite) {
        sprite->width = 128;
        sprite->height = 128;
    } else printf("could not load sprite\n");

    S2D_Show(window);
    return 0;
}
