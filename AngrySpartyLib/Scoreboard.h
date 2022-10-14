/**
 * @file ScoreBoard.cpp
 * @author Tyler Baird
 */

#ifndef ANGRYSPARTY_SCOREBOARD_H
#define ANGRYSPARTY_SCOREBOARD_H
class Score;

class ScoreBoard {
private:
    int mCurrentScore;
public:
    void getCurrentScore();
    void addScores(Score* score);


};


#endif //ANGRYSPARTY_SCOREBOARD_H