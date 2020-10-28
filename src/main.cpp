#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

static S2D_Window *window = NULL;

typedef struct args {
    char *str = NULL;
    int i = 0;
} update_args;

float speed = 2.f;

void move_sprite(SDL_Keycode key)
{
    float x = 0, y = 0;
    float dt = (float)(window->loop_ms/100.0f);

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
}

void sdOnKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);

    switch (e.type) {
        case S2D_KEY_UP: key == SDLK_ESCAPE ? S2D_Close(window) : 0;
            break;

        case S2D_KEY_HELD: move_sprite(key);
            break;

        default:
        break;
    }
}

void update(void* args)
{
    update_args *a_args = (update_args *)(args);

}

void render()
{

}

int main(int argc, char const *argv[])
{
    update_args u_args;
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->on_update_args = (&u_args);
    window->on_key = sdOnKeyCallback;
    window->background = { .12, .10, .10};
    window->viewport.mode = S2D_SCALE;

    S2D_Show(window);
    return 0;
}
