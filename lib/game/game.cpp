#include <iostream>

#include "game/game.hpp"

Game::Game(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->objects = new std::vector<Obj *>();
}

Game::~Game()
{
    this->objects->clear();
    delete this->objects;

    SDL_DestroyRenderer(this->renderer);
}

void Game::update()
{
    this->draw();
}

void Game::addObj(Obj *obj)
{
    this->objects->push_back(obj);
}

void Game::draw()
{
    SDL_RenderClear(this->renderer);

    for (auto &object : *this->objects)
        object->draw(this->renderer);

    SDL_RenderPresent(this->renderer);
}