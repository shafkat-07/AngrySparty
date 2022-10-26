/**
 * @file SlingshotTest.cpp
 * @author Western Tanager
 *
 * Test the slingshot
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Slingshot.h>
#include <Level.h>

TEST(SlingshotTest, Construct)
{
    Level level(L"levels/level0.xml");
    Slingshot slingshot(&level);

    ASSERT_TRUE(slingshot.GetLevel() == &level);
}
