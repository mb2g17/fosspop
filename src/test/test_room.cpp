#include <random>

#include "test/test_room.hpp"

SDL_Renderer *my_renderer;

TestRoom::TestRoom(SDL_Renderer *renderer)
{
    my_renderer = renderer;

    // Sets bg color
    this->setBgColor({.r = 0xBF, .g = 0x00, .b = 0xFF, .a = 0xFF});

    // Sets grid
    grid = new Grid();
    grid->init();

    // Sets up objs
    const char *filenames[7] = {
        "assets/blue.fw.png",
        "assets/green.fw.png",
        "assets/orange.fw.png",
        "assets/pink.fw.png",
        "assets/purple.fw.png",
        "assets/red.fw.png",
        "assets/yellow.fw.png"};

    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int i = grid->getTile(row, col);

            Obj *obj = new Obj(renderer, filenames[i]);
            obj->setPos(70 * col, 70 * row);
            this->addObj(obj);
        }
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

unsigned int x, y;

void TestRoom::onMouseMotion(const SDL_MouseMotionEvent *mouseMotionEvent)
{
    /*printf("mouse motion x: %d, y: %d, xrel: %d, yrel: %d\n", mouseMotionEvent->x, mouseMotionEvent->y, mouseMotionEvent->xrel, mouseMotionEvent->yrel);

    if (mouseMotionEvent->state & SDL_BUTTON_LMASK)
    {
        printf("Dragging with left mouse button\n");
    }*/
}

void TestRoom::onMouseButtonDown(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    if (mouseButtonEvent->button == SDL_BUTTON_LEFT)
    {
        x = mouseButtonEvent->x / 70;
        y = mouseButtonEvent->y / 70;
        printf("DOWN X: %d, Y: %d\n", x, y);
    }
    /*
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
    printf("Mouse button down %s\n", buttonStr);*/
}

void TestRoom::onMouseButtonUp(const SDL_MouseButtonEvent *mouseButtonEvent)
{
    if (mouseButtonEvent->button == SDL_BUTTON_LEFT)
    {
        unsigned int newX = mouseButtonEvent->x / 70;
        unsigned int newY = mouseButtonEvent->y / 70;

        grid->swap(y, x, newY, newX);

        printf("UP X: %d, Y: %d\n", newX, newY);

        objects->clear();

        // Sets up objs
        const char *filenames[7] = {
            "assets/blue.fw.png",
            "assets/green.fw.png",
            "assets/orange.fw.png",
            "assets/pink.fw.png",
            "assets/purple.fw.png",
            "assets/red.fw.png",
            "assets/yellow.fw.png"};

        for (int row = 0; row < 7; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                int i = grid->getTile(row, col);

                Obj *obj = new Obj(my_renderer, filenames[i]);
                obj->setPos(70 * col, 70 * row);
                this->addObj(obj);
            }
        }
    }
    /*const char *buttonStr = NULL;
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
    printf("Mouse button up %s\n", buttonStr);*/
}