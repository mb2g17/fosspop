#include <iostream>
#include <string>

#include "assets/textures.hpp"

#include <SDL2/SDL_image.h>

Textures *Textures::instance = 0;

SDL_Texture *Textures::getTileTexture(int tile)
{
    return tileTextures[tile];
}

void Textures::setTextures(SDL_Renderer *renderer, const char *packName)
{
    freeTextures();
    updateTextures(renderer, packName);
}

void Textures::freeTextures()
{
    if (!initialised)
        return;

    for (auto i = 0; i < 7; i++)
    {
        SDL_DestroyTexture(tileTextures[i]);
        tileTextures[i] = nullptr;
    }
}

void Textures::updateTextures(SDL_Renderer *renderer, const char *packName)
{
    const char *filenames[7] = {
        "blue.fw.png",
        "green.fw.png",
        "orange.fw.png",
        "pink.fw.png",
        "purple.fw.png",
        "red.fw.png",
        "yellow.fw.png"};

    initialised = true;
    for (auto i = 0; i < 7; i++)
    {
        std::string path;
        path.append("assets/");
        path.append(packName);
        path.append("/");
        path.append(filenames[i]);

        auto image = IMG_Load(path.c_str());
        this->tileTextures[i] = SDL_CreateTextureFromSurface(renderer, image);
    }
}