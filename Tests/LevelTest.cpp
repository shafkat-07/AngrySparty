/**
 * @file LevelTest.cpp
 * @author Western Tanager
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>

const std::wstring filename = L"levels/level2.xml";

TEST(LevelTest, Construct)
{
    // Loads level2 as a game level
    Level level(filename);

    // Test score functionality
    ASSERT_TRUE(level.GetScore() == 0);
    level.UpdateScore(50);
    ASSERT_TRUE(level.GetScore() == 50);

    level.SetLevel(); // Installing physics is required for hit testing on the b2bodies

    // Use HitTest to test the locations of items
    ASSERT_TRUE(level.HitTest(1,1) == nullptr);   // Random point, should ignore background
    ASSERT_FALSE(level.HitTest(3.35625,2.06137) == nullptr);   // Block on line 9 of the XML

    // Block on line 12 of the level2 XML
    ASSERT_FALSE(level.HitTest(3.69974, 0.364022) == nullptr);   // Exact
    ASSERT_FALSE(level.HitTest(3.69974, 0.464022) == nullptr);   // y += height/2
    ASSERT_TRUE(level.HitTest(3.69974, 0.464023) == nullptr);   // y += height/2 + 0.00001


    // Block on line 20
    ASSERT_FALSE(level.HitTest(9.05663,2.53256) == nullptr);   // Exact
    ASSERT_FALSE(level.HitTest(9.30663,2.53256) == nullptr);   // x += width/2
    ASSERT_TRUE(level.HitTest(9.30664,2.53256) == nullptr);   // x += width/2 + 0.00001
}
