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
            this->surface = SDL_CreateRGBSurfaceWithFormat(0, 8, 8, 32, SDL_PIXELFORMAT_RGBA32);

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
    SDL_Color red = {.r = 255, .g = 0, .b = 0, .a = 255},
              blue = {.r = 0, .g = 0, .b = 255, .a = 255},
              green = {.r = 0, .g = 255, .b = 0, .a = 255},
              yellow = {.r = 255, .g = 255, .b = 0, .a = 255};

    Uint32 redPixel = SDL_MapRGBA(surface->format, red.r, red.g, red.b, red.a),
           greenPixel = SDL_MapRGBA(surface->format, green.r, green.g, green.b, green.a),
           bluePixel = SDL_MapRGBA(surface->format, blue.r, blue.g, blue.b, blue.a),
           yellowPixel = SDL_MapRGBA(surface->format, yellow.r, yellow.g, yellow.b, yellow.a);

    PixelData pixelData = getPixels();
    EXPECT_EQ(pixelData.topleft, redPixel);
    EXPECT_EQ(pixelData.topright, greenPixel);
    EXPECT_EQ(pixelData.bottomleft, bluePixel);
    EXPECT_EQ(pixelData.bottomright, yellowPixel);
}