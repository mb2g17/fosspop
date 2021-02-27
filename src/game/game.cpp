#include <iostream>

#include "game/game.hpp"
#include "game/obj.hpp"

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

    this->renderer = renderer;
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    IMG_Quit();
    SDL_Quit();
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

SDL_Renderer *Game::getRenderer()
{
    return this->renderer;
}

void Game::processInput()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            this->currentRoom->onKeyDown(&event.key);
            break;
        case SDL_KEYUP:
            this->currentRoom->onKeyUp(&event.key);
            break;
        case SDL_MOUSEMOTION:
            this->currentRoom->onMouseMotion(&event.motion);
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->currentRoom->onMouseButtonDown(&event.button);
            break;
        case SDL_MOUSEBUTTONUP:
            this->currentRoom->onMouseButtonUp(&event.button);
            break;
        }
    }
}