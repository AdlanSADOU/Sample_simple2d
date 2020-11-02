#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

S2D_Window *gWindow;
S2D_Text *fps;

float gDeltaTime = 0.f;

void axisInput(SDL_Keycode key)
{
    switch (key)
    {
    case SDLK_w:
        (yAxis) -= gDeltaTime * gSpeed;
        break;
    case SDLK_a:
        (xAxis) -= gDeltaTime * gSpeed;
        break;
    case SDLK_s:
        (yAxis) += gDeltaTime * gSpeed;
        break;
    case SDLK_d:
        (xAxis) += gDeltaTime * gSpeed;
        break;
    case SDLK_LSHIFT:
        (yAxis > 0) ? ((yAxis) -= gSpeed) : ((yAxis) += gSpeed);
        (xAxis > 0) ? ((xAxis) -= gSpeed) : ((xAxis) += gSpeed);
        break;
    default:
        break;
    }
}

void sdOnKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);
    switch (e.type)
    {
    case S2D_KEY_UP:
        key == SDLK_ESCAPE ? S2D_Close(gWindow) : 0;
        break;

    case S2D_KEY_HELD:
        //axisInput(key);
        invaderOnKeyHeld(key);
        break;
    default:
        break;
    }
}

void update(void *args)
{
    UpdateArgs *a_args = (UpdateArgs *)(args);

    gDeltaTime = ((1/gWindow->fps)*1000);
    S2D_SetText(fps, "FPS: %.2f  //  1/FPS: %.2f  //  ms: %d", gWindow->fps, gDeltaTime, gWindow->loop_ms);

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
    gWindow = S2D_CreateWindow("Awesome Sample", 1280, 720, update, render, S2D_HIGHDPI);
    gWindow->vsync = false;
    gWindow->background = {.12f, .10f, .10f};
    gWindow->on_UpdateArgs = (&u_args);
    gWindow->viewport.mode = 3;
    gWindow->on_key = sdOnKeyCallback;
    gWindow->fps_cap = 120;

    fps = S2D_CreateText("assets/PixelSpaceRage/fonts/space_invaders.ttf", "Hello Space!", 20);
    fps->color = {0.1f, 0.8f,0.1f, 0.9f};
    fps->x = 20;

    invaderInit();

    S2D_Show(gWindow);
    return 0;
}
