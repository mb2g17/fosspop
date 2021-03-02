#include <SDL2/SDL.h>

#include "game/game.hpp"
#include "game/room.hpp"

#include "gtest/gtest.h"

namespace GameUpdateRoomTest
{
    class TestRoom : public Room
    {
    public:
        bool updated = false;
        TestRoom() { this->updated = true; }
    };

    class GameUpdateRoomFixture : public testing::Test
    {
    public:
        Game *game;
        TestRoom *room;
        SDL_Surface *surface;

        GameUpdateRoomFixture()
        {
            this->surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(this->surface);

            this->game = new Game(renderer);
            this->room = new TestRoom();
            game->setCurrentRoom(this->room);

            game->update();
        }

        ~GameUpdateRoomFixture()
        {
            SDL_FreeSurface(this->surface);
            delete this->game;
        }
    };
}

using namespace GameUpdateRoomTest;

TEST_F(GameUpdateRoomFixture, game_should_update_current_room)
{
    EXPECT_TRUE(room->updated);
}