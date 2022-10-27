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
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
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

    mLevelManager->OnDraw(graphics, width, height);
    mScoreboard->Draw(graphics);
    mGraphics = graphics;
}

/**
 * Set the current level
 * @param level Level to set
 */
void Game::SetLevel(int level)
{
    mLevelManager->ChangeLevel(level);
//    std::cout << "Changed Level" << '\n';
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
        auto targetBody = mGrabbedItem->GetBody();
        if(targetBody->GetType() == b2_dynamicBody)
        {
            //
            // Create a mouse joint object we can use
            // to drag items around
            //
            // Only works for dynamic bodies
            //
            b2MouseJointDef jointDef;
            jointDef.bodyA = mLevelManager->GetCurrentLevel()->GetGround();
            jointDef.bodyB = targetBody;
            jointDef.maxForce = 10000 * targetBody->GetMass();
            jointDef.stiffness = 10000 * targetBody->GetMass();
            jointDef.damping = 125;
            jointDef.target = b2Vec2(x, y);

            mMouseJoint = (b2MouseJoint*)mLevelManager->GetCurrentLevel()->GetWorld()->CreateJoint(&jointDef);
            mMouseJoint->SetTarget(b2Vec2(x, y));
        }
    }
}

void Game::OnMouseMove(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        // move it while the left button is down.
        if(event.LeftIsDown())
        {
            if(mMouseJoint != nullptr)
            {
                mMouseJoint->SetTarget(b2Vec2(x, y));
            }
        }
        else
        {
            // When the left button is released, we release the
            // item.
            if(mMouseJoint != nullptr)
            {
                GetCurrentLevel()->GetWorld()->DestroyJoint(mMouseJoint);
                mMouseJoint = nullptr;
            }
        }

    }

}

/**
 * Left mouse button down event
 * @param event Mouse event
 */
void Game::OnLeftUp(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) / Consts::MtoCM;
    auto y = (event.m_y / -mScale - mYOffset) / Consts::MtoCM;
    mMouseLocation = b2Vec2(x, y);

    // When the left button is released, we release the
    // item.
    if(mMouseJoint != nullptr)
    {
        GetCurrentLevel()->GetWorld()->DestroyJoint(mMouseJoint);
        GetCurrentLevel()->LaunchSparty();
        mMouseJoint = nullptr;
    }
}
