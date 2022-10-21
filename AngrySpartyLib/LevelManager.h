/**
 * @file LevelManager.h
 * @author Western Tanager
 *
 * Loads and manages all of the levels in the game
 */

#ifndef ANGRYSPARTY_LEVELMANAGER_H
#define ANGRYSPARTY_LEVELMANAGER_H

#include "Level.h"

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
    int mDisplayedLevel = 0;

    /// Scale we are drawing at
    double mScale = 1;

    /// X offset when we draw
    double mXOffset = 0;

    /// Y offset when we draw
    double mYOffset = 0;

public:
    LevelManager();
    void Load(const std::wstring& filename);
    void ChangeLevel(int desiredLevel);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Returns the currently played/displayed level
     * @return The index of the displayed level
     */
    int GetDisplayedLevel() const {return mDisplayedLevel;}

    /**
     * Returns the total number of levels in the game
     * @return The total number of levels in the game
     */
    int GetLevelCount() const {return mLevelCount;}
};

#endif //ANGRYSPARTY_LEVELMANAGER_H
