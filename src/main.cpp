#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <emscripten.h>

#include "game/game.hpp"

/**
 * Inverse square root of two, for normalising velocity
 */
#define REC_SQRT2 0.7071067811865475

/**
 * Set of input states
 */
enum input_state
{
    NOTHING_PRESSED = 0,
    UP_PRESSED = 1,
    DOWN_PRESSED = 1 << 1,
    LEFT_PRESSED = 1 << 2,
    RIGHT_PRESSED = 1 << 3
};

/**
 * Context structure that will be passed to the loop handler
 */
typedef struct Context
{
    Game *game;

    SDL_Renderer *renderer;

    /**
     * Rectangle that the texture will be rendered into
     */
    SDL_Rect dest;
    SDL_Texture *tex;

    input_state active_state;

    /**
     * x and y components of velocity
     */
    int vx;
    int vy;
} Context;

/**
 * Processes the input events and sets the velocity
 * of the owl accordingly
 */
void process_input(Context *ctx)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            if (event.key.type == SDL_KEYDOWN)
                ctx->active_state = (enum input_state)(ctx->active_state | UP_PRESSED);
            else if (event.key.type == SDL_KEYUP)
                ctx->active_state = (enum input_state)(ctx->active_state ^ UP_PRESSED);
            break;
        case SDLK_DOWN:
            if (event.key.type == SDL_KEYDOWN)
                ctx->active_state = (enum input_state)(ctx->active_state | DOWN_PRESSED);
            else if (event.key.type == SDL_KEYUP)
                ctx->active_state = (enum input_state)(ctx->active_state ^ DOWN_PRESSED);
            break;
        case SDLK_LEFT:
            if (event.key.type == SDL_KEYDOWN)
                ctx->active_state = (enum input_state)(ctx->active_state | LEFT_PRESSED);
            else if (event.key.type == SDL_KEYUP)
                ctx->active_state = (enum input_state)(ctx->active_state ^ LEFT_PRESSED);
            break;
        case SDLK_RIGHT:
            if (event.key.type == SDL_KEYDOWN)
                ctx->active_state = (enum input_state)(ctx->active_state | RIGHT_PRESSED);
            else if (event.key.type == SDL_KEYUP)
                ctx->active_state = (enum input_state)(ctx->active_state ^ RIGHT_PRESSED);
            break;
        default:
            break;
        }
    }

    ctx->vy = 0;
    ctx->vx = 0;
    if (ctx->active_state & UP_PRESSED)
        ctx->vy = -5;
    if (ctx->active_state & DOWN_PRESSED)
        ctx->vy = 5;
    if (ctx->active_state & LEFT_PRESSED)
        ctx->vx = -5;
    if (ctx->active_state & RIGHT_PRESSED)
        ctx->vx = 5;

    if (ctx->vx != 0 && ctx->vy != 0)
    {
        ctx->vx *= REC_SQRT2;
        ctx->vy *= REC_SQRT2;
    }
}

void loop_handler(void *arg)
{
    Context *ctx = (Context *)arg;

    ctx->game->update();

    /*int vx = 0;
    int vy = 0;
    process_input(ctx);

    ctx->dest.x += ctx->vx;
    ctx->dest.y += ctx->vy;

    SDL_RenderClear(ctx->renderer);
    SDL_RenderCopy(ctx->renderer, ctx->tex, NULL, &ctx->dest);

    SDL_Rect rect;
    rect.x = ctx->dest.x + 150;
    rect.y = ctx->dest.y + 150;
    rect.w = ctx->dest.w;
    rect.h = ctx->dest.h;
    SDL_RenderCopy(ctx->renderer, ctx->tex, NULL, &rect);*/

    SDL_RenderPresent(ctx->renderer);
}

#include <string>
int main(int argc, char **argv)
{
    printf("Started!!\n");

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window;
    Context ctx;

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &ctx.renderer);

    SDL_SetRenderDrawColor(ctx.renderer, 128, 0, 0, 255);
    SDL_RenderClear(ctx.renderer);
    SDL_RenderPresent(ctx.renderer);

    // Gets image
    SDL_Surface *image = IMG_Load("assets/helloworld.png");
    ctx.tex = SDL_CreateTextureFromSurface(ctx.renderer, image);
    ctx.dest.w = image->w;
    ctx.dest.h = image->h;
    SDL_FreeSurface(image);

    // Sets initial state
    ctx.active_state = NOTHING_PRESSED;
    ctx.dest.x = 200;
    ctx.dest.y = 100;
    ctx.vx = 0;
    ctx.vy = 0;

    // Sets game
    Game *game = new Game(ctx.renderer);
    Room *room = new Room();
    game->setCurrentRoom(room);

    const char *filenames[7] = {
        "assets/blue.fw.png",
        "assets/green.fw.png",
        "assets/orange.fw.png",
        "assets/pink.fw.png",
        "assets/purple.fw.png",
        "assets/red.fw.png",
        "assets/yellow.fw.png"};

    for (int i = 0; i < 7; i++)
    {
        Obj *obj = new Obj(ctx.renderer, filenames[i]);
        obj->setPos(50 * i, 50 * i);
        room->addObj(obj);
    }

    /*Obj *obj1 = new Obj(ctx.renderer, "assets/blue.fw.png");
    game->addObj(obj1);

    Obj *obj2 = new Obj(ctx.renderer, "assets/green.fw.png");
    obj2->setPos(50, 50);
    game->addObj(obj2);

    Obj *obj3 = new Obj(ctx.renderer, "assets/red.fw.png");
    obj3->setPos(100, 100);
    game->addObj(obj3);*/

    ctx.game = game;

    // Starts loop
    emscripten_set_main_loop_arg(loop_handler, &ctx, -1, 1);

    IMG_Quit();
    SDL_Quit();

    return 0;
}