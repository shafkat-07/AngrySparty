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

    /// The total number of levels on the game. Indexing from 1
    int mLevelCount = 0;

    /// The index of the currently displayed level. Indexing from 1
    int mDisplayedLevel = 2;
public:
    LevelManager();
    void Load(const std::wstring& filename);
    void ChangeLevel(int desiredLevel);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

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
