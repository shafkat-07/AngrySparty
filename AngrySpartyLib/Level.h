/**
 * @file Level.h
 * @author Western Tanager
 *
 * Contains all the items for a level
 */

#ifndef ANGRYSPARTY_LEVEL_H
#define ANGRYSPARTY_LEVEL_H

#include <b2_math.h>
#include <b2_world.h>
#include <b2_body.h>

#include <vector>
#include <memory>
#include <random>

#include "Item.h"
#include "World.h"
#include "Sparty.h"
#include "Ring.h"

class ItemVisitor;

/**
 * This class represents a level with it's own score and item collection
 */
class Level {
private:
    /// Size of the playing area in meters
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);

    /// The physics object initialized with the size of the display
    std::shared_ptr<World> mPhysics = nullptr;

     /// The main vector of pointers to the items for each level
     std::vector<std::shared_ptr<Item>> mItems;

     /// Contains pointers to Sparty objects. Transferred down to the Shooter class.
     std::vector<std::shared_ptr<Sparty>> mSparties;

     /// Save the index location of the shooter.
     int mShooterIndex = -1;

     /// Any item we have grabbed and are moving
     std::shared_ptr<Item> mGrabbedItem;

     /// Mouse joint for moving things
     b2MouseJoint* mMouseJoint = nullptr;

     /// Score tracking for each level
     int mScore = 0;

     /// The number of sparties in the world.
     int mSpartiesLeft = 0;

    /// Random number generator
    std::mt19937 mRandom;

    /// The speed-boost ring for this level
    std::shared_ptr<Ring> mRing;

public:
    Level(const std::wstring &);
    void Load(const std::wstring &);
    void XmlItem(wxXmlNode* node);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);
    std::shared_ptr<Item> HitTest(double x, double y);
    void SetLevel();
    void ResetLevel();
    void Update(double elapsed);
    void Accept(ItemVisitor* visitor);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() { return mRandom; }

    /**
     * Getter for the score from this level
     * @return Score
     */
    int GetScore() const { return mScore; }

    /**
     * Getter for the score from this level
     * @return Score
     */
    b2Vec2 GetSize() const { return mSize; }

    /**
     * Getter for the number of sparties left
     * @return Number of sparties alive
     */
    int GetSpartiesLeft() const { return mSpartiesLeft; }

    /**
     * Decreases the amount of sparties left by 1
     */
    void ReduceSpartiesLeft() { --mSpartiesLeft; }

    /**
     * Getter for the total sparties in this level (including dead ones)
     * @return Total number of sparties
     */
    int GetTotalSparties() const { return mSparties.size(); }

    /**
     * Get the list of sparties
     * @return A reference to the list of sparties
     */
    std::vector<std::shared_ptr<Sparty>>& GetSparties() { return mSparties; }

    /**
     * Updates the score by incrementing with the parameter (can be negative)
     * @param score The parameter to increment by (can be negative)
     */
    void UpdateScore(int score) { mScore += score; }

    /**
     * Get the Box2D World object
     * @return b2World object
     */
    b2World *GetWorld() { return mPhysics->GetWorld(); }

    /**
     * Get the Box2D ground object for this level's physics environment
     * @return b2Body ground object
     */
    b2Body* GetGround() { return mPhysics->GetGround(); }

    /**
     * Get this level's ring
     * @return This level's ring
     */
    std::shared_ptr<Ring> GetRing() { return mRing; }

    // Sparty methods
    void TransferSpartiesToShooter();
    void LaunchSparty();
};

#endif //ANGRYSPARTY_LEVEL_H
