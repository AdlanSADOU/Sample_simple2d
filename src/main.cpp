#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

static S2D_Window *window = NULL;
static sdEntity *entity = NULL;
static S2D_FRect testrect = S2D_FRect {150,150, 100,100};

float speed = 2.f;

typedef struct args {
    char *str = NULL;
    int i = 0;
} update_args;

void move_sprite(SDL_Keycode key)
{
    float x = 0, y = 0;

    switch (key)
    {
    case SDLK_w: --y;
        --testrect.y;
        break;
    case SDLK_a: --x;
        --testrect.x;
        break;
    case SDLK_s: ++y;
        ++testrect.y;
        break;
    case SDLK_d: ++x;
        ++testrect.x;
        break;
    default:
        break;
    }

    float dt = (float)(window->loop_ms/100.0f);
    speed = 13.f;
    printf("float dt: %f\n", dt);
    sdEntityMove(entity, x * speed * dt, y * speed * dt);
}

bool contains = 0;
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
    system("cls");
    update_args *a_args = (update_args *)(args);
    contains = S2D_Intersect_Point_FRect(entity->rect, window->mouse.x, window->mouse.y);
    contains ? printf("Point collision!\n") : 0;
}

    char buffer[20];
void render()
{
    if (S2D_Intersect_FRect(entity->rect, S2D_FRect {150,150, 100,100}) ||
        S2D_Intersect_FRect(entity->rect, testrect) ||
        S2D_Intersect_FRect(testrect, S2D_FRect {150,150, 100,100}))
            printf("intersects!\n");

    S2D_DrawRect(S2D_FRect {150,150, 100,100}, S2D_Color {1.f, .2f,.2f, 1.f}, true);
    S2D_DrawRect(testrect, S2D_Color {.2f, .9f,.2f, 1.f}, true);

    window->title = SDL_itoa((int)window->fps, buffer, 10);
    sdEntityDraw(entity, true);
}

int main(int argc, char const *argv[])
{
    update_args u_args;
    // u_args.str = "is it working?";
    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->on_update_args = (&u_args);
    window->vsync = false;
    window->on_key = sdOnKeyCallback;
    window->background = { .12, .10, .10};
    window->fps_cap = 9999;
    window->viewport.mode = S2D_SCALE;

    entity = sdEntityCreate("assets/profile.png");

    if (entity && entity->sprite) {
        sdEntitySetSize(entity, 128, 128);
        sdEntitySetPosition(entity, 0,0);
        sdEntityMove(entity, 10,10);
    } else printf("could not load sprite\n");

    S2D_Show(window);
    return 0;
}
