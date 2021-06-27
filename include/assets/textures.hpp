#pragma once

#include <SDL2/SDL.h>

class Textures
{
    static Textures *instance;

    SDL_Texture *tileTextures[7];
    bool initialised;

    Textures()
    {
        for (auto i = 0; i < 7; i++)
            tileTextures[i] = nullptr;
        initialised = false;
    };

public:
    static Textures &getInstance()
    {
        if (!instance)
            instance = new Textures;
        return *instance;
    }

    SDL_Texture *getTileTexture(int tile);
    void setTextures(SDL_Renderer *renderer, const char *packName);

private:
    void freeTextures();
    void updateTextures(SDL_Renderer *renderer, const char *packName);
};