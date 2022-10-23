/**
 * @file LevelManager.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "LevelManager.h"
#include "Consts.h"

/// XML1's file location
const std::wstring XML0 = L"levels/level0.xml";
/// XML2's file location
const std::wstring XML1 = L"levels/level1.xml";
/// XML3's file location
const std::wstring XML2 = L"levels/level2.xml";
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
    mDisplayedLevel = desiredLevel;
    mLevels[mDisplayedLevel]->SetLevel();
}

/**
 * Passes on the wxGraphicsContext draw pointer to the Items
 * @param graphics The wxGraphicsContext pointer
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void LevelManager::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    graphics->PushState();

    // Get the playing area size in centimeters
    auto playingAreaSize = mLevels[mDisplayedLevel]->GetSize();
    playingAreaSize *= Consts::MtoCM;

    //
    // Automatic Scaling
    // We use CM display units instead of meters
    // because a 1-meter wide line is very wide
    //
    auto scaleX = double(height) / double(playingAreaSize.y);
    auto scaleY = double(width) / double(playingAreaSize.x);
    mScale = scaleX < scaleY ? scaleX : scaleY;
    graphics->Scale(mScale, -mScale);

    // Determine the virtual size in cm
    auto virtualWidth = (double)width / mScale;
    auto virtualHeight = (double)height / mScale;

    // And the offset to the middle of the screen
    mXOffset = virtualWidth / 2.0;
    mYOffset = -(virtualHeight - playingAreaSize.y) / 2.0 - playingAreaSize.y;

    graphics->Translate(mXOffset, mYOffset);

    //
    // From here we are dealing with centimeter pixels
    // and Y up being increase values
    //

    mLevels[mDisplayedLevel]->OnDraw(graphics);
    graphics->Flush();
}
