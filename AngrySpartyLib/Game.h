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

/**
 * The class for our Game
 */
class Game {
private:
    /// Level manager containing levels
    std::unique_ptr<LevelManager> mLevelManager;

    /// The Scoreboard associated to this game
    std::unique_ptr<Scoreboard> mScoreboard;

    /// Scale we are drawing at
    double mScale = 1;

    /// X offset when we draw
    double mXOffset = 0;

    /// Y offset when we draw
    double mYOffset = 0;

    /// Mouse location
    b2Vec2 mMouseLocation = b2Vec2(0.0f, 0.0f);

    /// Size of the playing area in meters
    std::shared_ptr<Item> mGrabbedItem;

    /// Mouse joint for moving things
    b2MouseJoint* mMouseJoint = nullptr;

public:
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void SetLevel(int Level);
    void Update(double elapsed);
    void ToggleRing(bool);

    void OnMouseMove(wxMouseEvent& event);
    void OnLeftDown(wxMouseEvent& event);
    void OnLeftUp(wxMouseEvent& event);

    /**
     * Get the total score for the game
     * @return Total score for this game
     */
    int GetTotalScore() const { return mLevelManager->GetTotalScore(); }

    /**
     * Get the current level object
     * @return Get the current level object
     */
    std::shared_ptr<Level> GetCurrentLevel() { return mLevelManager->GetCurrentLevel(); }

    /**
     * Get the current level's size
     * @return Current level's size
     */
    b2Vec2 GetCurrentLevelSize() const { return mLevelManager->GetCurrentLevelSize(); }

    /**
     * Get the current level's score
     * @return Curren level's score
     */
    int GetCurrentLevelScore() const { return mLevelManager->GetCurrentLevelScore(); }

    /**
     * Add a score to the total
     * @param score The score to add
     */
    void UpdateTotalScore(int score) { mLevelManager->UpdateTotalScore(score); }
};

#endif //ANGRYSPARTY_GAME_H
