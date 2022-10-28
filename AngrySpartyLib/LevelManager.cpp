/**
 * @file LevelManager.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "LevelManager.h"

using namespace std;

/// XML0's file location
const wstring XML0 = L"levels/level0.xml";

/// XML1's file location
const wstring XML1 = L"levels/level1.xml";

/// XML2's file location
const wstring XML2 = L"levels/level2.xml";

/// XML3's file location
const wstring XML3 = L"levels/level3.xml";

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
void LevelManager::Load(const wstring& filename)
{
    auto newLevel = make_shared<Level>(filename);
    mLevels.push_back(newLevel);
    ++mLevelCount;
//    cout << "Just loaded level " << mLevelCount << '\n';
}

/**
 * Updates the level displayed to the one passed in
 * @param desiredLevel The index of the level to play
 */
void LevelManager::ChangeLevel(int desiredLevel)
{
    GetCurrentLevel()->ResetLevel(); // Reset previous level to default state
    mDisplayedLevel = desiredLevel;
    GetCurrentLevel()->SetLevel(); // Install new level
}

/**
 * Passes on the wxGraphicsContext draw pointer to the Items
 * @param graphics The wxGraphicsContext pointer
 */
void LevelManager::OnDraw(shared_ptr<wxGraphicsContext> graphics)
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
    FoeVisitor a;
    mLevels[mDisplayedLevel]->Accept(&a);
    if(a.GetNumFoes() == 0){
        ChangeLevel(mDisplayedLevel+1);
    }

}
