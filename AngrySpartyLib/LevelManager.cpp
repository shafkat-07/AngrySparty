/**
 * @file LevelManager.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "LevelManager.h"

/// XML1's file location
const std::wstring XML0 = L"levels/level0.xml";
/// XML2's file location
const std::wstring XML1 = L"levels/level1.xml";
/// XML3's file location
const std::wstring XML2 = L"levels/level2.xml";

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
 * @param desiredLevel The index of the level to play
 */
void LevelManager::ChangeLevel(int desiredLevel)
{
    // TODO Delete the currently displayed level's object and add the desired ones
    mDisplayedLevel = desiredLevel;
}

/**
 * Passes on the wxGraphicsContext draw pointer to the Items
 * @param graphics The wxGraphicsContext pointer
 */
void LevelManager::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mLevels[mDisplayedLevel]->OnDraw(graphics);
}
