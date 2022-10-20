/**
 * @file LevelTest.cpp
 * @author Vetri
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>

const std::wstring filename = L"levels/level2.xml";

TEST(LevelTest, Construct)
{
    Level level(filename);
    ASSERT_TRUE(level.GetScore() == 0);
    level.UpdateScore(50);
    ASSERT_TRUE(level.GetScore() == 50);
    ASSERT_TRUE(level.HitTest(4.09142,2.04342));
    ASSERT_TRUE(level.HitTest(9.05663,2.53256));
    ASSERT_FALSE(level.HitTest(19.05663,2.53256));

    ASSERT_TRUE(level.HitTest(9.05663,2.53256));
    ASSERT_TRUE(level.HitTest(9.05663,2.53256));
    ASSERT_FALSE(level.HitTest(19.05663,2.53256));
}
