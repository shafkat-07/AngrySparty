/**
 * @file Sparty.cpp
 * @author Western Tanager
 *
 * Class to represent the Angry Sparty
*/

#include "pch.h"
#include "Sparty.h"
#include "Level.h"
#include "Consts.h"

#include <b2_world.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>

/// The angular damping of the dynamic Sparty body.
const float AngularDamping = 0.9f;

/// The linear damping of the dynamic Sparty body.
const float LinearDamping = 0.1f;

/// The density of the dynamic Sparty body.
const float Density = 5.0f;

/// The friction of the dynamic Sparty body.
const float Friction = 1.0f;

/// The restitution of the dynamic Sparty body.
const float Restitution = 0.3f;

/**
 * Constructor for a sparty object
 * @param level The level this item is contained in
 */
Sparty::Sparty(Level* level) : CircleBody(level)
{
}

/**
 * Load the attributes for a sparty
 *
 * Load radius and stop velocity, which are specific to a sparty
 * @param node The Xml node we are loading the sparty from
 */
void Sparty::XmlLoad(wxXmlNode* node)
{
    CircleBody::XmlLoad(node);

    // Sparty-specific attributes
    SetStatic(true);
}

/**
 * Destroy the current sparty's body and give it a
 * new dynamic one
 */
void Sparty::ModifyBodyToDynamic()
{
    SetStatic(false);
    auto world = GetWorld();
    world->DestroyBody(GetBody());
    auto body = DefineBody(&(*CreateShape()), GetWorld());
    SetBody(body);
}

/**
 * Define the body for a Sparty
 * @param shape The b2Shape of the sparty
 * @param world The world in which this sparty resides
 * @return A pointer to a b2Body
 */
b2Body* Sparty::DefineBody(b2Shape* shape, b2World* world)
{
    if (IsStatic())
    {
        return PhysicalObject::DefineBody(shape, world);
    }
    else
    {
        // Create the body definition
        b2BodyDef bodyDefinition;
        bodyDefinition.position = GetBodyPosition();
        bodyDefinition.angle = GetAngle();
        bodyDefinition.type = b2_dynamicBody;
        bodyDefinition.angularDamping = AngularDamping;
        bodyDefinition.linearDamping = LinearDamping;
        auto body = world->CreateBody(&bodyDefinition);

        // Attributes for prior to launch.
        body->SetFixedRotation(true);
        body->SetGravityScale(0.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = Density;
        fixtureDef.friction = Friction;
        fixtureDef.restitution = Restitution;
        body->CreateFixture(&fixtureDef);
        return body;
    }
}
