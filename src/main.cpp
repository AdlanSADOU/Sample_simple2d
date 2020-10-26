#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

static S2D_Window *window = NULL;
static sdEntity *entity = NULL;
float speed = 2.f;

typedef struct args {
    char *str = NULL;
    int i = 0;
} update_args;

bool sdContainsPointRect(S2D_IRect rect, int point_x, int point_y)
{
    // printf("rect(%d, %d)\nmous(%d, %d)\n", rect.x, rect.y, point_x, point_y);
    static int i = 0;

    bool topLeft = (point_x >= rect.x);
    bool bottomLeft = (point_y >= rect.y);
    bool topRight = (point_x <= (rect.x + rect.width));
    bool bottomRight = (point_y <= (rect.y + rect.height));

    if (topLeft && topRight && bottomLeft && bottomRight) {
        printf("%d: collides!\n", ++i);
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
void sdOnKeyCallback(S2D_Event e)
{
    SDL_Keycode key = SDL_GetKeyFromName(e.key);

    switch (e.type) {
        case S2D_KEY_UP: key == SDLK_ESCAPE ? S2D_Close(window) : 0;
            break;

        case S2D_KEY_HELD: contains ? move_sprite(key) : 0;
            break;

        default:
        break;
    }
}

void update(void* args)
{
    update_args *a_args = (update_args *)(args);

    contains = sdContainsPointRect(entity->rect, window->mouse.x, window->mouse.y);
    contains ? printf("%d: %s\n", ++(a_args->i), a_args->str) : 0;
}

void sdEntityDraw(sdEntity *entity, bool debugMode)
{
    S2D_IRect rect = entity->rect;

    GLfloat x1 = rect.x,                  y1 = rect.y;
    GLfloat x2 = (rect.x + rect.width),   y2 = (rect.y);
    GLfloat x3 = (rect.x + rect.width),   y3 = (rect.y + rect.height);
    GLfloat x4 = (rect.x),                y4 = (rect.y + rect.height);

    S2D_Color color = { 1.0, 0.5, 0.5, 1.0 };

    S2D_DrawQuad(
        x1, y1,   color.r, color.g, color.b, color.a,
        x2, y2,   color.r, color.g, color.b, color.a,
        x3, y3,   color.r, color.g, color.b, color.a,
        x4, y4,   color.r, color.g, color.b, color.a
    );
    // S2D_DrawSprite(entity->sprite);
}

void render()
{
    sdEntityDraw(entity, true);
}


int main(int argc, char const *argv[])
{
    update_args u_args;
    u_args.str = "is it working?";

    window = S2D_CreateWindow("Awesome Sample", 800, 600, update, render, S2D_RESIZABLE);
    window->on_update_args = (&u_args);
    window->vsync = false;
    window->on_key = sdOnKeyCallback;
    window->background = { .12, .10, .10};

    entity = sdEntityCreate("assets/profile.png");
    
    if (entity && entity->sprite) {
        sdEntitySetSize(entity, 128, 128);
        sdEntityMove(entity, 50, 50);
    } else printf("could not load sprite\n");

    S2D_Show(window);
    return 0;
}
