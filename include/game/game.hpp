#pragma once

#include <vector>

#include "game/obj/obj.hpp"

class Game
{
    SDL_Renderer *renderer;
    std::vector<Obj *> *objects;

public:
    Game(SDL_Renderer *);
    ~Game();
    void update();

    void addObj(Obj *obj);

private:
    void draw();
};