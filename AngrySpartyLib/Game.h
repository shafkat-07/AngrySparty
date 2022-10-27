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
#include "Scoreboard.h"

class Scoreboard;

/**
 * The class for our Game
 */
class Game {
private:
    /// The graphics object
    std::shared_ptr<wxGraphicsContext> mGraphics;

    /// Level manager containing levels
    std::unique_ptr<LevelManager> mLevelManager;

    /// The Scoreboard associated to this game
    std::unique_ptr<Scoreboard> mScoreboard;

    /// The total score for the game
    int mTotalScore = 0;

    /// Scale we are drawing at
    double mScale = 1;

    /// X offset when we draw
    double mXOffset = 0;

    /// Y offset when we draw
    double mYOffset = 0;

    /// Mouse location
    b2Vec2 mMouseLocation;

    /// A ground reference object
    b2Body* mGround;/// A ground reference object

    /// Size of the playing area in meters
    std::shared_ptr<Item> mGrabbedItem;

    /// Mouse joint for moving things
    b2MouseJoint* mMouseJoint = nullptr;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void SetLevel(int Level);
    void Update(double elapsed);

    /**
     * Get the total score for the game
     * @return Total score for this game
     */
    int GetTotalScore() const { return mTotalScore; }

    /**
     * Get the current level's score
     * @return Curren level's score
     */
    int GetCurrentLevelScore() const { return mLevelManager->GetCurrentLevelScore(); }

    /**
     * Add a score to the total
     * @param score The score to add
     */
    void UpdateTotalScore(int score) { mTotalScore += score; }

    /**
     * Get the current level's size
     * @return Current level's size
     */
    b2Vec2 GetCurrentLevelSize() const { return mLevelManager->GetCurrentLevelSize(); }

    void OnMouseMove(wxMouseEvent& event);
//
//    void OnMouseUp(wxMouseEvent& event);

    /**
     * Left mouse button down event
     * @param event Mouse event
     */
    void OnLeftDown(wxMouseEvent& event);

    /**
     * Get the current level object
     * @return Get the current level object
     */
    std::shared_ptr<Level> GetCurrentLevel() { return mLevelManager->GetCurrentLevel(); }
};

#endif //ANGRYSPARTY_GAME_H
