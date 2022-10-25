/**
 * @file Scoreboard.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include "Scoreboard.h"
#include "Game.h"
#include "Consts.h"

/// The font size for the scoreboard
const int FontSize = 80;

/// The horizontal distance to the edge of the screen for the scores
const int HorizontalMargin = 20;

/// The vertical distance to the edge of the screen for the scores
const int VerticalMargin = 10;

/**
 * Constructor for a Scoreboard
 * @param game The game this scoreboard belongs to
 */
Scoreboard::Scoreboard(Game* game) : mGame(game)
{
}

/**
 * Draw the score board.
 * @param graphics The drawing context to draw on.
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Get score values and dimensions of the current level
    wxString totalScore = wxString::Format(wxT("%i"),mGame->GetTotalScore());
    wxString currentLevelScore = wxString::Format(wxT("%i"),mGame->GetCurrentLevelScore());
    b2Vec2 currentLevelSize = mGame->GetCurrentLevelSize();
    double wid = currentLevelSize.x * Consts::MtoCM;
    double hit = currentLevelSize.y * Consts::MtoCM;

    graphics->PushState();
    wxFont bigFont(wxSize(0, FontSize),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(255, 0, 0));

    // Store the width of the score to fit it to the screen accordingly
    double currScoreWidth;
    double currScoreHeight;
    graphics->GetTextExtent(currentLevelScore, &currScoreWidth, &currScoreHeight);

    graphics->Scale(1, -1);
    graphics->DrawText(totalScore, -wid/2 + HorizontalMargin, -hit + VerticalMargin);
    graphics->DrawText(currentLevelScore, wid/2 - (currScoreWidth + HorizontalMargin), -hit + VerticalMargin);

    graphics->PopState();
}
