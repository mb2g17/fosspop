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

void Room::onKeyDown(const SDL_KeyboardEvent *keyboardEvent)
{
    printf("key down: %s\n", SDL_GetKeyName(keyboardEvent->keysym.sym));
}

void Room::onKeyUp(const SDL_KeyboardEvent *keyboardEvent)
{
    printf("key up: %s\n", SDL_GetKeyName(keyboardEvent->keysym.sym));
}

void Room::onMouseMotion(const SDL_MouseMotionEvent *mouseMotionEvent)
{
    printf("mouse motion x: %d, y: %d, xrel: %d, yrel: %d\n", mouseMotionEvent->x, mouseMotionEvent->y, mouseMotionEvent->xrel, mouseMotionEvent->yrel);

    if (mouseMotionEvent->state & SDL_BUTTON_LMASK)
    {
        printf("Dragging with left mouse button\n");
    }
}

void Room::onMouseButtonDown(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    const char *buttonStr = NULL;
    switch (mouseButtonEvent->button)
    {
    case SDL_BUTTON_LEFT:
        buttonStr = "Left";
        break;
    case SDL_BUTTON_MIDDLE:
        buttonStr = "Middle";
        break;
    case SDL_BUTTON_RIGHT:
        buttonStr = "Right";
        break;
    default:
        buttonStr = "Unknown";
        break;
    }
    printf("Mouse button down %s\n", buttonStr);
}

void Room::onMouseButtonUp(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    const char *buttonStr = NULL;
    switch (mouseButtonEvent->button)
    {
    case SDL_BUTTON_LEFT:
        buttonStr = "Left";
        break;
    case SDL_BUTTON_MIDDLE:
        buttonStr = "Middle";
        break;
    case SDL_BUTTON_RIGHT:
        buttonStr = "Right";
        break;
    default:
        buttonStr = "Unknown";
        break;
    }
    printf("Mouse button up %s\n", buttonStr);
}