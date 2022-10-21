/**
 * @file Game.h
 * @author Western Tanager
 *
 * The class for our Game
 */

#ifndef ANGRYSPARTY_GAME_H
#define ANGRYSPARTY_GAME_H

#include <b2_math.h>
#include <wx/dc.h>
#include "LevelManager.h"

/**
 * The class for our Game
 */
class Game {
private:
    /// The graphics object
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Level manager containing levels
    std::unique_ptr<LevelManager> mLevelManager;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void SetLevel(int Level);
};

#endif //ANGRYSPARTY_GAME_H
