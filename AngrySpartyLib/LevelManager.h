/**
 * @file LevelManager.h
 * @author Vetri Vijay
 *
 * Loads and manages all of the levels in the game
 *
 */

#ifndef ANGRYSPARTY_LEVELMANAGER_H
#define ANGRYSPARTY_LEVELMANAGER_H

#include "Level.h"

//TODO Remove wx headers after pch.h is configured
#include <wx/string.h>
#include <wx/dc.h>

/**
 * A manager for the levels in the game
 */
class LevelManager {
private:
    /// Collection of levels to be managed
    std::vector<std::shared_ptr<Level>> mLevels;

    /// The total number of levels on the game
    int mLevelCount = 0;

    /// The index of the currently displayed level
    int mDisplayedLevel = 0;
public:
    LevelManager();
    void Load(const std::wstring& filename);
    void ChangeLevel(int desiredlevel);
    void OnDraw(wxDC * dc);

    /**
     * Returns the currently played/displayed level
     * @return The index of the displayed level
     */
    int GetDisplayedLevel() const {return mDisplayedLevel;}
};

#endif //ANGRYSPARTY_LEVELMANAGER_H
