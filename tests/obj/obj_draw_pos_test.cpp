#include <SDL2/SDL.h>

#include "game/game.hpp"
#include "game/obj.hpp"

#include "gtest/gtest.h"

namespace ObjDrawPosTest
{
    struct PixelData
    {
        Uint32 topleft, topright, bottomleft, bottomright;
    };

    class ObjDrawPosFixture : public testing::Test
    {
    public:
        SDL_Surface *surface;
        Game *game;
        Obj *obj;

        ObjDrawPosFixture()
        {
            Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
#else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
#endif
            this->surface = SDL_CreateRGBSurface(0, 8, 8, 32, rmask, gmask, bmask, amask);

            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(this->surface);

            this->game = new Game(renderer);
            Room *room = new Room();
            this->game->setCurrentRoom(room);

            Obj *obj = new Obj(renderer, "assets/windows.fw.png");
            obj->setPos(2, 4);
            room->addObj(obj);

            this->game->update();
        }

        ~ObjDrawPosFixture()
        {
            SDL_FreeSurface(this->surface);
            delete this->game;
        }

        PixelData getPixels()
        {
            auto pixels = (Uint32 *)this->surface->pixels;

            PixelData pixelData{
                .topleft = pixels[this->surface->w * 4 + 2],
                .topright = pixels[this->surface->w * 4 + 3],
                .bottomleft = pixels[this->surface->w * 5 + 2],
                .bottomright = pixels[this->surface->w * 5 + 3]};

            return pixelData;
        }
    };
}

using namespace ObjDrawPosTest;

TEST_F(ObjDrawPosFixture, obj_should_draw_at_position)
{
    Uint32 red, green, blue, yellow;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    red = 0xff0000ff;
    green = 0x00ff00ff;
    blue = 0x0000ffff;
    yellow = 0xffff00ff;
#else
    red = 0xff0000ff;
    green = 0xff00ff00;
    blue = 0xffff0000;
    yellow = 0xff00ffff;
#endif

    PixelData pixelData = getPixels();
    EXPECT_EQ(pixelData.topleft, red);
    EXPECT_EQ(pixelData.topright, green);
    EXPECT_EQ(pixelData.bottomleft, blue);
    EXPECT_EQ(pixelData.bottomright, yellow);
}