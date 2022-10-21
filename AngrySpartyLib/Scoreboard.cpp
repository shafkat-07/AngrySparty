/**
 * @file Scoreboard.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Game.h"

/**
 * Add a score
 *
 * @param score The score to add
 */
int Scoreboard::addScores(Score *score)
{
    int new_score;
    new_score = mCurrentScore+mTotalScore;
    return new_score;
}

/**
 * Get the current score
 */
int Scoreboard::getCurrentScore()
{
    return mCurrentScore;
}


void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    //
    // Measuring text and drawing centered
    //
    graphics->PushState();
    wxFont bigFont(wxSize(0, 50),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(250, 0, 0));

    double wid, hit;
    graphics->GetTextExtent(L"0", &wid, &hit);
    graphics->DrawText(L"0", 650, hit + 700);
    graphics->GetTextExtent(L"0", &wid, &hit);
    graphics->DrawText(L"0", -650, hit + 700);

    graphics->PopState();
}

Scoreboard::Scoreboard(Game *game) {

}