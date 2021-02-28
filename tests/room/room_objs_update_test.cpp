#include <numeric>
#include <vector>

#include "game/game.hpp"
#include "game/room.hpp"
#include "game/obj.hpp"

#include "gtest/gtest.h"

namespace RoomObjsUpdateTest
{
    class UpdateFlagObj : public Obj
    {
    public:
        bool updated = false;

        UpdateFlagObj() : Obj(NULL, "") {}
        void update(SDL_Renderer *) override { this->updated = true; }
    };

    class TestRoom : public Room
    {
    private:
        std::vector<UpdateFlagObj *> *updateFlagObjs;

    public:
        TestRoom(int noOfObjs)
        {
            this->updateFlagObjs = new std::vector<UpdateFlagObj *>();

            for (int i = 0; i < noOfObjs; i++)
            {
                UpdateFlagObj *obj = new UpdateFlagObj();
                this->addObj(obj);
                this->updateFlagObjs->push_back(obj);
            }
        }

        ~TestRoom()
        {
            delete this->updateFlagObjs;
        }

        bool areAllObjsUpdated()
        {
            for (std::vector<UpdateFlagObj *>::iterator it = this->updateFlagObjs->begin(); it != this->updateFlagObjs->end(); ++it)
            {
                UpdateFlagObj *obj = *it;
                if (!obj->updated)
                    return false;
            }
            return true;
        }
    };

    class EventFixture : public testing::Test, public testing::WithParamInterface<int>
    {
    public:
        Game *game;
        TestRoom *room;

        EventFixture()
        {
            const int noOfObjs = GetParam();

            this->game = new Game();
            this->room = new TestRoom(noOfObjs);
            game->setCurrentRoom(this->room);

            this->game->update();
        }

        ~EventFixture()
        {
            delete this->game;
        }
    };
}

using namespace RoomObjsUpdateTest;

TEST_P(EventFixture, room_objs_update_test)
{
    EXPECT_TRUE(room->areAllObjsUpdated());
}

INSTANTIATE_TEST_CASE_P(Default, EventFixture,
                        testing::Values(1, 2, 3, 4, 5));