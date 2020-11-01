#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

S2D_Window *gWindow;
S2D_Text *fps;
float gSpeed = .9f;
float gDeltaTime = 0.f;

void axisInput(SDL_Keycode key)
{

    switch (key) {
    case SDLK_w: (yAxis) -= gDeltaTime * gSpeed;
        break;
    case SDLK_a: (xAxis) -= gDeltaTime * gSpeed;
        break;
    case SDLK_s: (yAxis) += gDeltaTime * gSpeed;
        break;
    case SDLK_d: (xAxis) += gDeltaTime * gSpeed;
        break;
    case SDLK_SPACE:
        (yAxis > 0)? ((yAxis) -= gDeltaTime * gSpeed) : ((yAxis) += gDeltaTime * gSpeed);
        (xAxis > 0)? ((xAxis) -= gDeltaTime * gSpeed) : ((xAxis) += gDeltaTime * gSpeed);
        break;
    default:
        break;
    }
}

void sdOnKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);
    switch (e.type) {
        case S2D_KEY_UP: key == SDLK_ESCAPE ? S2D_Close(gWindow) : 0;
            break;

        case S2D_KEY_HELD: 
            axisInput(key);
            invaderOnKeyHeld(key);
            break;
        default:
        break;
    }
}

void update(void* args)
{
    UpdateArgs *a_args = (UpdateArgs *)(args);

    S2D_SetText(fps, "FPS: %.2f ms: %.2f", gWindow->fps, gDeltaTime);
    gDeltaTime = (float)(gWindow->loop_ms/100.0f);

    invaderUpdate(a_args);
}

void render()
{
    invaderRender();
    S2D_DrawText(fps);
}

int main(int argc, char const *argv[])
{
    UpdateArgs u_args;
    gWindow = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    gWindow->background      = { .12f, .10f, .10f};
    gWindow->on_UpdateArgs  = (&u_args);
    gWindow->viewport.mode   = S2D_SCALE;
    gWindow->on_key          = sdOnKeyCallback;
    gWindow->fps_cap         = 60;
    
    fps = S2D_CreateText("assets/PixelSpaceRage/fonts/space_invaders.ttf", "Hello Space!", 20);
    invaderInit();

    S2D_Show(gWindow);
    return 0;
}
