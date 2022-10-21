/**
 * @file LevelManagerTest.cpp
 * @author Vetri
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <LevelManager.h>

const std::wstring filename0 = L"levels/level0.xml";
const std::wstring filename1 = L"levels/level1.xml";
const std::wstring filename2 = L"levels/level2.xml";

TEST(LevelManagerTest, Construct)
{
    LevelManager level_manager;
    ASSERT_TRUE(level_manager.GetDisplayedLevel() == 0);

    ASSERT_TRUE(level_manager.GetDisplayedLevel() == 0);

    level_manager.ChangeLevel(2);
    ASSERT_TRUE(level_manager.GetDisplayedLevel() == 2);

    level_manager.ChangeLevel(1);
    ASSERT_TRUE(level_manager.GetDisplayedLevel() == 1);
}