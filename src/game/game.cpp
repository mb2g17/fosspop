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
    this->processInput();
}

void Game::setCurrentRoom(Room *newRoom)
{
    delete this->currentRoom;
    this->currentRoom = newRoom;
}

void Game::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        this->currentRoom->handleInput(&event);
    }
}