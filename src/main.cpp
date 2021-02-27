#include <string>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <emscripten.h>

#include "game/game.hpp"
#include "test/test_room.hpp"

void loop_handler(void *arg)
{
    Game *game = (Game *)arg;
    game->update();
}

int main(int argc, char **argv)
{
    // Sets game
    Game *game = new Game();

    TestRoom *testRoom = new TestRoom(game->getRenderer());
    game->setCurrentRoom(testRoom);

    // Starts loop
    emscripten_set_main_loop_arg(loop_handler, game, -1, 1);

    IMG_Quit();
    SDL_Quit();

    return 0;
}