#include <iostream>

#include "game/game.hpp"
#include "game/obj.hpp"

Game::Game(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
}

void Game::update()
{
    this->currentRoom->update(this->renderer);
}

void Game::setCurrentRoom(Room *newRoom)
{
    delete this->currentRoom;
    this->currentRoom = newRoom;
}