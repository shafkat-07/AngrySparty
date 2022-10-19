/**
 * @file Game.h
 * @author Juan Camilo Sabogal Olarte
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
    /// Background image to use
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;

    /// Level manager containing levels
    std::unique_ptr<LevelManager> mLevelManager;  


    /// Size of the playing area in meters. TODO: Move this to level since each level has width and height?
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);

    /// Scale we are drawing at
    double mScale = 1;

    /// X offset when we draw
    double mXOffset = 0;

    /// Y offset when we draw
    double mYOffset = 0;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void SetLevel(int Level);
};

#endif //ANGRYSPARTY_GAME_H
