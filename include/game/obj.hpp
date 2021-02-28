#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Obj
{
    SDL_Texture *tex;
    SDL_Rect dest;

public:
    Obj(SDL_Renderer *, const char *);
    ~Obj();
    virtual void update(SDL_Renderer *);
    void setPos(int x, int y);

protected:
    void draw(SDL_Renderer *);
};