#include "game.h"

// SDL_main.h is included automatically from SDL.h
#ifdef main
#undef main
#endif

static S2D_Window *window = NULL;
static sdEntity *entity = NULL;

S2D_FRect testrect = S2D_FRect {150,150, 100,100};

float speed = 2.f;

typedef struct args {
    char *str = NULL;
    int i = 0;
} update_args;

bool S2D_FRect_Intersect(S2D_FRect rect1, S2D_FRect rect2)
{
    float r1x = rect1.x + rect1.width;
    float r1y = rect1.y - rect1.height;
    float r2x = rect2.x + rect2.width;
    float r2y = rect2.y - rect2.height;

    if (rect1.x >= r2x || rect2.x >= r1x) 
        return false; 

    if (rect1.y <= r2y || rect2.y <= r1y) 
        return false; 

    return true;
}

bool sdContainsPointRect(S2D_FRect rect, int point_x, int point_y)
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

void sdEntityDraw(sdEntity *entity, bool debugMode)
{
    S2D_FRect rect = entity->rect;

    GLfloat x1 = rect.x,                y1 = rect.y;
    GLfloat x2 = rect.x + rect.width,   y2 = rect.y;
    GLfloat x3 = rect.x + rect.width,   y3 = rect.y + rect.height;
    GLfloat x4 = rect.x,                y4 = rect.y + rect.height;

    S2D_Color color = { 1.0, 0.5, 0.5, 1.0 };

    // S2D_DrawSprite(entity->sprite);
    S2D_DrawSpriteF(entity->sprite);

    // S2D_DrawQuad()
    S2D_DrawRect(rect, color, true);
}

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
    uint32_t dt = window->loop_ms;
    printf("ms: %d\n", dt);
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
    update_args *a_args = (update_args *)(args);
    // system("cls");
    contains = sdContainsPointRect(entity->rect, window->mouse.x, window->mouse.y);
    // contains ? printf("%d: %s (%f, %f)\n", ++(a_args->i), a_args->str, entity->rect.x, entity->rect.y) : 0;
}

void render()
{
    // sdEntityDraw(entity, true);
    printf("x : %f\n y + height : %f\n", entity->rect.x, entity->rect.y - entity->rect.height);
    if (S2D_FRect_Intersect(testrect, S2D_FRect {150,150, 100,100}))
        printf("intersects!\n");
    S2D_DrawRect(S2D_FRect {150,150, 100,100}, S2D_Color {1.f, .2f,.2f, 1.f}, true);
    S2D_DrawRect(testrect, S2D_Color {.2f, .9f,.2f, 1.f}, true);
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
    window->fps_cap = 30;

    entity = sdEntityCreate("assets/profile.png");

    if (entity && entity->sprite) {
        sdEntitySetPosition(entity, 0,0);
        sdEntitySetSize(entity, 128, 128);
        // sdEntityMove(entity, 50, 50);
    } else printf("could not load sprite\n");



    S2D_Show(window);
    return 0;
}
