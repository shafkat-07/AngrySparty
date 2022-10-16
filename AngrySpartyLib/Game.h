/**
 * @file Game.h
 * @author Juan Camilo Sabogal Olarte
 *
 * The class for our Game
 */

#ifndef ANGRYSPARTY_GAME_H
#define ANGRYSPARTY_GAME_H

#include <wx/dc.h>
#include "LevelManager.h"

/**
 * The class for our Game
 */
class Game {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use
    std::unique_ptr<LevelManager> mLevelManager;  ///< Level manager containing levels

public:
    Game();
    void OnDraw(wxDC* dc);

};

#endif //ANGRYSPARTY_GAME_H
