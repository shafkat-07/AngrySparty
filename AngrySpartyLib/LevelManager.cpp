/**
 * @file LevelManager.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <sstream>
#include "LevelManager.h"
#include "Consts.h"

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

/// Time the level start or end message displays
const double LevelMessageDisplayTime = 2.0;

/// How big the level message's font size is
/// relative to the level's height
const int LevelMessageFontRatio = 10;

/// The color for the level message
const wxColour LevelMessageColor = wxColour(0, 0, 255);

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
}

/**
 * Updates the level displayed to the one passed in
 *
 * This function also gets called when using the menu options
 * @param desiredLevel The index of the level to play
 */
void LevelManager::ChangeLevel(int desiredLevel)
{
    GetCurrentLevel()->ResetLevel(); // Reset previous level to default state
    mDisplayedLevel = desiredLevel;
    GetCurrentLevel()->SetLevel();

    mState = State::Starting;
    mLevelMessageDuration = 0;

    // Restart win state
    mWinState = false;
    mLoseState = false;
}

/**
 * Passes on the wxGraphicsContext draw pointer to the Items
 * @param graphics The wxGraphicsContext pointer
 */
void LevelManager::OnDraw(shared_ptr<wxGraphicsContext> graphics)
{
    GetCurrentLevel()->OnDraw(graphics);

    if (mState == State::Starting)
    {
        OnBeginDraw(graphics);
    }
    else if (mState == State::Ending)
    {
        OnEndDraw(graphics);
    }
}

/**
 * Handle updates for animation and level state
 * @param elapsed The time since the last update
 */
void LevelManager::Update(double elapsed)
{
    FoeCounter foeCounter;
    switch(mState)
    {
    case State::Starting:
        mLevelMessageDuration += elapsed;
        if(mLevelMessageDuration >= LevelMessageDisplayTime)
        {
            mState = State::Playing;
            mLevelMessageDuration = 0;
            GetCurrentLevel()->IncrementSpartyIndex(); // Set SpartyIndex from -1 to 0 on level begin
        }
        break;

    case State::Playing:
        GetCurrentLevel()->Update(elapsed);
        mLevels[mDisplayedLevel]->Accept(&foeCounter);
        if (foeCounter.GetNumFoes() == 0)
        {
            mWinState = true;
        }
        else if (mLevels[mDisplayedLevel]->GetSpartiesLeft() == 0)
        {
            mLoseState = true;
        }

        if (mWinState || mLoseState)
        {
            mState = State::Ending;
            mLevelMessageDuration = 0;
        }
        break;

    case State::Ending:
        mLevelMessageDuration += elapsed;
        if(mLevelMessageDuration >= LevelMessageDisplayTime)
        {
            // Determine next level depending on win state
            int nextLevel = mWinState ? (mDisplayedLevel + 1) % mLevelCount : mDisplayedLevel;
            // Update total score depending on win state
            if (mWinState) UpdateTotalScore(GetCurrentLevelScore());
            ChangeLevel(nextLevel); // Resets the level message duration and sets back to Starting state
        }
        break;

    default:
        break;
    }
}

/**
 * Draw the level begin message
 * @param graphics The graphics context to draw on
 */
void LevelManager::OnBeginDraw(shared_ptr<wxGraphicsContext> graphics)
{
    ostringstream message;
    message << "Level " << mDisplayedLevel <<  " Begin";
    DrawMessage(graphics, message.str());
}

/**
 * Draw the level end message depending on the win state
 * @param graphics The graphics context to draw on
 */
void LevelManager::OnEndDraw(shared_ptr<wxGraphicsContext> graphics)
{
    string message = mWinState ? "Level Complete!" : "Level Fail!";
    DrawMessage(graphics, message);
}

/**
 * Draw a specific level message on the screen
 * @param graphics The graphics context to draw on
 * @param message The message to draw
 */
void LevelManager::DrawMessage(shared_ptr<wxGraphicsContext> graphics, string message)
{
    double levelHeight = GetCurrentLevelSize().y * Consts::MtoCM;

    graphics->PushState();
    wxFont bigFont(wxSize(0, GetCurrentLevelSize().y *  LevelMessageFontRatio),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, LevelMessageColor);

    // Get width and height of message to center it
    double messageWidth;
    double messageHeight;
    graphics->GetTextExtent(message, &messageWidth, &messageHeight);

    graphics->Scale(1, -1);
    graphics->DrawText(message, -messageWidth/2, -levelHeight/2 - messageHeight/2);

    graphics->PopState();
}