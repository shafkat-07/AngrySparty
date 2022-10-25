/**
 * @file Game.h
 * @author Western Tanager
 *
 * The class for our Game
 */

#ifndef ANGRYSPARTY_GAME_H
#define ANGRYSPARTY_GAME_H

#include <b2_math.h>
#include <wx/dc.h>
#include "LevelManager.h"
#include "Scoreboard.h"

class Scoreboard;

/**
 * The class for our Game
 */
class Game {
private:
    /// The graphics object
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Level manager containing levels
    std::unique_ptr<LevelManager> mLevelManager;

    /// The Scoreboard associated to this game
    std::unique_ptr<Scoreboard> mScoreboard;

    /// The total score for the game
    int mTotalScore = 0;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void SetLevel(int Level);

    /**
     * Get the total score for the game
     * @return Total score for this game
     */
    int GetTotalScore() const { return mTotalScore; }

    /**
     * Get the current level's score
     * @return Curren level's score
     */
    int GetCurrentLevelScore() const { return mLevelManager->GetCurrentLevelScore(); }

    /**
     * Add a score to the total
     * @param score The score to add
     */
    void UpdateTotalScore(int score) { mTotalScore += score; }

    /**
     * Get the current level's size
     * @return Current level's size
     */
    b2Vec2 GetCurrentLevelSize() const { return mLevelManager->GetCurrentLevelSize(); }


};

#endif //ANGRYSPARTY_GAME_H
