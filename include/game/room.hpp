#pragma once

#include <vector>

#include "game/obj.hpp"

class Room
{
    std::vector<Obj *> *objects;
    SDL_Color bgColor;

public:
    Room();
    ~Room();
    void update(SDL_Renderer *);
    void addObj(Obj *obj);
    void setBgColor(SDL_Color colour);

private:
    void draw(SDL_Renderer *);
};