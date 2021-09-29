#include "assets/audio.hpp"

Audio *Audio::instance = 0;

Audio::~Audio()
{
    Mix_FreeChunk(negative);
    Mix_FreeChunk(positive);
    Mix_FreeChunk(pink);
    Mix_FreeChunk(maxPink);
    Mix_FreeChunk(morePositive);
    Mix_FreeChunk(ring);
    Mix_FreeChunk(lose);
}

void Audio::playNegative()
{
    playSound(negative);
}

void Audio::playPositive()
{
    playSound(positive);
}

void Audio::playPink()
{
    playSound(pink);
}

void Audio::playMaxPink()
{
    playSound(maxPink);
}

void Audio::playMorePositive()
{
    playSound(morePositive);
}

void Audio::playRing()
{
    playSound(ring);
}

void Audio::playLose()
{
    playSound(lose);
}

Mix_Chunk *Audio::loadSound(const char *path)
{
    auto chunk = Mix_LoadWAV(path);

    if (chunk == nullptr)
        std::cout << "Couldn't load sound " << path << std::endl;

    return chunk;
}

void Audio::playSound(Mix_Chunk *sfx)
{
    if (sfx == nullptr)
    {
        std::cout << "Trying to play nullptr, stopping" << std::endl;
        return;
    }

    if (Mix_PlayChannel(-1, sfx, 0) == -1)
        std::cout << "Failed to play negative sfx" << std::endl;
}