#include <SDL2/SDL.h>

#include "game/game.hpp"
#include "game/obj.hpp"

#include "gtest/gtest.h"

namespace ObjLoadAssetTest
{
    class ObjLoadAssetFixture : public testing::Test
    {
    public:
        SDL_Surface *surface;
        Game *game;
        Obj *obj;

        ObjLoadAssetFixture()
        {
            this->surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(this->surface);

            this->game = new Game(renderer);
            this->obj = new Obj(renderer, "assets/windows.fw.png");
        }

        ~ObjLoadAssetFixture()
        {
            SDL_FreeSurface(this->surface);
            delete this->game;
        }
    };
}

using namespace ObjLoadAssetTest;

TEST_F(ObjLoadAssetFixture, obj_should_load_given_asset)
{
    EXPECT_EQ(this->obj->getWidth(), 2);
    EXPECT_EQ(this->obj->getHeight(), 2);
}