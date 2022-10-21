/**
 * @file GameView.h
 * @author Western Tanager
 *
 * View class for our game
 */

#ifndef ANGRYSPARTY_GAMEVIEW_H
#define ANGRYSPARTY_GAMEVIEW_H

#include "Game.h"

/**
 * View class for our game
 */
class GameView : public wxWindow {
private:
    /// An object that describes our game
    Game mGame;
    /// The timer that allows for animation
    wxTimer mTimer;

    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);
    void OnLevel0(wxCommandEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);

public:
    void Initialize(wxFrame* parent);
};

#endif //ANGRYSPARTY_GAMEVIEW_H
