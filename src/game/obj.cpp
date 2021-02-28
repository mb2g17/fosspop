#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game/obj.hpp"

Obj::Obj(SDL_Renderer *renderer, const char *path)
{
    if (renderer != NULL)
    {
        SDL_Surface *image = IMG_Load(path);
        this->tex = SDL_CreateTextureFromSurface(renderer, image);
        this->dest.w = image->w;
        this->dest.h = image->h;

        SDL_FreeSurface(image);
    }
    else
        this->tex = NULL;
}

Obj::~Obj()
{
    SDL_DestroyTexture(this->tex);
}

void Obj::update(SDL_Renderer *renderer)
{
    this->draw(renderer);
}

void Obj::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, this->tex, NULL, &this->dest);
}

void Obj::setPos(int x, int y)
{
    this->dest.x = x;
    this->dest.y = y;
}