/**
 * @file LevelManager.h
 * @author Western Tanager
 *
 * Loads and manages all of the levels in the game
 */

#ifndef ANGRYSPARTY_LEVELMANAGER_H
#define ANGRYSPARTY_LEVELMANAGER_H

#include "Level.h"
#include "FoeVisitor.h"

/**
 * A manager for the levels in the game
 */
class LevelManager {
private:
    /// Collection of levels to be managed
    std::vector<std::shared_ptr<Level>> mLevels;

    /// The total number of levels on the game
    int mLevelCount = 0;

    /// The index of the currently displayed level. Indexing from 0
    int mDisplayedLevel = 1;

    /// Determines if the level is in a win state
    bool mWinState = false;

    /// Determines if the level is in a lose state
    bool mLoseState = false;

    /// The duration for the level begin/end message
    double mLevelMessageDuration = 0;

    /// The level state possibilities
    enum class State {Starting, Playing, Ending};

    /// The current level station state
    State mState = State::Starting;

    /// The total score for the game
    int mTotalScore = 0;

public:
    LevelManager();
    void Load(const std::wstring& filename);
    void ChangeLevel(int desiredLevel);
    void Update(double elapsed);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void OnBeginDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void OnEndDraw(std::shared_ptr<wxGraphicsContext> graphics);
    void DrawMessage(std::shared_ptr<wxGraphicsContext> graphics, std::string message);

    /**
     * Returns the currently played/displayed level
     * @return The index of the displayed level
     */
    int GetDisplayedLevel() const {return mDisplayedLevel;}

    /**
     * Returns the vector of levels
     * @return The vector of levels
     */
    std::vector<std::shared_ptr<Level>> GetLevels() const { return mLevels; }

    /**
     * Get the current level's score
     * @return Curren level's score
     */
    int GetCurrentLevelScore() const { return mLevels[mDisplayedLevel]->GetScore(); }

    /**
     * Get the current level's size
     * @return The current level's size
     */
    b2Vec2 GetCurrentLevelSize() const { return mLevels[mDisplayedLevel]->GetSize(); }

    /**
     * Get current level
     * @return current level being displayed
     */
    std::shared_ptr<Level> GetCurrentLevel() const { return mLevels[mDisplayedLevel]; }

    /**
     * Get the total score for the game
     * @return Total score for this game
     */
    int GetTotalScore() const { return mTotalScore; }

    /**
     * Add a score to the total
     * @param score The score to add
     */
    void UpdateTotalScore(int score) { mTotalScore += score; }
};

#endif //ANGRYSPARTY_LEVELMANAGER_H
