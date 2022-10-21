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
    LevelManager levelManager;
    ASSERT_TRUE(levelManager.GetDisplayedLevel() == 1);

    levelManager.ChangeLevel(2);
    ASSERT_TRUE(levelManager.GetDisplayedLevel() == 2);

    levelManager.ChangeLevel(1);
    ASSERT_TRUE(levelManager.GetDisplayedLevel() == 1);
}