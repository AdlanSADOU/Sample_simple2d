#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

S2D_Window *window;
float speed = .9f;
float dt = 0.f;
S2D_Text *fps;

void move_sprite(SDL_Keycode key)
{

    switch (key) {
    case SDLK_w: (yAxis) -= dt * speed;
        break;
    case SDLK_a: (xAxis) -= dt * speed;
        break;
    case SDLK_s: (yAxis) += dt * speed;
        break;
    case SDLK_d: (xAxis) += dt * speed;
        break;
    case SDLK_SPACE:
        (yAxis > 0)? ((yAxis) -= dt * speed) : ((yAxis) += dt * speed);
        (xAxis > 0)? ((xAxis) -= dt * speed) : ((xAxis) += dt * speed);
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

    S2D_SetText(fps, "FPS: %.2f ms: %.2f", window->fps, dt);
    dt = (float)(window->loop_ms/100.0f);

    invader_update(a_args);
}

void render()
{
    invader_render();
    S2D_DrawText(fps);
}

int main(int argc, char const *argv[])
{
    update_args u_args;
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->background      = { .12f, .10f, .10f};
    window->on_update_args  = (&u_args);
    window->viewport.mode   = S2D_SCALE;
    window->on_key          = sdOnKeyCallback;
    window->fps_cap         = 60;
    
    fps = S2D_CreateText("assets/PixelSpaceRage/fonts/space_invaders.ttf", "Hello Space!", 20);
    // S2D_SetText()
    invader_init();

    S2D_Show(window);
    return 0;
}
