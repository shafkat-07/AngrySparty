/**
 * @file Game.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <memory>
#include "Game.h"

using namespace std;

/**
 * Game Constructor
 */
Game::Game()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);
    mLevelManager = make_unique<LevelManager>();
}

/**
 * Draw the game background
 * @param dc The device context to draw on
 */
void Game::OnDraw(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));

    mLevelManager->OnDraw(dc);
}