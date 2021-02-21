#include <SDL2/SDL.h>

#include "game/room.hpp"

Room::Room()
{
    this->objects = new std::vector<Obj *>();
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

void Room::draw(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);

    for (auto &object : *this->objects)
        object->draw(renderer);

    SDL_RenderPresent(renderer);
}