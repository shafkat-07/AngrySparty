/**
 * @file Item.h
 * @author kabir
 *
 * Base Class for all items in the game
 */

#pragma once

#include "b2_body.h"

/**
 * Base class for all items in the physics system
 */
class Item {
private:
    /// The box2d body
    b2Body* mBody;

    /// The box2d fixture
    b2Fixture* mFixture;

    /// The box2d body definition
    b2BodyDef mBodyDef;
public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    Item(b2BodyDef bodyDef);

    /// Assignment operator
    void operator=(const Item &) = delete;

    /// Destructor
    virtual ~Item();

    /// Get the box2d body
    b2Body* GetBody() { return mBody; }

    /// Get the box2d fixture
    b2Fixture* GetFixture() { return mFixture; }

    /// Get the box2d body definition
    b2BodyDef GetBodyDef() { return mBodyDef; }
};
