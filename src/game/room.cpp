#include <cstdio>
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

void Room::setBgColor(SDL_Color Color)
{
    this->bgColor = Color;
}

void Room::draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, this->bgColor.r, this->bgColor.g, this->bgColor.b, this->bgColor.a);
    SDL_RenderClear(renderer);

    for (auto &object : *this->objects)
        object->update(renderer);

    SDL_RenderPresent(renderer);
}

void Room::onKeyDown(const SDL_KeyboardEvent *keyboardEvent) {}

void Room::onKeyUp(const SDL_KeyboardEvent *keyboardEvent) {}

void Room::onMouseMotion(const SDL_MouseMotionEvent *mouseMotionEvent) {}

void Room::onMouseButtonDown(const SDL_MouseButtonEvent *mouseButtonEvent) {}

void Room::onMouseButtonUp(const SDL_MouseButtonEvent *mouseButtonEvent) {}