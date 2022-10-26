/**
 * @file Goalpost.cpp
 * @author Western Tanager
 *
 * Test the goalpost
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Goalpost.h>
#include <Level.h>

TEST(GoalpostTest, Constructor)
{
    Level level(L"levels/level0.xml");
    Goalpost goalpost(&level);

    ASSERT_TRUE(goalpost.GetLevel() == &level);
}
