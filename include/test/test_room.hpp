#pragma once

#include "game/room.hpp"

class TestRoom : public Room
{
public:
    TestRoom(SDL_Renderer *);

    void onKeyDown(const SDL_KeyboardEvent *) override;
    void onKeyUp(const SDL_KeyboardEvent *) override;
    void onMouseMotion(const SDL_MouseMotionEvent *) override;
    void onMouseButtonDown(const SDL_MouseButtonEvent *) override;
    void onMouseButtonUp(const SDL_MouseButtonEvent *) override;
};