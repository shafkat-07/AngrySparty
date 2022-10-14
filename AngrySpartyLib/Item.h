/**
 * @file Item.h
 * @author kabir and Brendan Bushbaker
 *
 * Base Class for all items in the game.
 */

#pragma once

#include "b2_body.h"
#include <memory>
#include <wx\graphics.h>

class Level;
class b2Body;
class b2World;
class b2Fixture;
class b2Shape;

/**
 * Base class for all items in the physics system
 */
class Item {
private:
    /// The level this item is contained in
    Level *mLevel;

    /// The physics system body
    b2Body* mBody = nullptr;

    /// The box2d fixture
    b2Fixture* mFixture;

    /// The box2d body definition
    b2BodyDef mBodyDef;

    double mX = 0; ///< X location for the center of the item
    double mY = 0; ///< Y location for the center of the item

    std::unique_ptr<wxImage> mItemImage; ///< The underlying item image

    std::unique_ptr<wxBitmap> mItemBitmap; ///< The bitmap that can be displayed for an item
public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    Item(b2BodyDef bodyDef);

    Item(Level *level) {};

    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /// Get the box2d body
    b2Body* GetBody() { return mBody; }

    /// Get the box2d fixture
    b2Fixture* GetFixture() { return mFixture; }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update in seconds
     */
    virtual void Update(double elapsed) = 0;

    /**
     * Set the transform for the item.
     * @param location Location in meters
     * @param angle Angle in radians
     */
    void SetTransform(const b2Vec2& location, double angle);

    virtual bool HitTest(double x, double y);

    b2Fixture* CreateFixture(b2Shape* shape);

    /// Indicates that the item has been released by the mouse
    virtual void Release() {}

    b2World* GetWorld();
};
