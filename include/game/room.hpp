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
    void addObj(Obj *);
    void setBgColor(SDL_Color);

    void onKeyDown(const SDL_KeyboardEvent *);
    void onKeyUp(const SDL_KeyboardEvent *);
    void onMouseMotion(const SDL_MouseMotionEvent *);
    void onMouseButtonDown(const SDL_MouseButtonEvent *);
    void onMouseButtonUp(const SDL_MouseButtonEvent *);

private:
    void draw(SDL_Renderer *);
};