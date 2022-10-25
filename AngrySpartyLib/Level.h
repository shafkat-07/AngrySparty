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

class b2MouseJoint;
class ItemVisitor;

/**
 * This class represents a level with it's own score and item collection
 */
class Level {
private:
    /// The box2d world for this level
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;

    /// Size of the playing area in meters
    b2Vec2 mSize = b2Vec2(14.22f, 8.0f);

    /// The physics object initialized with the size of the display
    std::shared_ptr<World> mPhysics;

    /// Mouse location
    b2Vec2 mMouseLocation;

     /// The main vector of pointers to the items for each level
     std::vector<std::shared_ptr<Item>> mItems;

     /// Any item we have grabbed and are moving
     std::shared_ptr<Item> mGrabbedItem;

     /// Mouse joint for moving things
     b2MouseJoint* mMouseJoint = nullptr;

     /// Score tracking for each level
     int mScore = 0;

     /// The number of sparties in the world.
     /// The game starts with -1 sparties to account for the initial sparty location.
     /// Sparty 0 means there is one sparty in the world. Will work well for indexing.
     int mSpartyCount = -1;

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
    b2World *GetWorld() { return &mWorld; }

    bool HitTest(double x, double y);

    void Accept(ItemVisitor* visitor);

    void SetLevel();
};

#endif //ANGRYSPARTY_LEVEL_H
