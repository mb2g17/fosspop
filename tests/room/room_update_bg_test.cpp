#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <vector>

#include "game/game.hpp"
#include "game/room.hpp"
#include "game/obj.hpp"

#include "gtest/gtest.h"

namespace RoomUpdateBgTest
{
    class RoomUpdateBgTestFixture : public testing::Test, public testing::WithParamInterface<SDL_Color>
    {
    public:
        Game *game;
        Room *room;
        SDL_Surface *surface;

        RoomUpdateBgTestFixture()
        {
            const SDL_Color color = GetParam();

            this->surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(this->surface);

            this->game = new Game(renderer);
            this->room = new Room();
            game->setCurrentRoom(this->room);

            this->room->setBgColor(color);
            this->game->update();
        }

        ~RoomUpdateBgTestFixture()
        {
            SDL_FreeSurface(this->surface);
            delete this->game;
        }
    };
}

using namespace RoomUpdateBgTest;

TEST_P(RoomUpdateBgTestFixture, room_update_bg_test)
{
    SDL_Color expectedColor = GetParam();

    SDL_Color actualColor;
    SDL_GetRenderDrawColor(game->getRenderer(), &actualColor.r, &actualColor.g, &actualColor.b, &actualColor.a);

    EXPECT_EQ(expectedColor.r, actualColor.r);
    EXPECT_EQ(expectedColor.g, actualColor.g);
    EXPECT_EQ(expectedColor.b, actualColor.b);
    EXPECT_EQ(expectedColor.a, actualColor.a);
}

INSTANTIATE_TEST_CASE_P(Default, RoomUpdateBgTestFixture,
                        testing::Values(
                            SDL_Color{.r = 255, .g = 0, .b = 0, .a = 255},
                            SDL_Color{.r = 0, .g = 255, .b = 0, .a = 255},
                            SDL_Color{.r = 0, .g = 0, .b = 255, .a = 255},
                            SDL_Color{.r = 255, .g = 255, .b = 255, .a = 255},
                            SDL_Color{.r = 0, .g = 0, .b = 0, .a = 255}));