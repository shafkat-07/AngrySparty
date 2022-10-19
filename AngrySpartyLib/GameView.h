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

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);
};

#endif //ANGRYSPARTY_GAMEVIEW_H
