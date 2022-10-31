/**
 * @file World.h
 * @author Western Tanager
 *
 * World class for the game
 */

#pragma once

#include <Box2D/Box2D.h>

/**
 * World class for the game
 */
class World {
public:
    /// Default constructor (disabled)
    World() = delete;

    /// Copy constructor (disabled)
    World(const World &) = delete;

    World(const b2Vec2& size);

    /// Assignment operator
    void operator=(const World &) = delete;

    /**
     * Returns the box2d world
     * @return The box2d world
     */
    b2World* GetWorld() { return &mWorld; }

    /**
     * Get the Box2D ground object
     * @return b2Body ground object
     */
    b2Body* GetGround() { return mGround; }

private:
    /// The box2d world
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;

public:
    void Update(double elapsed);
};
