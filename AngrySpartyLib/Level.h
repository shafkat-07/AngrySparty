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
    World mPhysics = World(mSize);

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
};

#endif //ANGRYSPARTY_LEVEL_H
