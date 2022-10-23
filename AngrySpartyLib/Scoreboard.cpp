/**
 * @file Scoreboard.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Game.h"

/**
 * Add a score
 * @param score The score to add
 * @return The sum of the scores
 */
int Scoreboard::AddScores(Score *score)
{
    int newScore;
    newScore = mCurrentScore+mTotalScore;
    return newScore;
}

/**
 * Get the current score
 * @return The value of the current score
 */
int Scoreboard::GetCurrentScore()
{
    return mCurrentScore;
}

/**
 * Draw the score board.
 * @param graphics The drawing context to draw on.
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    //
    // Measuring text and drawing centered
    //
    graphics->PushState();
    wxFont bigFont(wxSize(0, 60),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(250, 0, 0));

    double wid, hit;
    graphics->GetTextExtent(L"0", &wid, &hit);
    graphics->DrawText(L"0", 600, hit + 650);
    graphics->GetTextExtent(L"0", &wid, &hit);
    graphics->DrawText(L"0", -600, hit + 650);

    graphics->PopState();
}

/**
 * Constructor for a Scoreboard
 * @param game The game this scoreboard belongs to
 */
Scoreboard::Scoreboard(Game *game) {

}