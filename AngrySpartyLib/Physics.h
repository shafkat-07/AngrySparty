/**
 * @file Physics.h
 * @author kabir
 *
 * Class
 */

#pragma once

#include <Box2D/Box2D.h>

class Physics {
public:
    /// Default constructor (disabled)
    Physics() = delete;

    /// Copy constructor (disabled)
    Physics(const Physics &) = delete;

    Physics(const b2Vec2& size);

    /// Assignment operator
    void operator=(const Physics &) = delete;


private:
    /// The box2d world
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;
};
