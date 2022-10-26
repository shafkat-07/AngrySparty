/**
 * @file GameTest.cpp
 * @author Western Tanager
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>

TEST(GameTest, Construct)
{
    Game game;
    ASSERT_TRUE(game.GetTotalScore() == 0);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 0);

    game.GetCurrentLevel()->UpdateScore(50);
    game.UpdateTotalScore(game.GetCurrentLevelScore());

    ASSERT_TRUE(game.GetTotalScore() == 50);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 50);
}