/**
 * @file GameView.cpp
 * @author Western Tanager
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include "GameView.h"
#include "ids.h"

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
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel1,this, LEVEL_1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel2,this, LEVEL_2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,&GameView::OnLevel3,this, LEVEL_3);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();

    // Create a graphics context
    auto graphics =
            std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
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
