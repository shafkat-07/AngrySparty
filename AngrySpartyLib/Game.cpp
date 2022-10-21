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

    mLevelManager->OnDraw(graphics, width, height);
    mGraphics = graphics;


}

/**
 * Set the current level
 * @param level Level to set
 */
void Game::SetLevel(int level)
{
    mLevelManager->ChangeLevel(level);
    std::cout << "Changed Level" << '\n';
}
