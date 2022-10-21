/**
 * @file Scoreboard.h
 * @author Western Tanager
 *
 * Class to represent the Scoreboard
 */

#ifndef ANGRYSPARTY_SCOREBOARD_H
#define ANGRYSPARTY_SCOREBOARD_H

class Score;
class Game;

/**
 * Class to represent the Scoreboard
 *
 * Holds the total score for the game
 * and the score for the current level
 */
class Scoreboard {
private:
    /// The value of the total score
    int mTotalScore;

    /// The value of the current level's score
    int mCurrentScore;

public:
    Scoreboard(Game* game);
    int getCurrentScore();
    int addScores(Score* score);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);


};


#endif //ANGRYSPARTY_SCOREBOARD_H