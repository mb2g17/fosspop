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
    class EventFixture : public testing::Test, public testing::WithParamInterface<int>
    {
    public:
        Game *game;
        TestRoom *room;

        EventFixture()
        {
            this->game = new Game();
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

        ~EventFixture()
        {
            delete this->game;
        }
    };
}

using namespace RoomEventTest;

#define TEST_EVENT(EVENT_ENUM, EVENT_FIXTURE_NAME, EVENT_PROPERTY, TEST_NAME) \
    struct EVENT_FIXTURE_NAME : public EventFixture<EVENT_ENUM>               \
    {                                                                         \
    };                                                                        \
    TEST_P(EVENT_FIXTURE_NAME, TEST_NAME)                                     \
    {                                                                         \
        EXPECT_EQ(room->EVENT_PROPERTY, GetParam());                          \
    }                                                                         \
    INSTANTIATE_TEST_CASE_P(Default, EVENT_FIXTURE_NAME,                      \
                            testing::Values(1, 2, 3, 4, 5));

TEST_EVENT(SDL_KEYDOWN, KeyDownFixture, keyDownCount, room_should_handle_keydown_events)
TEST_EVENT(SDL_KEYUP, KeyUpFixture, keyUpCount, room_should_handle_keyup_events)
TEST_EVENT(SDL_MOUSEMOTION, MouseMotionFixture, mouseMotionCount, room_should_handle_mousemotion_events)
TEST_EVENT(SDL_MOUSEBUTTONDOWN, MouseButtonDownFixture, mouseButtonDownCount, room_should_handle_mousebuttondown_events)
TEST_EVENT(SDL_MOUSEBUTTONUP, MouseButtonUpFixture, mouseButtonUpCount, room_should_handle_mousebuttonup_events)