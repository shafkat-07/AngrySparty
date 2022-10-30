/**
 * @file Scoreboard.h
 * @author Western Tanager
 *
 * Class to represent the Scoreboard
 */

#ifndef ANGRYSPARTY_SCOREBOARD_H
#define ANGRYSPARTY_SCOREBOARD_H

class Game;

/**
 * Class to represent the Scoreboard
 *
 * Accesses the game's scores and handles the drawing
 */
class Scoreboard {
private:
    /// The game this Scoreboard belongs to
    Game* mGame;

public:
    Scoreboard(Game* game);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //ANGRYSPARTY_SCOREBOARD_H