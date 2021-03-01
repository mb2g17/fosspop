#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game/game.hpp"
#include "game/room.hpp"

#include "gtest/gtest.h"

namespace RoomEventTest
{
    class TestRoom : public Room
    {
    public:
        int keyDownCount = 0;
        int keyUpCount = 0;
        int mouseMotionCount = 0;
        int mouseButtonDownCount = 0;
        int mouseButtonUpCount = 0;

        void onKeyDown(const SDL_KeyboardEvent *) override { this->keyDownCount++; }

        void onKeyUp(const SDL_KeyboardEvent *) override { this->keyUpCount++; }

        void onMouseMotion(const SDL_MouseMotionEvent *) override { this->mouseMotionCount++; }

        void onMouseButtonDown(const SDL_MouseButtonEvent *) override { this->mouseButtonDownCount++; }

        void onMouseButtonUp(const SDL_MouseButtonEvent *) override { this->mouseButtonUpCount++; }
    };

    template <int event_type>
    class RoomEventFixture : public testing::Test, public testing::WithParamInterface<int>
    {
    public:
        Game *game;
        TestRoom *room;
        SDL_Surface *surface;

        RoomEventFixture()
        {
            this->surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
            SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(this->surface);

            this->game = new Game(renderer);
            this->room = new TestRoom();
            game->setCurrentRoom(this->room);

            // Push events
            SDL_Event event{.type = event_type};
            auto noOfEvents = GetParam();

            for (int i = 0; i < noOfEvents; i++)
                SDL_PushEvent(&event);

            // Handle events
            game->update();
        }

        ~RoomEventFixture()
        {
            SDL_FreeSurface(this->surface);
            delete this->game;
        }
    };
}

using namespace RoomEventTest;

#define TEST_EVENT(EVENT_ENUM, EVENT_FIXTURE_NAME, EVENT_PROPERTY, TEST_NAME) \
    struct EVENT_FIXTURE_NAME : public RoomEventFixture<EVENT_ENUM>           \
    {                                                                         \
    };                                                                        \
    TEST_P(EVENT_FIXTURE_NAME, TEST_NAME)                                     \
    {                                                                         \
        EXPECT_EQ(room->EVENT_PROPERTY, GetParam());                          \
    }                                                                         \
    INSTANTIATE_TEST_CASE_P(Default, EVENT_FIXTURE_NAME,                      \
                            testing::Values(1, 2, 3, 4, 5));

TEST_EVENT(SDL_KEYDOWN, RoomEvent_KeyDownFixture, keyDownCount, room_should_handle_keydown_events)
TEST_EVENT(SDL_KEYUP, RoomEvent_KeyUpFixture, keyUpCount, room_should_handle_keyup_events)
TEST_EVENT(SDL_MOUSEMOTION, RoomEvent_MouseMotionFixture, mouseMotionCount, room_should_handle_mousemotion_events)
TEST_EVENT(SDL_MOUSEBUTTONDOWN, RoomEvent_MouseButtonDownFixture, mouseButtonDownCount, room_should_handle_mousebuttondown_events)
TEST_EVENT(SDL_MOUSEBUTTONUP, RoomEvent_MouseButtonUpFixture, mouseButtonUpCount, room_should_handle_mousebuttonup_events)