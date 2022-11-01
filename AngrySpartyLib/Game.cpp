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
    mLevelManager = make_unique<LevelManager>();
    mScoreboard = make_unique<Scoreboard>(this);
}

/**
 * Handle drawing the game on the screen including all subsystems.
 * @param graphics Graphics context to draw on
 * @param width Width of the window in pixels
 * @param height Height of the window in pixels
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxBrush background(*wxBLACK);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, width, height);

    graphics->PushState();

    // Get the playing area size in centimeters
    auto playingAreaSize = GetCurrentLevelSize();
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

    mLevelManager->OnDraw(graphics);
    mScoreboard->Draw(graphics);
}

/**
 * Set the current level
 * @param level Level to set
 */
void Game::SetLevel(int level)
{
    mLevelManager->ChangeLevel(level);
//    cout << "Changed Level" << '\n';
}

/**
 * Update the game state by updating the current active level.
 * @param elapsed time elapsed since last update.
 */
void Game::Update(double elapsed)
{
    mLevelManager->Update(elapsed);
}

/**
 * Handle the left mouse button down event
 * @param event Mouse event
 */
void Game::OnLeftDown(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    mGrabbedItem = GetCurrentLevel()->HitTest(x, y);

    if (mGrabbedItem != nullptr)
    {
        mGrabbedItem->ClickItem(mMouseLocation);
    }
}

/**
* Handle the mouse move event
* @param event Mouse event
*/
void Game::OnMouseMove(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        mGrabbedItem->MoveItem(event, mMouseLocation);
    }

}

/**
 * Left mouse button down event
 * @param event Mouse event
 */
void Game::OnLeftUp(wxMouseEvent &event)
{
    if (mGrabbedItem != nullptr)
    {
        if (mGrabbedItem->GetMouseJoint()!=nullptr)
        {
            GetCurrentLevel()->GetWorld()->DestroyJoint(mGrabbedItem->GetMouseJoint());
            GetCurrentLevel()->LaunchSparty();
            mGrabbedItem->SetMouseJoint(nullptr);
        }
    }
}

/**
 * Enables/disables the ring for all levels
 *
 * This acts on all levels since the menu option
 * determines the global activation state of rings for the game
 * @param activate Whether or not to activate the rings
 */
void Game::ToggleRing(bool activate)
{
    for (auto level : mLevelManager->GetLevels())
    {
        level->GetRing()->SetAlive(activate);
    }
}