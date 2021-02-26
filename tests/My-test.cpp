#include "gtest/gtest.h"

#include "game/game.hpp"
#include "game/room.hpp"

class TestRoom : public Room
{
public:
    int count = 0;
    void onKeyDown(const SDL_KeyboardEvent *) override
    {
        this->count++;
    }
};

struct State
{
    int testRoomCount;
};

State arrange();
void destroy();

TEST(blaTest, test1)
{
    State state = arrange();

    EXPECT_EQ(state.testRoomCount, 2);

    destroy();
}

State arrange()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

    Game *game = new Game(renderer);
    TestRoom *testRoom = new TestRoom();
    game->setCurrentRoom(testRoom);

    // Push events
    SDL_Event event;
    event.type = SDL_KEYDOWN;
    SDL_PushEvent(&event);
    SDL_PushEvent(&event);

    // Run update
    game->update();

    State rv{.testRoomCount = testRoom->count};
    return rv;
}

void destroy()
{
    SDL_Quit();
}