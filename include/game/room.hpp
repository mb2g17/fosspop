#pragma once

#include <vector>

#include "game/obj.hpp"

class Room
{
    std::vector<Obj *> *objects;
    SDL_Color bgColor = {.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF};

public:
    Room();
    ~Room();
    void update(SDL_Renderer *);

    void addObj(Obj *);

    void setBgColor(SDL_Color);

    virtual void onKeyDown(const SDL_KeyboardEvent *);
    virtual void onKeyUp(const SDL_KeyboardEvent *);
    virtual void onMouseMotion(const SDL_MouseMotionEvent *);
    virtual void onMouseButtonDown(const SDL_MouseButtonEvent *);
    virtual void onMouseButtonUp(const SDL_MouseButtonEvent *);

private:
    void draw(SDL_Renderer *);
};