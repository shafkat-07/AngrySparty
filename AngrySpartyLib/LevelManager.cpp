/**
 * @file LevelManager.cpp
 * @author Vetri Vijay
 */

#include "LevelManager.h"

/// XML1's file location
const std::wstring XML0 = L"../levels/level0.xml";
/// XML2's file location
const std::wstring XML1 = L"../levels/level1.xml";
/// XML3's file location
const std::wstring XML2 = L"..levels/level2.xml";

/**
 * Constructor for the LevelManager, will load the 3 predefined levels on creation
 */
LevelManager::LevelManager()
{
    Load(XML0);
    Load(XML1);
    Load(XML2);
}

/**
 * Loads a Level XML file into the game
 * @param filename Path of the XML file on disk
 */
void LevelManager::Load(const std::wstring& filename)
{
    auto new_level = std::make_shared<Level>(filename);
    mLevels.push_back(new_level);
    ++mLevelCount;
}

/**
 * Updates the level displayed to the one passed in
 * @param desiredlevel The index of the level to play
 */
void LevelManager::ChangeLevel(int desiredlevel)
{
    // TODO Delete the currently displayed level's object and add the desired ones
    mDisplayedLevel = desiredlevel;
}

/**
 * Passes on the wxDC draw pointer to the Items
 * @param dc The wxDC pointer
 */
void LevelManager::OnDraw(wxDC* dc)
{
    mLevels[mDisplayedLevel]->OnDraw(dc);
}
