#include "test/test_room.hpp"

TestRoom::TestRoom(SDL_Renderer *renderer)
{
    // Sets bg color
    this->setBgColor({.r = 0xBF, .g = 0x00, .b = 0xFF, .a = 0xFF});

    // Sets up objs
    const char *filenames[7] = {
        "assets/blue.fw.png",
        "assets/green.fw.png",
        "assets/orange.fw.png",
        "assets/pink.fw.png",
        "assets/purple.fw.png",
        "assets/red.fw.png",
        "assets/yellow.fw.png"};

    for (int i = 0; i < 7; i++)
    {
        Obj *obj = new Obj(renderer, filenames[i]);
        obj->setPos(50 * i, 50 * i);
        this->addObj(obj);
    }
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
    printf("mouse motion x: %d, y: %d, xrel: %d, yrel: %d\n", mouseMotionEvent->x, mouseMotionEvent->y, mouseMotionEvent->xrel, mouseMotionEvent->yrel);

    if (mouseMotionEvent->state & SDL_BUTTON_LMASK)
    {
        printf("Dragging with left mouse button\n");
    }
}

void TestRoom::onMouseButtonDown(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    const char *buttonStr = NULL;
    switch (mouseButtonEvent->button)
    {
    case SDL_BUTTON_LEFT:
        buttonStr = "Left";
        break;
    case SDL_BUTTON_MIDDLE:
        buttonStr = "Middle";
        break;
    case SDL_BUTTON_RIGHT:
        buttonStr = "Right";
        break;
    default:
        buttonStr = "Unknown";
        break;
    }
    printf("Mouse button down %s\n", buttonStr);
}

void TestRoom::onMouseButtonUp(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    const char *buttonStr = NULL;
    switch (mouseButtonEvent->button)
    {
    case SDL_BUTTON_LEFT:
        buttonStr = "Left";
        break;
    case SDL_BUTTON_MIDDLE:
        buttonStr = "Middle";
        break;
    case SDL_BUTTON_RIGHT:
        buttonStr = "Right";
        break;
    default:
        buttonStr = "Unknown";
        break;
    }
    printf("Mouse button up %s\n", buttonStr);
}