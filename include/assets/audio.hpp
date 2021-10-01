#pragma once

#include <iostream>

#include <SDL2/SDL_mixer.h>

class Audio
{
    static Audio *instance;

    Mix_Chunk *negative;
    Mix_Chunk *positive;
    Mix_Chunk *pink;
    Mix_Chunk *maxPink;
    Mix_Chunk *morePositive;
    Mix_Chunk *ring;
    Mix_Chunk *lose;
    Mix_Chunk *maxMultiplier;
    bool initialised;

    Audio()
    {
        negative = loadSound("assets/sounds/negative.wav");
        positive = loadSound("assets/sounds/positive.wav");
        pink = loadSound("assets/sounds/pink.wav");
        maxPink = loadSound("assets/sounds/maxPink.wav");
        morePositive = loadSound("assets/sounds/morePositive.wav");
        ring = loadSound("assets/sounds/ring.wav");
        lose = loadSound("assets/sounds/lose.wav");
        maxMultiplier = loadSound("assets/sounds/maxMultiplier.wav");

        initialised = false;
    };

    ~Audio();

public:
    static Audio &getInstance()
    {
        if (!instance)
            instance = new Audio;
        return *instance;
    }

    void playNegative();
    void playPositive();
    void playPink();
    void playMaxPink();
    void playMorePositive();
    void playRing();
    void playLose();
    void playMaxMultiplier();

private:
    Mix_Chunk *loadSound(const char *path);
    void playSound(Mix_Chunk *sfx);
};