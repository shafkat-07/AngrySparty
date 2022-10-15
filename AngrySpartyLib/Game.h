/**
 * @file Game.h
 * @author Western Tanager
 *
 * The class for our Game
 */

#ifndef ANGRYSPARTY_GAME_H
#define ANGRYSPARTY_GAME_H

/**
 * The class for our Game
 */
class Game {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

public:
    Game();
    void OnDraw(wxDC* dc);

};

#endif //ANGRYSPARTY_GAME_H
