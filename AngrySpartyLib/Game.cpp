/**
 * @file Game.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <memory>
#include "Game.h"
#include "Consts.h"

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
 * Handle drawing the game on the screen including all subsystems.
 * @param graphics Graphics context to draw on
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxBrush background(*wxBLACK);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, width, height);

    graphics->PushState();

    // Get the playing area size in centimeters
    auto playingAreaSize = mSize;
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

    // Draw a Background bitmap (inverting first) and size equal to the size of playing arena
    graphics->PushState();
    graphics->Scale(1, -1);	// Negate Y
    graphics->DrawBitmap(*mBackground, -mSize.x/2 * Consts::MtoCM, -mSize.y * Consts::MtoCM,
                                        mSize.x * Consts::MtoCM, mSize.y * Consts::MtoCM);
    graphics->PopState();

    graphics->PopState();
}
