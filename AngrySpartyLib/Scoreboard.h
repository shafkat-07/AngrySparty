/**
 * @file Scoreboard.h
 * @author Western Tanager
 *
 * Class to represent the Scoreboard
 */

#ifndef ANGRYSPARTY_SCOREBOARD_H
#define ANGRYSPARTY_SCOREBOARD_H

class Score;

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
    void getCurrentScore();
    void addScores(Score* score);


};


#endif //ANGRYSPARTY_SCOREBOARD_H