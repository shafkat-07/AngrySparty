/**
 * @file GameView.h
 * @author Juan Camilo Sabogal Olarte
 *
 * View class for our game
 */

#ifndef ANGRYSPARTY_GAMEVIEW_H
#define ANGRYSPARTY_GAMEVIEW_H

#include <wx/wx.h>
#include "Game.h"

/**
 * View class for our game
 */
class GameView : public wxWindow {
private:
    /// An object that describes our game
    Game  mGame;

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame* parent);

};

#endif //ANGRYSPARTY_GAMEVIEW_H
