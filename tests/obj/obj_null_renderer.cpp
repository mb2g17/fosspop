#include "game/obj.hpp"

#include "gtest/gtest.h"

TEST(ObjNullRenderer, obj_should_handle_null_renderer)
{
    Obj *obj = new Obj(NULL, "test.png");

    EXPECT_EQ(obj->getWidth(), 0);
    EXPECT_EQ(obj->getHeight(), 0);

    delete obj;
}