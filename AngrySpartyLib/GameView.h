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

    void OnPaint(wxPaintEvent& event);
    void OnLevel0(wxCommandEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);
    void OnDebugView(wxCommandEvent& event);

public:
    void Initialize(wxFrame* parent);

    /**
     * Stop the game.
     *
     * Stops the timer which will freeze the game.
     */
    void Stop() { mTimer.Stop(); }

    void OnLeftDown(wxMouseEvent& event);
};

#endif //ANGRYSPARTY_GAMEVIEW_H
