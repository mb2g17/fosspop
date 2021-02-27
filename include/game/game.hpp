#pragma once

#include <vector>

#include "game/obj.hpp"
#include "game/room.hpp"

class Game
{
    SDL_Renderer *renderer;
    Room *currentRoom;

public:
    Game();
    ~Game();
    void update();
    void setCurrentRoom(Room *);
    SDL_Renderer *getRenderer();

private:
    void processInput();
};