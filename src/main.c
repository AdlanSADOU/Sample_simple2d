#include "simple2d.h"

S2D_Window *window = NULL;
S2D_Sprite *sprite = NULL;
float speed = 0.4f;

void move_sprite(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_w:
        (sprite->y) -= 1 * speed * window->loop_ms;
        break;
    case SDLK_a:
        (sprite->x) -= 1 * speed * window->loop_ms;
        break;
    case SDLK_s:
        (sprite->y) += 1 * speed * window->loop_ms;
    break;
    case SDLK_d:
        (sprite->x) += 1 * speed * window->loop_ms;
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
    
}

void render()
{
    S2D_DrawSprite(sprite);
}

int main(int argc, char const *argv[])
{
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->on_key = on_key;
    sprite = S2D_CreateSprite("assets/profile.png");

    if (sprite) {
        sprite->width = 128;
        sprite->height = 128;
    } else printf("could not load sprite\n");

    S2D_GL_PrintContextInfo(window);
    printf("Hello Simple2D!\n");
    S2D_Show(window);
    system("dir");
    return 0;
}
