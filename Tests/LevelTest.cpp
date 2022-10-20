/**
 * @file LevelTest.cpp
 * @author Vetri
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>

const std::wstring filename = L"levels/level1.xml";

TEST(LevelTest, Construct)
{
    Level level(filename);
    ASSERT_TRUE(level.GetScore() == 0);
    level.UpdateScore(50);
    ASSERT_TRUE(level.GetScore() == 50);
    ASSERT_FALSE(level.HitTest(4.0139,0.765071));
}