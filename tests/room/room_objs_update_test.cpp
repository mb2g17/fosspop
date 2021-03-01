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

    class EventFixture : public testing::Test, public testing::WithParamInterface<int>
    {
    private:
        std::vector<UpdateFlagObj *> *updateFlagObjs;

    public:
        Game *game;
        Room *room;

        EventFixture()
        {
            this->updateFlagObjs = new std::vector<UpdateFlagObj *>();

            this->game = new Game();
            this->room = new Room();
            game->setCurrentRoom(this->room);

            this->addUpdateFlagObjs();

            this->game->update();
        }

        ~EventFixture()
        {
            delete this->game;
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

    private:
        void addUpdateFlagObjs()
        {
            const int noOfObjs = GetParam();

            for (int i = 0; i < noOfObjs; i++)
            {
                UpdateFlagObj *obj = new UpdateFlagObj();
                this->room->addObj(obj);
                this->updateFlagObjs->push_back(obj);
            }
        }
    };
}

using namespace RoomObjsUpdateTest;

TEST_P(EventFixture, room_objs_update_test)
{
    EXPECT_TRUE(areAllObjsUpdated());
}

INSTANTIATE_TEST_CASE_P(Default, EventFixture,
                        testing::Values(1, 2, 3, 4, 5));