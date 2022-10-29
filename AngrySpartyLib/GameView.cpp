/**
 * @file GameView.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include "GameView.h"
#include "ids.h"
#include "DebugDraw.h"

using namespace std;

/// Frame duration in seconds
const double FrameDuration = 1.0/60.0;
/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
            wxDefaultPosition, wxDefaultSize,
            wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel0,this, LEVEL_0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel1,this, LEVEL_1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel2,this, LEVEL_2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel3,this, LEVEL_3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnDebugView,this, IDM_DEBUG_VIEW);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnRingToggle,this, IDM_RING);

    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_MOTION, &GameView::OnMouseMove, this);
    Bind(wxEVT_LEFT_UP, &GameView::OnLeftUp, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    auto newTime = mStopWatch.Time() * 0.001;
    while (mTime < newTime)
    {
        mTime += FrameDuration;
        mGame.Update(FrameDuration);
    }

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();

    // Create a graphics context
    auto graphics =
            shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());

    if (mDebugView)
    {
        DebugDraw debugDraw(graphics);
        debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
        mGame.GetCurrentLevel()->GetWorld()->SetDebugDraw(&debugDraw);
        mGame.GetCurrentLevel()->GetWorld()->DebugDraw();
    }
}

/**
 * Changes the level to lvl0
 * @param event Paint event object
 */
void GameView::OnLevel0(wxCommandEvent& event)
{
    mGame.SetLevel(0);
}

/**
 * Changes the level to lvl1
 * @param event Paint event object
 */
void GameView::OnLevel1(wxCommandEvent& event)
{
    mGame.SetLevel(1);
}

/**
 * Changes the level to lvl2
 * @param event Paint event object
 */
void GameView::OnLevel2(wxCommandEvent& event)
{
    mGame.SetLevel(2);
}

/**
 * Changes the level to lvl3
 * @param event Paint event object
 */
void GameView::OnLevel3(wxCommandEvent& event)
{
    mGame.SetLevel(3);
}

/**
 * Enables/disables debug view
 * @param event Paint event object
 */
void GameView::OnDebugView(wxCommandEvent& event)
{
    mDebugView = !mDebugView;
}

/**
 * Enables/disables the Ring
 * @param event Paint event object
 */
void GameView::OnRingToggle(wxCommandEvent& event)
{
    mRingView = !mRingView;
    mGame.ToggleRing(mRingView);
}

/**
 * Left mouse button down event.
 * @param event Mouse event
 */
void GameView::OnLeftDown(wxMouseEvent& event)
{
    mGame.OnLeftDown(event);
}

/**
* Handle the left mouse button up event
* @param event Mouse event
*/
void GameView::OnLeftUp(wxMouseEvent& event)
{
    mGame.OnLeftUp(event);
}

/**
* Handle the mouse move event
* @param event Mouse event
*/
void GameView::OnMouseMove(wxMouseEvent& event)
{
    mGame.OnMouseMove(event);
}

/**
 * Handle timer events
 * @param event Timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}