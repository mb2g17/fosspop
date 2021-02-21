#pragma once

#include <vector>

#include "game/obj.hpp"
#include "game/room.hpp"

class Game
{
    SDL_Renderer *renderer;
    Room *currentRoom;

public:
    Game(SDL_Renderer *);
    ~Game();
    void update();
    void setCurrentRoom(Room *);
};