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

    /// The stopwatch used to measure elapsed time.
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    double mTime = 0;

    /// Debug view enabled?
    bool mDebugView = false;

    /// Ring enabled?
    bool mRingView = false;

    void OnPaint(wxPaintEvent& event);

    void OnLevel0(wxCommandEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);
    void OnDebugView(wxCommandEvent& event);
    void OnRingToggle(wxCommandEvent& event);

    void OnTimer(wxTimerEvent& event);

    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);

public:
    void Initialize(wxFrame* parent);

    /**
     * Stop the timer so the window can close
     */
    void Stop() { mTimer.Stop(); }

};

#endif //ANGRYSPARTY_GAMEVIEW_H
