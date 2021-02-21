#include <cstdio>
#include <SDL2/SDL.h>

#include "game/room.hpp"

Room::Room()
{
    this->objects = new std::vector<Obj *>();
    this->bgColor = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};
}

Room::~Room()
{
    this->objects->clear();
    delete this->objects;
}

void Room::update(SDL_Renderer *renderer)
{
    this->draw(renderer);
}

void Room::addObj(Obj *obj)
{
    this->objects->push_back(obj);
}

void Room::setBgColor(SDL_Color Color)
{
    this->bgColor = Color;
}

void Room::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, this->bgColor.r, this->bgColor.g, this->bgColor.b, this->bgColor.a);
    SDL_RenderClear(renderer);

    for (auto &object : *this->objects)
        object->draw(renderer);

    SDL_RenderPresent(renderer);
}

void Room::handleInput(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        printf("pressed: %s\n", SDL_GetKeyName(event->key.keysym.sym));
        break;
    }
}