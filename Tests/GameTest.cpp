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
}

TEST(GameTest, Scoring)
{
    Game game;
    ASSERT_TRUE(game.GetTotalScore() == 0);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 0);

    game.GetCurrentLevel()->UpdateScore(50);
    game.UpdateTotalScore(game.GetCurrentLevelScore());

    ASSERT_TRUE(game.GetTotalScore() == 50);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 50);

    game.SetLevel(2);
    ASSERT_TRUE(game.GetTotalScore() == 50);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 0);

    // Old score for this level is not saved, but total score is preserved
    game.SetLevel(1);
    ASSERT_TRUE(game.GetTotalScore() == 50);
    ASSERT_TRUE(game.GetCurrentLevelScore() == 0);
}