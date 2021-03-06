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

            this->surface = SDL_CreateRGBSurfaceWithFormat(0, 1, 1, 32, SDL_PIXELFORMAT_RGBA32);
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

        Uint32 getPixel()
        {
            auto pixels = (Uint32 *)this->surface->pixels;
            return pixels[0];
        }
    };
}

using namespace RoomUpdateBgTest;

TEST_P(RoomUpdateBgTestFixture, room_should_update_bg)
{
    SDL_Color expectedColor = GetParam();
    Uint32 expectedPixel = SDL_MapRGBA(surface->format, expectedColor.r, expectedColor.g, expectedColor.b, expectedColor.a);

    Uint32 actualPixel = getPixel();

    EXPECT_EQ(expectedPixel, actualPixel);
}

INSTANTIATE_TEST_CASE_P(Default, RoomUpdateBgTestFixture,
                        testing::Values(
                            SDL_Color{.r = 255, .g = 0, .b = 0, .a = 255},
                            SDL_Color{.r = 0, .g = 255, .b = 0, .a = 255},
                            SDL_Color{.r = 0, .g = 0, .b = 255, .a = 255},
                            SDL_Color{.r = 255, .g = 255, .b = 255, .a = 255},
                            SDL_Color{.r = 0, .g = 0, .b = 0, .a = 255}));