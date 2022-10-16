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


private:
    /// The box2d world
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;
};