#include <random>

#include "test/test_room.hpp"
#include "grid/grid_obj.hpp"
#include "assets/textures.hpp"

SDL_Renderer *my_renderer;

TestRoom::TestRoom(SDL_Renderer *renderer)
{
    my_renderer = renderer;

    // Sets textures
    Textures::getInstance().setTextures(renderer, "bevel");

    // Sets bg color
    this->setBgColor({.r = 0xBF, .g = 0x00, .b = 0xFF, .a = 0xFF});

    // Adds background
    this->bg = new Obj(renderer, "assets/game.png");
    this->bg->setPos(34, 34);
    this->addObj(this->bg);

    // Adds grid
    this->gridObj = new GridObj(renderer);
    this->gridObj->setPos(50, 50);
    this->addObj(this->gridObj);
}

void TestRoom::onKeyDown(const SDL_KeyboardEvent *keyboardEvent)
{
    printf("key down: %s\n", SDL_GetKeyName(keyboardEvent->keysym.sym));
}

void TestRoom::onKeyUp(const SDL_KeyboardEvent *keyboardEvent)
{
    printf("key up: %s\n", SDL_GetKeyName(keyboardEvent->keysym.sym));
}

void TestRoom::onMouseMotion(const SDL_MouseMotionEvent *mouseMotionEvent)
{
    SDL_Rect mousePos{
        .x = mouseMotionEvent->x,
        .y = mouseMotionEvent->y};
    this->gridObj->updateMousePos(mousePos);
}

void TestRoom::onMouseButtonDown(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    if (mouseButtonEvent->button == SDL_BUTTON_LEFT)
    {
        this->gridObj->startDrag();
    }
}

void TestRoom::onMouseButtonUp(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    this->gridObj->endDrag();
}