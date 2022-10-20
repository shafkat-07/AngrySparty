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
    // Loads level2 as a game level
    Level level(filename);

    // Test score functionality
    ASSERT_TRUE(level.GetScore() == 0);
    level.UpdateScore(50);
    ASSERT_TRUE(level.GetScore() == 50);

    // Use HitTest to test the locations of items
    ASSERT_FALSE(level.HitTest(1,1));   // Random point, should ignore background
    ASSERT_TRUE(level.HitTest(3.35625,2.06137));   // Block on line 9 of the XML

    // Block on line 16 of the level2 XML
    ASSERT_TRUE(level.HitTest(4.5197, 0.36511));   // Exact
    ASSERT_TRUE(level.HitTest(4.5197, 0.46511));   // y += height/2
    ASSERT_FALSE(level.HitTest(4.5197, 0.46512));   // y += height/2 + 0.00001

    // Block on line 20
    ASSERT_TRUE(level.HitTest(9.05663,2.53256));   // Exact
    ASSERT_TRUE(level.HitTest(9.30663,2.53256));   // x += width/2
    ASSERT_FALSE(level.HitTest(9.30664,2.53256));   // x += width/2 + 0.00001
}
