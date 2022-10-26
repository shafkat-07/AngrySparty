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

#include "Item.h"
#include "World.h"
#include "Sparty.h"

class b2MouseJoint;
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
     int mSpartyCount = 0;

public:
    Level(const std::wstring &);
    void Load(const std::wstring &);
    void Clear();
    void XmlItem(wxXmlNode* node);
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

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
     * Getter for the number of sparties in the world.
     * @return Number of sparties.
     */
    int GetSpartyCount() const { return mSpartyCount; }

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

    std::shared_ptr<Item> HitTest(double x, double y);

    void SetLevel();

    void Accept(ItemVisitor* visitor);

    void Update(double elapsed);

    void TransferSpartiesToShooter();
};

#endif //ANGRYSPARTY_LEVEL_H
