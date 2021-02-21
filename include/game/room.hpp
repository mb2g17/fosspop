#pragma once

#include <vector>

#include "game/obj.hpp"

class Room
{
    std::vector<Obj *> *objects;

public:
    Room();
    ~Room();
    void update(SDL_Renderer *);
    void addObj(Obj *obj);

private:
    void draw(SDL_Renderer *);
};