/**
 * @file LevelManager.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "LevelManager.h"
#include "Consts.h"

/// XML0's file location
const std::wstring XML0 = L"levels/level0.xml";

/// XML1's file location
const std::wstring XML1 = L"levels/level1.xml";

/// XML2's file location
const std::wstring XML2 = L"levels/level2.xml";

/// XML3's file location
const std::wstring XML3 = L"levels/level3.xml";

/// The first level to display when starting the game
const int StartingLevel = 1;

/**
 * Constructor for the LevelManager, will load the 3 predefined levels on creation
 */
LevelManager::LevelManager()
{
    Load(XML0);
    Load(XML1);
    Load(XML2);
    Load(XML3);
    ChangeLevel(StartingLevel);
}

/**
 * Loads a Level XML file into the game
 * @param filename Path of the XML file on disk
 */
void LevelManager::Load(const std::wstring& filename)
{
    auto newLevel = std::make_shared<Level>(filename);
    mLevels.push_back(newLevel);
    ++mLevelCount;
//    std::cout << "Just loaded level " << mLevelCount << '\n';
}

/**
 * Updates the level displayed to the one passed in
 * @param desiredLevel The index of the level to play
 */
void LevelManager::ChangeLevel(int desiredLevel)
{
    // TODO Delete the currently displayed level's object and add the desired ones
    GetCurrentLevel()->ResetLevel(); // Reset its objects and scores
    mDisplayedLevel = desiredLevel;
    GetCurrentLevel()->SetLevel();
    mWinState = false;
    mLoseState = false;
}

/**
 * Passes on the wxGraphicsContext draw pointer to the Items
 * @param graphics The wxGraphicsContext pointer
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void LevelManager::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    GetCurrentLevel()->OnDraw(graphics);
    graphics->Flush();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void LevelManager::Update(double elapsed)
{
    GetCurrentLevel()->Update(elapsed);
    FoeVisitor foeVisitor;
    mLevels[mDisplayedLevel]->Accept(&foeVisitor);
    if(foeVisitor.GetNumFoes() == 0){
        mWinState = true;
    }
    if(mLevels[mDisplayedLevel]->GetSpartyCount() == 0){
        mLoseState = true;
    }
}
