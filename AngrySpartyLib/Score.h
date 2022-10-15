/**
 * @file Score.h
 * @author Western Tanager
 *
 * Class to represent a Score
 */
#ifndef ANGRYSPARTY_SCORE_H
#define ANGRYSPARTY_SCORE_H

/**
 * Class to represent a Score
 */
class Score {
private:
    /// The value of the score
    int mValue;

public:
    /**
     * Get the current score
     * @return The current score
     */
    int getScore() { return mValue; }


};


#endif //ANGRYSPARTY_SCORE_H
