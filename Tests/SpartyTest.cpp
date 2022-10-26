/**
 * @file SpartyTest.cpp
 * @author Western Tanager
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Sparty.h>
#include <Level.h>

TEST(SpartyTest, Constructor)
{
    Level level(L"levels/level0.xml");
    Sparty sparty(&level);

    ASSERT_TRUE(sparty.GetLevel() == &level);
}

TEST(SpartyTest, Move)
{
    Level level(L"levels/level0.xml");
    Sparty sparty(&level);

    // Test the set position function
    sparty.SetXPosition(1);
    ASSERT_TRUE(sparty.GetPosition().x == 1);

    // Now for y
    sparty.SetYPosition(1);
    ASSERT_TRUE(sparty.GetPosition().y == 1);
}

TEST(SpartyTest, NullInitializedBody)
{
    Level level(L"levels/level0.xml");
    Sparty sparty(&level);

    auto body = sparty.GetBody();
    ASSERT_TRUE(body == nullptr);

}


